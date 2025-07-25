#ifndef RestApiBlockingH
#define RestApiBlockingH

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
   class Blocking : public QObject
   {
      // do not use Q_OBJECT
      // this file will not be moc'ed automatically

   public:
      Blocking(QObject* parent, const QString& baseUrl);

   public:
      virtual QJsonObject get(const QString& endpoint, const QUrlQuery& params = QUrlQuery()) const;
      virtual QJsonObject post(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;
      virtual QJsonObject put(const QString& endpoint, const QJsonObject& payload = QJsonObject(), const QUrlQuery& params = QUrlQuery()) const;

   protected:
      using ReplyGeneratorFunction = std::function<QNetworkReply*(QNetworkRequest request)>;

   protected:
      void setAuthProvider(AuthProvider::Token* newProvider);
      void setUseExceptions(bool enabled);
      void setVerbose(bool enabled);
      bool isVerbose() const;
      void setBaseUrl(const QString& url);
      void addUnauthorizedStatusCode(int code);

      QNetworkRequest createRequest(const QString& endpoint, const QUrlQuery& params) const;

   protected:
      QNetworkAccessManager* manager;
      QList<int> unauthorizedStatusCodes;
      AuthProvider::Token* provider;
      QString baseUrl;

      bool useExceptions;
      bool verbose;

   private :
      friend class Async;

   private:
      QJsonObject handleReply(QNetworkRequest request, ReplyGeneratorFunction replyGenerator) const;
   };
} // namespace RestApi

#ifndef RestApiBlockingHPP
#include "RestApiBlocking.hpp"
#endif // NOT RestApiBlockingHPP

#endif // NOT RestApiBlockingH
