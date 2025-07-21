#ifndef LogFileHPP
#define LogFileHPP

#include "LogFile.h"

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
