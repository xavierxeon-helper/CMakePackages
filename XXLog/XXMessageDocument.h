#ifndef XXMessageDocumentH
#define XXMessageDocumentH

#include "XXLogExportDef.h"
#include <QTextDocument>

#include <QTextCursor>

namespace XX
{
   class XXLOG_DECLSPEC MessageDocument : public QTextDocument
   {
      Q_OBJECT

   public:
      MessageDocument(QObject* parent, int maxLines = -1);
      ~MessageDocument();

   public:
      static QColor symbolColor(const QtMsgType& type);
      static QColor messageColor(const QtMsgType& type);

   private:
      void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

   private:
      const int maxLines;
      QTextCursor cursor;
   };
} // namespace XX

#endif // NOT XXMessageDocumentH
