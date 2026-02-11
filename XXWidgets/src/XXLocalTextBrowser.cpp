#include "XXLocalTextBrowser.h"

#include <QBuffer>
#include <QImage>
#include <QUrlQuery>

XX::LocalTextBrowser::LocalTextBrowser(QWidget* parent)
   : QTextBrowser(parent)
{
}

QVariant XX::LocalTextBrowser::loadResource(int type, const QUrl& name)
{
   if (QTextDocument::ImageResource != type)
      return QTextBrowser::loadResource(type, name);

   auto getFileName = [](const QUrl& url)
   {
      if (url.isLocalFile())
         return url.toLocalFile();

      if ("qrc" == url.scheme())
         return ":/" + url.fileName();

      return QString();
   };

   const QString fileName = getFileName(name);
   QImage image(fileName);
   if (image.isNull())
      return QVariant();

   const QUrlQuery query(name);
   const int width = query.hasQueryItem("width") ? query.queryItemValue("width").toInt() : -1;
   const int height = query.hasQueryItem("height") ? query.queryItemValue("height").toInt() : -1;

   if (width != -1 && height != -1)
      image = image.scaled(width, height, Qt::KeepAspectRatio, Qt::SmoothTransformation);
   else if (width != -1)
      image = image.scaledToWidth(width, Qt::SmoothTransformation);
   else if (height != -1)
      image = image.scaledToHeight(height, Qt::SmoothTransformation);

   QByteArray content;
   QBuffer buffer(&content);
   image.save(&buffer, "PNG");

   const QVariant result(content);
   return result;
}
