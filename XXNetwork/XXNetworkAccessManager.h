#ifndef XXNetworkAccessManagerH
#define XXNetworkAccessManagerH

#include "XXNetworkExportDef.h"
#include <QNetworkAccessManager>

#include <QList>
#include <QLoggingCategory>
#include <QNetworkAccessManager>
#include <QSslCertificate>
#include <QString>
#include <QStringList>

Q_DECLARE_LOGGING_CATEGORY(xxNetwork)

namespace XX
{
   /*!
    QNetworkAccessManager with diagnostics for the license server connection:
    request/response logging (console and/or files) and additionally trusted CA
    certificates for test servers. With nothing enabled it behaves exactly like a
    plain QNetworkAccessManager.

    \par Console logging
    Logging category "xx.network", debug level, off by default. Enable with
    QT_LOGGING_RULES="xx.network.debug=true" or
    xxNetwork().setEnabled(QtDebugMsg, true). Secrets are always redacted.

    \par File capture
    \ref setCaptureDirectory or the environment variable LSP_NETWORK_CAPTURE_DIR.
    One sub-directory "yyyyMMdd-HHmmss-<pid>" per session, one file
    "NNNN-<METHOD>-<endpoint>.txt" per exchange (request + response, timestamps,
    duration). Files are created owner-only (0600). Redacted by default;
    \ref setCaptureRedacted(false) writes live tokens - local debugging only.

    \par Additional CA certificates (test setup)
    \ref addCaCertificates or the environment variable LSP_NETWORK_EXTRA_CA (PEM file,
    e.g. the self-signed certificate of a local Keycloak). They are added to the CA
    list of requests of THIS manager only; chain and hostname verification stay
    active, no SSL errors are ignored. Public-key pinning (RestApi) is unaffected.

    \par Redaction
    Headers: Authorization (scheme kept), Cookie, Set-Cookie.
    JSON / form fields: access_token, refresh_token, id_token, code, client_secret,
    code_verifier, password.

    \par Limitations
    Response bodies are captured with peek() when the reply finishes. Callers that
    read during readyRead (streaming) leave only the unread remainder in the log.
    Intended for use from a single thread.

    @ingroup XXNetwork
    */

   class XXNETWORK_DECLSPEC NetworkAccessManager : public QNetworkAccessManager
   {
      Q_OBJECT

   public:
      explicit NetworkAccessManager(QObject* parent = nullptr);

   public:
      //! Additionally trusted CA certificates (e.g. self-signed test server). Only for requests of this manager.
      void addCaCertificates(const QList<QSslCertificate>& certificates);

      /*!
       Enables file capture below \p directory (empty => off). A sub-directory
       "yyyyMMdd-HHmmss-<pid>" is created per call.
       */
      void setCaptureDirectory(const QString& directory);

      //! The session directory currently written to (empty => capture off).
      QString captureDirectory() const;

      /*!
       false => files contain headers and bodies UNREDACTED (live tokens!).
       Only for local protocol debugging. Default: true.
       */
      void setCaptureRedacted(bool redacted);

   protected:
      QNetworkReply* createRequest(Operation op, const QNetworkRequest& request, QIODevice* outgoingData = nullptr) override;

   private:
      static QStringList formatRequest(quint64 id, Operation op, const QNetworkRequest& request, const QByteArray& body, bool redact);
      static QStringList formatResponse(quint64 id, QNetworkReply* reply, qint64 elapsedMs, bool redact);
      QString captureFilePath(quint64 id, Operation op, const QNetworkRequest& request) const;
      void writeLines(const QString& filePath, const QStringList& lines) const;

      static QByteArray operationName(Operation op, const QNetworkRequest& request);
      static QByteArray redactHeader(const QByteArray& name, const QByteArray& value);
      static QByteArray redactBody(const QByteArray& body, const QByteArray& contentType);

   private:
      quint64 requestCounter;
      QList<QSslCertificate> extraCaCertificates;
      QString sessionDirectory;
      bool captureRedacted;
   };
} // namespace XX

#endif // NOT XXNetworkAccessManagerH
