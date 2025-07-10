
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
   , messageStack()
   , messageExpiration()
{
   setMinimumSize(QSize(50, 20));
   setFrameShape(QFrame::Panel);
   setFrameShadow(QFrame::Sunken);

   installEventFilter(this);

   QTimer* messageTimer = new QTimer(this);
   connect(messageTimer, &QTimer::timeout, this, &MessageLabel::slotUpdateTimeout);
   messageTimer->setInterval(1000);
   messageTimer->start();
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

      messageStack.append(symbol + " " + message);
      while (messageStack.size() > stackSize)
         messageStack.removeFirst();

      setToolTip(messageStack.join("\n"));
   };

   if (isWarning)
   {
      setStyleSheet("QLabel{color: red; margin-right: 10px;}");
      toolTip();
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
