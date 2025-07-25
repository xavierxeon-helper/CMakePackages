#ifndef RestApiStatusExceptionH
#define RestApiStatusExceptionH

#include <QException>
#include <QJsonObject>

namespace RestApi
{
   class StatusException : public QException
   {
   public:
      StatusException(int statusCode, const QJsonObject& content);

   private:
      int statusCode;
      QJsonObject content;
   };
} // namespace RestApi

#ifndef RestApiStatusExceptionHPP
#include "RestApiStatusException.hpp"
#endif // NOT RestApiStatusExceptionHPP

#endif // NOT RestApiStatusExceptionH
