#include "DataStore.h"

#include <QDir>
#include <QFile>
#include <QFileInfo>

QString DataStore::path = QString();

QString DataStore::getPath()
{
   return path;
}

void DataStore::setPath(const QString& _path, const QString& anchor)
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
