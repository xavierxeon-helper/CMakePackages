#ifndef XXLogFileH
#define XXLogFileH

#include "XXLogExportDef.h"

#include <XXCompileTimeString.h>
#include <QFile>

#include <QDateTime>

namespace XX
{
   struct XXLOG_DECLSPEC LogFileBase
   {
      static QString appendTimeStampToFileName(const QString& fileName, const QDateTime& timestamp = QDateTime::currentDateTime());
   };

   //! tag is used to create a unique instance of LogFile and provides a static text stream
   template <CompileTimeString tag>
   class LogFile : public QFile
   {
   public:
      LogFile(const QString& fileName);
      ~LogFile();

   public:
      static QTextStream stream();
      //! closes file and opens it with a new filename
      void changeFileName(const QString& fileName);

   private:
      static LogFile* me;
   };
} // namespace XX

#ifndef XXLogFileHPP
#include "XXLogFile.hpp"
#endif // NOT XXLogFileHPP

#endif // NOT LogFileH
