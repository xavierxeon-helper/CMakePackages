#ifndef ExcelXMLWriterH
#define ExcelXMLWriterH

#include <QString>

// see https://learn.microsoft.com/en-us/previous-versions/technet-magazine/cc161037(v=msdn.10)?redirectedfrom=MSDN

namespace Excel
{
   class XMLWriter
   {
   public:
      XMLWriter();
      ~XMLWriter();

   public:
      void save(const QString& fileName);
   };
} // namespace Excel

#ifndef ExcelXMLWriterHPP
#include "ExcelXMLWriter.hpp"
#endif // NOT ExcelXMLWriterHPP

#endif // NOT ExcelXMLWriterH
