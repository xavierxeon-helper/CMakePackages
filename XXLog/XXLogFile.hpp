#ifndef XXLogFileHPP
#define XXLogFileHPP

#include "XXLogFile.h"

template <XX::CompileTimeString tag>
inline XX::LogFile<tag>* XX::LogFile<tag>::me = nullptr;

template <XX::CompileTimeString tag>
inline XX::LogFile<tag>::LogFile(const QString& fileName)
   : QFile(fileName)
{
   me = this;
   const bool result = open(QIODevice::WriteOnly);

   qDebug() << "LOG FILE OPEN" << result << fileName;
}

template <XX::CompileTimeString tag>
inline XX::LogFile<tag>::~LogFile()
{
   me = nullptr;
   close();

   qDebug() << "LOG FILE CLOSE" << fileName();
}

template <XX::CompileTimeString tag>
inline QTextStream XX::LogFile<tag>::stream()
{
   if (!me)
      return QTextStream();

   return QTextStream(me);
}

template <XX::CompileTimeString tag>
void XX::LogFile<tag>::changeFileName(const QString& fileName)
{
   close();
   setFileName(fileName);
   open(QIODevice::WriteOnly);
}

#endif // NOT XXLogFileHPP
