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

#endif // NOT NetworkExceptionsH
