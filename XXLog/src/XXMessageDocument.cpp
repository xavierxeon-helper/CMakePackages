#include "XXMessageDocument.h"

#include <QTextCursor>

#include "XXMessageInterceptor.h"

XX::MessageDocument::MessageDocument(QObject* parent, int maxLines)
   : QTextDocument(parent)
   , maxLines(maxLines)
{
   MessageInterceptor::enable(this, &MessageDocument::outputMessage);
}

XX::MessageDocument::~MessageDocument()
{
   MessageInterceptor::disable(this);
}

// see https://stackoverflow.com/questions/27814909/qtextedit-delete-whole-line-at-given-position
void XX::MessageDocument::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   const QString symbol = MessageInterceptor::symbol(type);
   const QString text = "<span style=\"color:blue;\">" + symbol + " " + msg + "</span><br>\n";

   QTextCursor cursor(this);
   cursor.insertHtml(text);
}
