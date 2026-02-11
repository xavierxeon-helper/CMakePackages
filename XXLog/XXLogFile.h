#ifndef LogFileH
#define LogFileH

#include "XXLogExportDef.h"

#include <XXCompileTimeString.h>
#include <QFile>

#include <QDateTime>

struct XXLOG_DECLSPEC LogFileBase
{
   static QString appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp = QDateTime::currentDateTime());
};

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

private:
   static LogFile* me;
};

#ifndef LogFileHPP
#include "XXLogFile.hpp"
#endif // NOT LogFileHPP

#endif // NOT LogFileH
