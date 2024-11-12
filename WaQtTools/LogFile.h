#ifndef LogFileH
#define LogFileH

#include "../WaTools/CompileTimeString.h"

#include <QFile>

template <CompileTimeString tag>
class LogFile
{
public:
   LogFile(const QString& fileName);
   ~LogFile();

public:
   static QTextStream stream();

private:
   static LogFile* me;
   QFile* file;
};

#ifndef LogFileHPP
#include "LogFile.hpp"
#endif // NOT LogFileHPP

#endif // NOT LogFileH
