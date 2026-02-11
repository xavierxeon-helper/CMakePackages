#include "XXDataStore.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

QString XX::DataStore::path = QString();

QString XX::DataStore::getPath()
{
   return path;
}

void XX::DataStore::setPath(const QString& _path, const QString& anchor)
{
   if (anchor.isEmpty())
   {
      path = _path;
   }
   else
   {
      const QString thisPath = QFileInfo(anchor).dir().absolutePath();
      path = QDir(thisPath + "/" + _path).absolutePath();
   }

   QDir().mkpath(path);
}
