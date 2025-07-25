#ifndef RestApiStatusExceptionHPP
#define RestApiStatusExceptionHPP

#include "RestApiStatusException.h"

inline RestApi::StatusException::StatusException(int statusCode, const QJsonObject& content)
   : QException()
   , statusCode(statusCode)
   , content(content)
{
}

#endif // NOT RestApiStatusExceptionHPP