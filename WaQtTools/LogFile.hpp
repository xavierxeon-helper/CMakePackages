#ifndef LogFileHPP
#define LogFileHPP

#include "LogFile.h"

template <CompileTimeString tag>
inline LogFile<tag>* LogFile<tag>::me = nullptr;

template <CompileTimeString tag>
inline LogFile<tag>::LogFile(const QString& fileName)
   : file(nullptr)
{
   me = this;

   file = new QFile(fileName);
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

#endif // NOT LogFileHPP
