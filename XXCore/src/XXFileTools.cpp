#include "XXFileTools.h"

#ifdef Q_OS_WASM
#include <emscripten/fetch.h>
#endif // Q_OS_WASM

#include <QDir>
#include <QDirIterator>
#include <QJsonDocument>
#include <QProcess>
#include <QSettings>
#include <QStandardPaths>

QJsonObject XX::FileTools::readJson(const QString& filePath, bool verbose)
{
   QFile file(filePath);
   if (!file.open(QIODevice::ReadOnly))
   {
      if (verbose)
         qWarning() << __FUNCTION__ << "Failed to open JSON file:" << filePath;
      return QJsonObject();
   }

   const QByteArray fileContent = file.readAll();
   file.close();

   return parseBytes(fileContent);
}

QJsonObject XX::FileTools::parseBytes(const QByteArray& data)
{
   QJsonParseError parseError;
   QJsonDocument doc = QJsonDocument::fromJson(data, &parseError);

   if (QJsonParseError::NoError != parseError.error)
   {
      qWarning() << "Failed to parse JSON file:" << parseError.errorString();
      return QJsonObject();
   }

   const QJsonObject object = doc.object();
   return object;
}

void XX::FileTools::writeJson(const QJsonObject& data, const QString& filePath, bool verbose)
{
   if (data.isEmpty())
   {
      if (verbose)
         qWarning() << __FUNCTION__ << "No data to write";
      return;
   }

   QFile file(filePath);
   if (!file.open(QIODevice::WriteOnly))
   {
      if (verbose)
         qWarning() << __FUNCTION__ << "Failed to open JSON file:" << filePath;
      return;
   }

   QJsonDocument doc(data);
   file.write(doc.toJson(QJsonDocument::Indented));
   file.close();
}

#ifdef Q_OS_WASM

QByteArray XX::FileTools::readIndexDB(const QString& filePath)
{
   emscripten_fetch_attr_t attr;
   emscripten_fetch_attr_init(&attr);
   strcpy(attr.requestMethod, "GET");
   attr.attributes = EMSCRIPTEN_FETCH_NO_DOWNLOAD | EMSCRIPTEN_FETCH_SYNCHRONOUS | EMSCRIPTEN_FETCH_LOAD_TO_MEMORY;

   const QByteArray filePathBytes = filePath.toUtf8();
   emscripten_fetch_t* fetch = emscripten_fetch(&attr, filePathBytes.constData());

   QByteArray data(fetch->data, fetch->numBytes);
   emscripten_fetch_close(fetch);

   return data;
}

void XX::FileTools::writeIndexDB(const QByteArray& data, const QString& filePath)
{
   emscripten_fetch_attr_t attr;
   emscripten_fetch_attr_init(&attr);
   strcpy(attr.requestMethod, "EM_IDB_STORE");
   attr.attributes = EMSCRIPTEN_FETCH_REPLACE | EMSCRIPTEN_FETCH_SYNCHRONOUS | EMSCRIPTEN_FETCH_PERSIST_FILE;

   attr.requestData = data.constData();
   attr.requestDataSize = data.size();

   const QByteArray filePathBytes = filePath.toUtf8();
   emscripten_fetch_t* fetch = emscripten_fetch(&attr, filePathBytes.constData());
   emscripten_fetch_close(fetch);
}

QJsonObject XX::FileTools::readIndexDBJson(const QString& filePath)
{
   const QByteArray content = readIndexDB(filePath);
   return parseBytes(content);
}

void XX::FileTools::writeIndexDBJson(const QJsonObject& data, const QString& filePath)
{
   QJsonDocument doc(data);
   const QByteArray content = doc.toJson(QJsonDocument::Indented);

   writeIndexDB(content, filePath);
}

#endif // Q_OS_WASM

QString XX::FileTools::compileDropboxPath(const QString& appName)
{
#if defined(Q_OS_WIN32)
   QString homePath = QDir::homePath();
   homePath = QDir::fromNativeSeparators(homePath);
   QString dropboxInfoPath = homePath + "/AppData/Local/Dropbox/info.json";
#elif defined(Q_OS_MACOS)
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#else // linux
   QString dropboxInfoPath = QDir::homePath() + "/.dropbox/info.json";
#endif

   const QJsonObject dropoxObject = readJson(dropboxInfoPath);
   if (dropoxObject.isEmpty())
      return QString();

   QJsonValue jsonPersonal = dropoxObject.value("personal");
   if (jsonPersonal.isUndefined())
      return QString();

   QJsonValue jsonPath = jsonPersonal.toObject().value("path");
   if (jsonPath.isUndefined())
      return QString();

   QString dropBoxPath = jsonPath.toString();
   dropBoxPath = QDir::fromNativeSeparators(dropBoxPath);
   QString path = dropBoxPath + QString("/Apps/") + appName;

   return path;
}

QString XX::FileTools::compileNextCloudPath(const QString& appName)
{
#if defined(Q_OS_WIN32)
   QString appPath = QStandardPaths ::writableLocation(QStandardPaths::AppDataLocation);
   appPath = QDir::fromNativeSeparators(appPath);
   appPath.replace(QCoreApplication::organizationName() + "/" + QCoreApplication::applicationName(), "");
   const QString nextCloudConfPath = appPath + "/Nextcloud/nextcloud.cfg";
#elif defined(Q_OS_MACOS)
   const QString nextCloudConfPath = QDir::homePath() + "/Library/Preferences/Nextcloud/nextcloud.cfg";
#else // linux
   const QString nextCloudConfPath = QDir::homePath() + "/.config/Nextcloud/nextcloud.cfg";
#endif

   if (!QFile::exists(nextCloudConfPath))
      return QString();

   QSettings settings(nextCloudConfPath, QSettings::IniFormat);

   QString nextCloudPath = settings.value("Accounts/0/Folders/1/localPath").toString();
   nextCloudPath = QDir::fromNativeSeparators(nextCloudPath);
   QString path = nextCloudPath + QString("Apps/") + appName;

   return path;
}

QJsonObject XX::FileTools::readApiKeys(const QString& appName, bool verbose)
{
   static const QStringList homePaths = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
   const QString keyFileName = homePaths.first() + "/.ApiKeys/" + appName + ".json";

   return readJson(keyFileName, verbose);
}

QStringList XX::FileTools::compileResourceNames(const QStringList& ignoreList)
{
   auto ignoreName = [&](const QString& name)
   {
      for (const QString& test : ignoreList)
      {
         if (name.startsWith(test))
            return true;
      }
      return false;
   };

   QStringList nameList;

   QDirIterator it(":", QDirIterator::Subdirectories);
   while (it.hasNext())
   {
      const QString name = it.next();
      if (ignoreName(name))
         continue;

      QFileInfo fileInfo(name);
      if (fileInfo.isFile())
         nameList.append(name);

      //nameList.append(name);
   }

   return nameList;
}

void XX::FileTools::openVSCode(const QString& path)
{
   openVSCode(QStringList{path});
}

void XX::FileTools::openVSCode(QStringList pathList)
{
   pathList.removeAll(QString(""));
   if (pathList.isEmpty())
      return;

#if defined(Q_OS_MAC)
   QString editorCommand = "code";
#elif defined(Q_OS_WIN)
   QString editorCommand = "code.cmd";
#else
   QString editorCommand = "code";
#endif

#if defined(Q_OS_IOS) || defined(Q_OS_ANDROID) || defined(Q_OS_WASM)
   qWarning() << __FUNCTION__ << "Not supported on mobile platforms";
#else
   QProcess::startDetached(editorCommand, pathList);
#endif
}
