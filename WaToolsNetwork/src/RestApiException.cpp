#include "RestApiException.h"

RestApi::StatusException::StatusException(const Result& result)
   : QException()
   , result(result)
{
}

RestApi::StatusException::StatusException(int statusCode, const QJsonObject& json)
   : QException()
   , result()
{
   result.statusCode = statusCode;
   result.json = json;
}
