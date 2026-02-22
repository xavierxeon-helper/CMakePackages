#ifndef XXQtMessageDocumentH
#define XXQtMessageDocumentH

#include "XXLogExportDef.h"
#include <QTextDocument>

#include <QTextCursor>

namespace XX
{
   namespace QtMessage
   {
      //! @brief qt message as document
      //! @ingroup XXLog

      class XXLOG_DECLSPEC Document : public QTextDocument
      {
         Q_OBJECT

      public:
         Document(QObject* parent, int maxLines = -1);
         ~Document();

      private:
         QColor symbolColor(const QtMsgType& type);
         QColor messageColor(const QtMsgType& type);

         void outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg);

      private:
         const int maxLines;
         QTextCursor cursor;
      };
   } // namespace QtMessage
} // namespace XX

#endif // NOT XXQtMessageDocumentH
