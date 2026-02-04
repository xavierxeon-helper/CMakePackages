#include "RestApiException.h"

RestApi::StatusException::StatusException(const Result& result, const QUrl sourceUrl)
   : QException()
   , result(result)
   , sourceUrl(sourceUrl)
{
}

RestApi::StatusException::StatusException(int statusCode, const QUrl sourceUrl, const QJsonObject& json)
   : QException()
   , result()
   , sourceUrl(sourceUrl)
{
   result.statusCode = statusCode;
   result.json = json;
}

RestApi::StatusException::operator QString() const
{
   const QString text = QJsonDocument(result.json).toJson(QJsonDocument::Compact);
   const QString source = sourceUrl.toString();
   return QString("StatusException: %1 from %2, Content: %3").arg(result.statusCode).arg(source, text);
}

int RestApi::StatusException::getStatusCode() const
{
   return result.statusCode;
}

const QJsonObject& RestApi::StatusException::getContent() const
{
   return result.json;
}

const QUrl& RestApi::StatusException::getSourceUrl() const
{
   return sourceUrl;
}

//

RestApi::UnreachableException::UnreachableException(const QUrl& sourceUrl)
   : QException()
   , sourceUrl(sourceUrl)
{
}

RestApi::UnreachableException::operator QString() const
{
   const QString source = sourceUrl.toString();
   return QString("UnreachableException from %2").arg(source);
}

const QUrl& RestApi::UnreachableException::getSourceUrl() const
{
   return sourceUrl;
}
