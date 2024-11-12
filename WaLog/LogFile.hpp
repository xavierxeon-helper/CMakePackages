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
{
   me = this;

   const QFileInfo info(fileName);
   QString logFileName = info.path() + "/" +  info.baseName();
   if(appendTimeStamp)
      logFileName +=  QDateTime::currentDateTime().toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

   file = new QFile(logFileName);
   file->open(QIODevice::WriteOnly);
}

template <CompileTimeString tag>
inline LogFile<tag>::~LogFile()
{
   file->close();
   delete file;

   me = nullptr;
}

template <CompileTimeString tag>
inline QTextStream LogFile<tag>::stream()
{
   if (!me)
      return QTextStream();

   return QTextStream(me->file);
}

template <CompileTimeString tag>
QString LogFile<tag>::getFileName() const
{
   return file->fileName();
}

#endif // NOT LogFileHPP
