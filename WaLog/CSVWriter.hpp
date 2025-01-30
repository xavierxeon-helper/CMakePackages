#ifndef CSVWriterHPP
#define CSVWriterHPP

#include "CSVWriter.h"

inline CSV::Writer::Writer()
   : channel(this)
   , file(fileName)
   , maxColumns(-1)
   , currentColumn(0)
{
   IOChannel::PrintFunction printFunction = std::bind(&CSV::Writer::print, this, std::placeholders::_1);
   channel.setup(printFunction);
}

inline void CSV::Writer::open(const QString& fileName)
{
   file.open(QIODevice::WriteOnly | QIODevice::Text);
}

inline void CSV::Writer::writeHeader(const QStringList& header)
{
   if (!file.isOpen())
      return;

   maxColumns = header.count();
   for (const QString& entry : header)
   {
      file.write(entry.toUtf8() + ";");
   }
   file.write("\n");
}

inline QTextStream CSV::Writer::entry()
{
   return QTextStream(&channel);
}

inline void CSV::Writer::endLine()
{
   if (!file.isOpen())
      return;

   file.write("\n");
   currentColumn = 0;
}

inline void CSV::Writer::close()
{
   if (!file.isOpen())
      return;

   file.close();
}

inline void CSV::Writer::print(const QString& text)
{
   if (-1 != maxColumns && currentColumn >= maxColumns)
      return;

   if (!file.isOpen())
      return;

   file.write(text.toUtf8() + ";");
   currentColumn++;
}

#endif // NOT CSVWriterHPP
