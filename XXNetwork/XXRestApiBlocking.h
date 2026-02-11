#ifndef XXRestApiBlockingH
#define XXRestApiBlockingH

#include "XXNetworkExportDef.h"
#include "XXNetworkSettings.h"
#include <QObject>

#include <QJsonObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QUrlQuery>

#include "XXRestApiResult.h"

namespace AuthProvider
{
   class Token;
};

namespace RestApi
{
   /// @brief Blocking REST API client

   class XXNETWORK_DECLSPEC Blocking : public QObject, public Network::Settings
   {
      Q_OBJECT

   public:
      Blocking(QObject* parent, const QString& baseUrl);

   public:
      virtual Result get(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
      virtual ResultRaw getRaw(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
      virtual Result post(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;
      virtual Result put(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;

      void setAuthProvider(AuthProvider::Token* newProvider);
      void setBaseUrl(const QString& url);
      const QString& getBaseUrl() const;

   protected:
      using ReplyGeneratorFunction = std::function<QNetworkReply*(QNetworkRequest request)>;

   protected:
      void addUnauthorizedStatusCode(int code);
      QNetworkRequest createRequest(const QString& endpoint, const QUrlQuery& params) const;

   protected:
      QNetworkAccessManager* manager;
      QList<int> successStatusCodes;
      QList<int> unauthorizedStatusCodes;
      AuthProvider::Token* provider;
      QString baseUrl;

   private:
      friend class Async;

   private:
      Result handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;
      ResultRaw handleReplyRaw(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;
   };
} // namespace RestApi

#endif // NOT XXRestApiBlockingH
