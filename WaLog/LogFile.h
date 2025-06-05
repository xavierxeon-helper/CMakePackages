#ifndef LogFileH
#define LogFileH

#include "../WaTools/CompileTimeString.h"

#include <QFile>

#include "IOChannel.h"

/// a file that acts as a target for a stream
/// this class is pure virtual
class LogFileBase
{
public:
   QString getFileName() const;
   QTextStream stream();
   IOChannel::PrintFunction printFunction();

   void setFileName(const QString& fileName); /// closes file and opens it with a new filename
   static QString appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp = QDateTime::currentDateTime());

protected:
   LogFileBase(const QString& fileName);
   virtual ~LogFileBase() = 0;

private:
   void cleanup();

private:
   QFile* file;
   QString logFileName;
};

/// tag is used to create a unique instance of LogFile and provides a static text stream
template <CompileTimeString tag>
class LogFile : public LogFileBase
{
public:
   LogFile(const QString& fileName);
   ~LogFile();

public:
   static QTextStream stream();

private:
   static LogFile* me;
};

#ifndef LogFileHPP
#include "LogFile.hpp"
#endif // NOT LogFileHPP

#endif // NOT LogFileH
