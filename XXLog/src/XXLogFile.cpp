#include "XXLogFile.h"

#include <QFileInfo>

QString XX::LogFileBase::appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp)
{
   const QFileInfo info(fileName);

   QString logFileName = info.path() + "/" + info.baseName();
   logFileName += timestamp.toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

   return logFileName;
}
