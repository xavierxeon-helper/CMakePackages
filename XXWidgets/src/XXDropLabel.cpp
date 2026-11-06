#include "XXDropLabel.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>

XX::DropLabel::DropLabel(QWidget* parent)
   : QLabel(parent)
   , dropFunction()
{
   setAcceptDrops(true);
}

XX::DropLabel::~DropLabel()
{
   // do nothing
}

void XX::DropLabel::dropEvent(QDropEvent* de)
{
   const QString path = getFirstLocalFile(de->mimeData());
   if (dropFunction && !path.isEmpty())
      dropFunction(path);
}

void XX::DropLabel::dragEnterEvent(QDragEnterEvent* dee)
{
   const QString path = getFirstLocalFile(dee->mimeData());

   if (path.isEmpty())
      dee->ignore();
   else
      dee->acceptProposedAction();
}

QString XX::DropLabel::getFirstLocalFile(const QMimeData* mimeData) const
{
   if (!mimeData || !mimeData->hasUrls())
      return QString();

   for (const QUrl& url : mimeData->urls())
   {
      if (!url.isLocalFile())
         continue;

      const QString path = url.toLocalFile();
      return path;
   }
   return QString();
}
