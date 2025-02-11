#ifndef LogFileHPP
#define LogFileHPP

#include <QDateTime>
#include <QFileInfo>

#include "LogFile.h"

inline LogFileBase::LogFileBase(const QString& fileName, bool appendTimeStamp)
   : file(nullptr)
   , logFileName()
{
   const QFileInfo info(fileName);

   logFileName = info.path() + "/" + info.baseName();
   if (appendTimeStamp)
      logFileName += QDateTime::currentDateTime().toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();
}

inline LogFileBase::~LogFileBase()
{
   if (file)
   {
      file->close();
      delete file;
   }
}

inline QString LogFileBase::getFileName() const
{
   return logFileName;
}

inline QTextStream LogFileBase::stream()
{
   if (!file)
   {
      file = new QFile(logFileName);
      file->open(QIODevice::WriteOnly);
   }

   return QTextStream(file);
}

inline void LogFileBase::writeToStream(const QString& message)
{
   stream() << message;
}

//

template <CompileTimeString tag>
inline LogFile<tag>* LogFile<tag>::me = nullptr;

template <CompileTimeString tag>
inline LogFile<tag>::LogFile(const QString& fileName, bool appendTimeStamp)
   : LogFileBase(fileName, appendTimeStamp)
{
   me = this;
}

template <CompileTimeString tag>
inline LogFile<tag>::~LogFile()
{
   me = nullptr;
}

template <CompileTimeString tag>
inline QTextStream LogFile<tag>::stream()
{
   if (!me)
      return QTextStream();

   me->stream();
}

#endif // NOT LogFileHPP
