#ifndef XXRestApiExceptionH
#define XXRestApiExceptionH

#include "XXNetworkExportDef.h"
#include <QException>

#include "XXRestApiResult.h"

#include <QJsonObject>

namespace XX
{
   namespace RestApi
   {
      /// @brief Exception class for network-related errors

      class XXNETWORK_DECLSPEC StatusException : public QException
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

      class XXNETWORK_DECLSPEC UnreachableException : public QException
      {
      public:
         UnreachableException(const QUrl& sourceUrl);

      public:
         operator QString() const;

      public:
         const QUrl& getSourceUrl() const;

      private:
         const QUrl sourceUrl;
      };
   } // namespace RestApi
} // namespace XX

#endif // NOT XXRestApiExceptionH
