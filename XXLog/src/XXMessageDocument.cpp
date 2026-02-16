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

QColor XX::MessageDocument::symbolColor(const QtMsgType& type)
{
   switch (type)
   {
      case QtDebugMsg:
         return QColor(Qt::blue);
         break;
      case QtInfoMsg:
         return QColor(Qt::green);
         break;
      default:
         return QColor(Qt::red);
         break;
   }
   return QColor(Qt::black);
}

QColor XX::MessageDocument::messageColor(const QtMsgType& type)
{
   switch (type)
   {
      case QtDebugMsg:
         return QColor(Qt::gray);
         break;
      case QtInfoMsg:
         return QColor(Qt::black);
         break;
      default:
         return QColor(Qt::black);
         break;
   }
   return QColor(Qt::black);
}

void XX::MessageDocument::outputMessage(QtMsgType type, const QMessageLogContext& context, const QString& msg)
{
   QString text = "<span style=\"color:" + symbolColor(type).name() + ";\">";
   text += MessageInterceptor::symbol(type) + "</span> ";
   text += "<span style=\"color:" + messageColor(type).name() + ";\">" + msg + "</span>";

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
