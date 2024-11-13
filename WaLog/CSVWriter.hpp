#ifndef CSVWriterHPP
#define CSVWriterHPP

#include "CSVWriter.h"

inline CSV::Writer::Writer(const QString& fileName)
   : IOChannel::Target()
   , channel(this, 0)
   , file(fileName)
   , maxColumns(-1)
   , currentColumn(0)
{
   file.open(QIODevice::WriteOnly | QIODevice::Text);
}

inline void CSV::Writer::setHeader(const QStringList& header)
{
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
   file.write("\n");
   currentColumn = 0;
}

inline void CSV::Writer::close()
{
   file.close();
}

inline void CSV::Writer::print(const QString& text, int chanelId)
{
   if (-1 != maxColumns && currentColumn >= maxColumns)
      return;

   file.write(text.toUtf8() + ";");
   currentColumn++;
}

#endif // NOT CSVWriterHPP
