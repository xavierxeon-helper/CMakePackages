
#include "MessageLabel.h"

#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QToolTip>

#include "LogSymbol.h"

MessageLabel::MessageLabel(QWidget* parent, int stackSize)
   : QLabel(parent)
   , Logger()
   , stackSize(stackSize)
   , showToolTip(true)
   , addTimeStamp(true)
   , messageStack()
   , historyDocument()
   , messageExpiration()
{
   setMinimumSize(QSize(50, 20));
   setFrameShape(QFrame::NoFrame);
   setFrameShadow(QFrame::Plain);

   QTimer* messageTimer = new QTimer(this);
   connect(messageTimer, &QTimer::timeout, this, &MessageLabel::slotUpdateTimeout);
   messageTimer->setInterval(1000);
   messageTimer->start();
}

QTextDocument* MessageLabel::getHistoryDocument()
{
   return &historyDocument;
}

void MessageLabel::setStackSize(const int& newStackSize)
{
   stackSize = newStackSize;
   updateStack();
}

void MessageLabel::clearStack()
{
   messageStack.clear();
   updateStack();
}

void MessageLabel::setShowToolTip(bool newShowToolTip)
{
   showToolTip = newShowToolTip;
}

void MessageLabel::setAddTimeStamp(bool newAddTimeStamp)
{
   addTimeStamp = newAddTimeStamp;
}

void MessageLabel::slotUpdateTimeout()
{
   if (messageExpiration.isNull())
      return;

   if (QDateTime::currentDateTime() < messageExpiration)
      return;

   messageExpiration = QDateTime();
   setText("");
}

void MessageLabel::updateStack()
{
   while (messageStack.size() > stackSize)
      messageStack.removeFirst();

   static const QString timeFormat("yyyy-MM-dd hh:mm:ss");

   QString toolTip;
   QString history;
   for (const Message& message : std::as_const(messageStack))
   {
      toolTip += message.symbol + " " + message.text + "\n";

      if (addTimeStamp)
         history += message.symbol + " " + message.timeStamp.toString(timeFormat) + ": " + message.text + "\n";
      else
         history += message.symbol + " " + message.text + "\n";
   }

   historyDocument.setPlainText(history);

   if (showToolTip)
      setToolTip(toolTip);
}

void MessageLabel::print(const QString& text, bool isWarning)
{
   auto addMessage = [&](const QString& message, const QString& symbol, int length = -1)
   {
      setText(" " + symbol + " " + message);

      if (-1 == length)
         messageExpiration = QDateTime();
      else
         messageExpiration = QDateTime::currentDateTime().addMSecs(length);

      if (0 == stackSize)
         return;

      messageStack.append({QDateTime::currentDateTime(), symbol, message});
      updateStack();
   };

   if (isWarning)
   {
      setStyleSheet("QLabel{color: red; margin-right: 10px;}");
      addMessage(text, LogSymbol::Attention);
   }
   else
   {
      setStyleSheet("QLabel{margin-right: 10px;}");
      addMessage(text, LogSymbol::Info, 2000);
   }
}

void MessageLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
   setText("");
}
