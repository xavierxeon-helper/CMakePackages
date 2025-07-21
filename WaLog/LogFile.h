#ifndef LogFileH
#define LogFileH

#include <CompileTimeString.h>
#include <QFile>

#include <QDateTime>

/// tag is used to create a unique instance of LogFile and provides a static text stream
template <CompileTimeString tag>
class LogFile : public QFile
{
public:
   LogFile(const QString& fileName);
   ~LogFile();

public:
   static QTextStream stream();

   void changeFileName(const QString& fileName); /// closes file and opens it with a new filename
   static QString appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp = QDateTime::currentDateTime());

private:
   static LogFile* me;
};

#ifndef LogFileHPP
#include "LogFile.hpp"
#endif // NOT LogFileHPP

#endif // NOT LogFileH
