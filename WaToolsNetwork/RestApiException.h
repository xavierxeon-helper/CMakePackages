#ifndef RestApiExceptionH
#define RestApiExceptionH

#include "WaToolsNetworkExportDef.h"
#include <QException>

#include "RestApiResult.h"

#include <QJsonObject>

namespace RestApi
{
   /// @brief Exception class for network-related errors

   class WATOOLSNETWORK_DECLSPEC StatusException : public QException
   {
   public:
      StatusException(const Result& result, const QUrl sourceUrl);
      StatusException(int statusCode, const QUrl sourceUrl, const QJsonObject& json = QJsonObject());

   public:
      operator QString() const;

   public:
      int getStatusCode() const;
      const QJsonObject& getContent() const;
      const QUrl& getSourceUrl() const;

   private:
      Result result;
      const QUrl sourceUrl;
   };
} // namespace RestApi

#endif // NOT RestApiExceptionH
