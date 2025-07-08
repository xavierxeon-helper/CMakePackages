#ifndef LogFileHPP
#define LogFileHPP

#include <QDateTime>
#include <QFileInfo>

#include "LogFile.h"

inline LogFileBase::LogFileBase(const QString& fileName)
   : file(nullptr)
   , logFileName(fileName)
{
}

inline LogFileBase::~LogFileBase()
{
   cleanup();
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
      int result = file->open(QIODevice::WriteOnly);
      Q_UNUSED(result)
   }

   return QTextStream(file);
}

inline IOChannel::PrintFunction LogFileBase::printFunction()
{
   IOChannel::PrintFunction printToStream = [this](const QString& message)
   {
      stream() << message;
   };

   return printToStream;
}

inline void LogFileBase::setFileName(const QString& fileName)
{
   logFileName = fileName;
   cleanup();
}

inline QString LogFileBase::appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp)
{
   const QFileInfo info(fileName);

   QString logFileName = info.path() + "/" + info.baseName();
   logFileName += timestamp.toString("_yyyyMMdd_hhmmss");
   logFileName += "." + info.completeSuffix();

   return logFileName;
}

inline void LogFileBase::cleanup()
{
   if (file)
   {
      file->close();
      delete file;
   }
   file = nullptr;
}

//

template <CompileTimeString tag>
inline LogFile<tag>* LogFile<tag>::me = nullptr;

template <CompileTimeString tag>
inline LogFile<tag>::LogFile(const QString& fileName)
   : LogFileBase(fileName)
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
