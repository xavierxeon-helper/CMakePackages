#ifndef RestApiBlockingH
#define RestApiBlockingH

#include "NetworkSettings.h"
#include "WaToolsNetworkExportDef.h"
#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

namespace AuthProvider
{
   class Token;
};

namespace RestApi
{
   /// @brief Blocking REST API client

   class WATOOLSNETWORK_DECLSPEC Blocking : public QObject, public Network::Settings
   {
      Q_OBJECT

   public:
      Blocking(QObject* parent, const QString& baseUrl);

   public:
      virtual QJsonObject get(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
      virtual QByteArray getRaw(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
      virtual QJsonObject post(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;
      virtual QJsonObject put(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;

      void setAuthProvider(AuthProvider::Token* newProvider);
      void setBaseUrl(const QString& url);
      const QString& getbaseUrl() const;

   protected:
      using ReplyGeneratorFunction = std::function<QNetworkReply*(QNetworkRequest request)>;

   protected:
      void addUnauthorizedStatusCode(int code);
      QNetworkRequest createRequest(const QString& endpoint, const QUrlQuery& params) const;

   protected:
      QNetworkAccessManager* manager;
      QList<int> unauthorizedStatusCodes;
      AuthProvider::Token* provider;
      QString baseUrl;

   private:
      friend class Async;

   private:
      QJsonObject handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;
      QByteArray handleReplyRaw(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;
   };
} // namespace RestApi

#endif // NOT RestApiBlockingH
