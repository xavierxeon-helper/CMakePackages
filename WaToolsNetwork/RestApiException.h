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
      StatusException(const Result& result);
      StatusException(int statusCode, const QJsonObject& json = QJsonObject());

   private:
      Result result;
   };
} // namespace RestApi

#endif // NOT RestApiExceptionH
