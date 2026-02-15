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

   private:
      void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

   private:
      const int maxLines;
      QTextCursor cursor;
   };
} // namespace XX

#endif // NOT XXMessageDocumentH
