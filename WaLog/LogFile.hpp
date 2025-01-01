#ifndef LogFileHPP
#define LogFileHPP

#include <QDateTime>
#include <QFileInfo>

#include "LogFile.h"

template <CompileTimeString tag>
inline LogFile<tag>* LogFile<tag>::me = nullptr;

template <CompileTimeString tag>
inline LogFile<tag>::LogFile(const QString& fileName, bool appendTimeStamp)
   : file(nullptr)
   , logFileName()
{
   me = this;

   const QFileInfo info(fileName);

   logFileName = info.path() + "/" +  info.baseName();
   if(appendTimeStamp)
      logFileName +=  QDateTime::currentDateTime().toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

}

template <CompileTimeString tag>
inline LogFile<tag>::~LogFile()
{
   if(file)
   {
      file->close();
      delete file;
   }

   me = nullptr;
}

template <CompileTimeString tag>
inline QTextStream LogFile<tag>::stream()
{
   if (!me)
      return QTextStream();

   me->openFileIfNecessary();

   return QTextStream(me->file);
}

template <CompileTimeString tag>
QString LogFile<tag>::getFileName() const
{
   return logFileName;
}

template <CompileTimeString tag>
void LogFile<tag>::openFileIfNecessary()
{
   if(file)
      return;

   file = new QFile(logFileName);
   file->open(QIODevice::WriteOnly);
}

#endif // NOT LogFileHPP
