#ifndef LogFileHPP
#define LogFileHPP

#include "LogFile.h"

#include <QFileInfo>

template <CompileTimeString tag>
inline LogFile<tag>* LogFile<tag>::me = nullptr;

template <CompileTimeString tag>
inline LogFile<tag>::LogFile(const QString& fileName)
   : QFile(fileName)
{
   me = this;
   open(QIODevice::WriteOnly);
}

template <CompileTimeString tag>
inline LogFile<tag>::~LogFile()
{
   me = nullptr;
   close();
}

template <CompileTimeString tag>
inline QTextStream LogFile<tag>::stream()
{
   if (!me)
      return QTextStream();

   return QTextStream(me);
}

template <CompileTimeString tag>
void LogFile<tag>::changeFileName(const QString& fileName)
{
   close();
   setFileName(fileName);
   open(QIODevice::WriteOnly);
}

template <CompileTimeString tag>
QString LogFile<tag>::appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp)
{
   const QFileInfo info(fileName);

   QString logFileName = info.path() + "/" + info.baseName();
   logFileName += timestamp.toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

   return logFileName;
}

#endif // NOT LogFileHPP
