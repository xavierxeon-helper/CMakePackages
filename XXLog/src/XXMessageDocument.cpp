#include "XXMessageDocument.h"

#include <iostream>

#include "XXMessageInterceptor.h"

XX::MessageDocument::MessageDocument(QObject* parent, int maxLines)
   : QTextDocument(parent)
   , maxLines(maxLines)
   , cursor(this)
{
   MessageInterceptor::enable(this, &MessageDocument::outputMessage);
}

XX::MessageDocument::~MessageDocument()
{
   MessageInterceptor::disable(this);
}

void XX::MessageDocument::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   const QString symbol = MessageInterceptor::symbol(type);
   const QString text = "<span style=\"color:blue;\">" + symbol + " " + msg + "</span>";

   cursor.movePosition(QTextCursor::End);
   cursor.insertHtml(text);
   cursor.insertText("\n");

   if (maxLines < 0)
      return;

   while (maxLines < cursor.blockNumber())
   {
      cursor.movePosition(QTextCursor::Start);
      cursor.select(QTextCursor::LineUnderCursor);
      cursor.removeSelectedText();
      cursor.deleteChar();
   }
}
