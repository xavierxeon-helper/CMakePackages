#ifndef CSVWriterH
#define CSVWriterH

#include "IOChannel.h"

#include <QFile>

namespace CSV
{
   class Writer : public IOChannel::Target
   {
   public:
      Writer(const QString& fileName);

   public:
      void setHeader(const QStringList& header);
      QTextStream entry();
      void endLine();
      void close();

   private:
      void print(const QString& text, int chanelId) override;

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
