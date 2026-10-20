#include "XXNetworkAccessManager.h"

#include <QBuffer>
#include <QCoreApplication>
#include <QDateTime>
#include <QDir>
#include <QElapsedTimer>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QRegularExpression>
#include <QSslConfiguration>
#include <QUrlQuery>

// Debug output disabled by default (minimum level Info).
Q_LOGGING_CATEGORY(xxNetwork, "xx.network", QtInfoMsg)

namespace
{
   const QList<QByteArray> secretKeys = {"authorization", "access_token", "refresh_token", "id_token",
                                         "code", "client_secret", "code_verifier", "password"};

   QByteArray redacted(const QByteArray& value)
   {
      return "<redacted " + QByteArray::number(value.size()) + " bytes>";
   }
} // namespace

XX::NetworkAccessManager::NetworkAccessManager(QObject* parent)
   : QNetworkAccessManager(parent)
   , requestCounter(0)
   , extraCaCertificates()
   , sessionDirectory()
   , captureRedacted(false)
{
   const QString caFile = qEnvironmentVariable("LSP_NETWORK_EXTRA_CA");
   if (!caFile.isEmpty())
   {
      const QList<QSslCertificate> certs = QSslCertificate::fromPath(caFile, QSsl::Pem);
      if (certs.isEmpty())
         qCWarning(xxNetwork) << "No certificate loaded from" << caFile;
      else
      {
         qCWarning(xxNetwork) << "Trusting additional CA certificate(s) from" << caFile << "(test setup!)";
         addCaCertificates(certs);
      }
   }

   const QString dir = qEnvironmentVariable("LSP_NETWORK_CAPTURE_DIR");
   if (!dir.isEmpty())
      setCaptureDirectory(dir);
}

void XX::NetworkAccessManager::addCaCertificates(const QList<QSslCertificate>& certificates)
{
   extraCaCertificates += certificates;
}

void XX::NetworkAccessManager::setCaptureDirectory(const QString& directory)
{
   sessionDirectory.clear();
   if (directory.isEmpty())
      return;

   const QString path = QDir(directory).filePath(QDateTime::currentDateTime().toString("yyyyMMdd-HHmmss") + QString("-%1").arg(QCoreApplication::applicationPid()));
   if (!QDir().mkpath(path))
   {
      qCWarning(xxNetwork) << "Cannot create network capture directory" << path;
      return;
   }

   sessionDirectory = path;
   qCInfo(xxNetwork) << "Capturing network traffic to" << path;
}

QString XX::NetworkAccessManager::captureDirectory() const
{
   return sessionDirectory;
}

void XX::NetworkAccessManager::setCaptureRedacted(bool redacted)
{
   captureRedacted = redacted;
}

QNetworkReply* XX::NetworkAccessManager::createRequest(Operation op, const QNetworkRequest& orgRequest, QIODevice* outgoingData)
{
   QNetworkRequest effectiveRequest(orgRequest);
   if (!extraCaCertificates.isEmpty())
   {
      QSslConfiguration ssl = effectiveRequest.sslConfiguration();
      ssl.addCaCertificates(extraCaCertificates);
      effectiveRequest.setSslConfiguration(ssl);
   }

   // Fast path: logging off -> zero overhead, outgoingData untouched.
   const bool toConsole = xxNetwork().isDebugEnabled();
   const bool toFile = !sessionDirectory.isEmpty();

   if (!toConsole && !toFile)
      return QNetworkAccessManager::createRequest(op, effectiveRequest, outgoingData);

   const quint64 id = ++requestCounter;

   // --- Outgoing body -------------------------------------------------------------
   // Random-access device (QBuffer, as created by post(QByteArray)): peek without consuming.
   // Sequential device: read fully and substitute an equivalent QBuffer.
   QByteArray body;
   QIODevice* upload = outgoingData;
   if (outgoingData)
   {
      if (!outgoingData->isSequential())
         body = outgoingData->peek(outgoingData->size() - outgoingData->pos());
      else
      {
         body = outgoingData->readAll();
         auto* buffer = new QBuffer;
         buffer->setData(body);
         buffer->open(QIODevice::ReadOnly);
         upload = buffer;
      }
   }

   const QString filePath = toFile ? captureFilePath(id, op, effectiveRequest) : QString();

   if (toConsole)
      for (const QString& line : formatRequest(id, op, effectiveRequest, body, true))
         qCDebug(xxNetwork).noquote() << line;
   if (toFile)
      writeLines(filePath, formatRequest(id, op, effectiveRequest, body, captureRedacted));

   QNetworkReply* reply = QNetworkAccessManager::createRequest(op, effectiveRequest, upload);
   if (upload != outgoingData)
      upload->setParent(reply);

   QElapsedTimer timer;
   timer.start();

   // --- Incoming response ---------------------------------------------------------
   // Connected BEFORE the caller gets the reply -> runs before its finished handlers.
   // peek() does not consume the data; the caller can still readAll() afterwards.

   auto onFinished = [this, reply, id, timer, toConsole, filePath]()
   {
      const qint64 elapsed = timer.elapsed();
      if (toConsole)
         for (const QString& line : formatResponse(id, reply, elapsed, true))
            qCDebug(xxNetwork).noquote() << line;
      if (!filePath.isEmpty())
         writeLines(filePath, formatResponse(id, reply, elapsed, captureRedacted));
   };
   connect(reply, &QNetworkReply::finished, this, onFinished);

   return reply;
}

