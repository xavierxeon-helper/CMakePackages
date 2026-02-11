#ifndef XXLoggerH
#define XXLoggerH

#include "XXLogExportDef.h"

#include <QColor>
#include <QDateTime>
#include <QTextStream>

namespace XX
{
   /// provide streams for logging messages and warnings
   namespace Logger
   {
      XXLOG_DECLSPEC QTextStream stream(const Qt::GlobalColor& color = Qt::black);

      class XXLOG_DECLSPEC Target
      {
      public:
         class StreamProxy;

      public:
         Target(int stackSize);
         ~Target();

      protected:
         struct Entry
         {
            QDateTime timeStamp;
            QString text;
            QColor color;

            using Buffer = QList<Entry>;
         };

      protected:
         virtual void update(const Entry::Buffer& buffer) = 0;
         void clear();

      private:
         void print(const QString& text, const QColor& color);

      private:
         static Target* master;
         QList<Target*> others;
         int stackSize;
         Entry::Buffer buffer;
      };
   } // namespace Logger
} // namespace XX

#endif // NOT XXLoggerH
