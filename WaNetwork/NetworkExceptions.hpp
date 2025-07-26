#ifndef NetworkExceptionsHPP
#define NetworkExceptionsHPP

#include "NetworkExceptions.h"

inline Network::StatusException::StatusException(int statusCode, const QJsonObject& content)
   : QException()
   , statusCode(statusCode)
   , content(content)
{
}

#endif // NOT NetworkExceptionsHPP
