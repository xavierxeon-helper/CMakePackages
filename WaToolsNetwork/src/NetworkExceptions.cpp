#include "NetworkExceptions.h"

Network::StatusException::StatusException(int statusCode, const QJsonObject& content)
   : QException()
   , statusCode(statusCode)
   , content(content)
{
}
