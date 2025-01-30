#ifndef CSVWriterH
#define CSVWriterH

#include "IOChannel.h"

#include <QFile>

namespace CSV
{
   class Writer
   {
   public:
      Writer();

   public:
      void open(const QString& fileName);
      void writeHeader(const QStringList& header);
      QTextStream entry();
      void endLine();
      void close();

   private:
      void print(const QString& text) override;

   private:
      IOChannel channel;
      QFile file;
      int maxColumns;
      int currentColumn;
   };
} // namespace CSV

#ifndef CSVWriterHPP
#include "CSVWriter.hpp"
#endif // NOT CSVWriterHPP

#endif // NOT CSVWriterH
