#ifndef LogFileH
#define LogFileH

#include "../WaTools/CompileTimeString.h"

#include <QFile>

#include "IOChannel.h"

class LogFileBase
{
public:
   QString getFileName() const;
   QTextStream stream();
   IOChannel::PrintFunction printFunction();

protected:
   LogFileBase(const QString& fileName, bool appendTimeStamp);
   virtual ~LogFileBase() = 0;

private:
   QFile* file;
   QString logFileName;
};

// tag is used to create a unique instance of LogFile

template <CompileTimeString tag>
class LogFile : public LogFileBase
{
public:
   LogFile(const QString& fileName, bool appendTimeStamp = false);
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
