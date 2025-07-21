
#include "LogFile.h"

#include <QDateTime>
#include <QFileInfo>

LogFileBase::LogFileBase(const QString& fileName)
   : file(nullptr)
   , logFileName(fileName)
{
}

LogFileBase::~LogFileBase()
{
   cleanup();
}

QString LogFileBase::getFileName() const
{
   return logFileName;
}

void LogFileBase::setFileName(const QString& fileName)
{
   logFileName = fileName;
   cleanup();
}

QString LogFileBase::appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp)
{
   const QFileInfo info(fileName);

   QString logFileName = info.path() + "/" + info.baseName();
   logFileName += timestamp.toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

   return logFileName;
}

void LogFileBase::cleanup()
{
   if (file)
   {
      file->close();
      delete file;
   }
   file = nullptr;
}
