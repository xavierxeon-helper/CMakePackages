#ifndef NetworkExceptionsH
#define NetworkExceptionsH

#include "WaToolsNetworkExportDef.h"
#include <QException>

#include <QJsonObject>

namespace Network
{
   /// @brief Exception class for network-related errors

   class WATOOLSNETWORK_DECLSPEC StatusException : public QException
   {
   public:
      StatusException(int statusCode, const QJsonObject& content);

   private:
      int statusCode;
      QJsonObject content;
   };
} // namespace Network

#endif // NOT NetworkExceptionsH