QStringList XX::NetworkAccessManager::formatRequest(quint64 id, Operation op, const QNetworkRequest& request,
                                                    const QByteArray& body, bool redact)
{
   QStringList lines;
   lines << QString(">>> #%1 %2 %3   [%4]")
               .arg(id)
               .arg(QString::fromLatin1(operationName(op, request)), request.url().toString(),
                    QDateTime::currentDateTime().toString(Qt::ISODateWithMs));

   for (const QByteArray& name : request.rawHeaderList())
   {
      const QByteArray value = request.rawHeader(name);
      lines << QString(">>>    %1: %2").arg(QString::fromLatin1(name), QString::fromUtf8(redact ? redactHeader(name, value) : value));
   }

   if (!body.isEmpty())
   {
      const QByteArray contentType = request.header(QNetworkRequest::ContentTypeHeader).toByteArray();
      lines << ">>>    body: " + QString::fromUtf8(redact ? redactBody(body, contentType) : body);
   }
   return lines;
}

QStringList XX::NetworkAccessManager::formatResponse(quint64 id, QNetworkReply* reply, qint64 elapsedMs, bool redact)
{
   QStringList lines;
   const int status = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
   lines << QString("<<< #%1 %2 %3   [%4, %5 ms]")
               .arg(id)
               .arg(status)
               .arg(reply->url().toString(), QDateTime::currentDateTime().toString(Qt::ISODateWithMs))
               .arg(elapsedMs);

   if (QNetworkReply::NoError != reply->error())
      lines << QString("<<<    error: %1 %2").arg(int(reply->error())).arg(reply->errorString());

   for (const auto& [name, value] : reply->rawHeaderPairs())
      lines << QString("<<<    %1: %2").arg(QString::fromLatin1(name), QString::fromUtf8(redact ? redactHeader(name, value) : value));

   const QByteArray body = reply->peek(reply->bytesAvailable());
   if (!body.isEmpty())
   {
      const QByteArray contentType = reply->header(QNetworkRequest::ContentTypeHeader).toByteArray();
      lines << "<<<    body: " + QString::fromUtf8(redact ? redactBody(body, contentType) : body);
   }
   return lines;
}

QString XX::NetworkAccessManager::captureFilePath(quint64 id, Operation op, const QNetworkRequest& request) const
{
   static const QRegularExpression invalid("[^A-Za-z0-9_.-]");

   QString endpoint = request.url().path().section('/', -1);
   endpoint.replace(invalid, "_");
   if (endpoint.isEmpty())
      endpoint = "root";

   return QDir(sessionDirectory).filePath(QString("%1-%2-%3.txt").arg(id, 4, 10, QChar('0')).arg(QString::fromLatin1(operationName(op, request)), endpoint));
}

void XX::NetworkAccessManager::writeLines(const QString& filePath, const QStringList& lines) const
{
   QFile file(filePath);
   const bool isNew = !file.exists();
   if (!file.open(QIODevice::WriteOnly | QIODevice::Append | QIODevice::Text))
   {
      qCWarning(xxNetwork) << "Cannot write network capture file" << filePath << file.errorString();
      return;
   }
   if (isNew)
      file.setPermissions(QFileDevice::ReadOwner | QFileDevice::WriteOwner); // 0600 on Unix

   file.write(lines.join('\n').toUtf8() + "\n\n");
}

QByteArray XX::NetworkAccessManager::operationName(Operation op, const QNetworkRequest& request)
{
   switch (op)
   {
      case HeadOperation:
         return "HEAD";
      case GetOperation:
         return "GET";
      case PutOperation:
         return "PUT";
      case PostOperation:
         return "POST";
      case DeleteOperation:
         return "DELETE";
      case CustomOperation:
         return request.attribute(QNetworkRequest::CustomVerbAttribute).toByteArray();
      default:
         return "UNKNOWN";
   }
}

QByteArray XX::NetworkAccessManager::redactHeader(const QByteArray& name, const QByteArray& value)
{
   if (name.compare("authorization", Qt::CaseInsensitive) == 0)
   {
      const qsizetype space = value.indexOf(' '); // keep the scheme ("Bearer")
      return space > 0 ? value.left(space) + ' ' + redacted(value.mid(space + 1)) : redacted(value);
   }
   if (name.compare("cookie", Qt::CaseInsensitive) == 0 || name.compare("set-cookie", Qt::CaseInsensitive) == 0)
      return redacted(value);
   return value;
}

QByteArray XX::NetworkAccessManager::redactBody(const QByteArray& body, const QByteArray& contentType)
{
   if (contentType.contains("json"))
   {
      QJsonParseError error;
      QJsonDocument doc = QJsonDocument::fromJson(body, &error);
      if (QJsonParseError::NoError == error.error && doc.isObject())
      {
         QJsonObject obj = doc.object();
         for (const QString& key : obj.keys())
            if (secretKeys.contains(key.toLower().toUtf8()))
               obj[key] = QString::fromLatin1(redacted(obj[key].toString().toUtf8()));
         return QJsonDocument(obj).toJson(QJsonDocument::Compact);
      }
   }
   else if (contentType.contains("x-www-form-urlencoded"))
   {
      QUrlQuery query(QString::fromUtf8(body));
      QUrlQuery out;
      for (const auto& [key, value] : query.queryItems(QUrl::FullyDecoded))
         out.addQueryItem(key, secretKeys.contains(key.toLower().toUtf8())
                                  ? QString::fromLatin1(redacted(value.toUtf8()))
                                  : value);
      return out.toString(QUrl::FullyDecoded).toUtf8();
   }
   return body.size() > 4096 ? body.left(4096) + "... (" + QByteArray::number(body.size()) + " bytes)" : body;
}