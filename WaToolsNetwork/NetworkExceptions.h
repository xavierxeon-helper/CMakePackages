#ifndef NetworkExceptionsH
#define NetworkExceptionsH

#include <QException>
#include <QJsonObject>

namespace Network
{
   class StatusException : public QException
   {
   public:
      StatusException(int statusCode, const QJsonObject& content);

   private:
      int statusCode;
      QJsonObject content;
   };
} // namespace Network

#ifndef NetworkExceptionsHPP
#include "NetworkExceptions.hpp"
#endif // NOT NetworkExceptionsHPP

#endif // NOT NetworkExceptionsH
