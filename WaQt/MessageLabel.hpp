#ifndef MessageLabelHPP
#define MessageLabelHPP

#include "MessageLabel.h"

#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QToolTip>

#include "LogSymbol.h"

inline MessageLabel::MessageLabel(QWidget* parent, int stackSize)
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

inline void MessageLabel::slotUpdateTimeout()
{
   if(messageExpiration.isNull())
      return;

   if(QDateTime::currentDateTime() < messageExpiration)
      return;

   messageExpiration = QDateTime();
   setText("");
}

inline void MessageLabel::print(const QString& text, bool isWarning)
{
   auto addMessage = [&](const QString& message, const QString& symbol, int length = -1)
   {
      setText(message + " " + symbol);

      if(0 == stackSize)
         return;

      messageStack.append(symbol + " " + message);
      while(messageStack.size() > stackSize)
         messageStack.removeFirst();

      if(-1 == length)
         messageExpiration = QDateTime();
      else
         messageExpiration = QDateTime::currentDateTime().addMSecs(length);

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

inline bool MessageLabel::eventFilter(QObject* obj, QEvent* event)
{
   if(obj == this)
   {
      if(QEvent::MouseButtonDblClick == event->type())
         setText("");
   }
   return true;
}

#endif // NOT MessageLabelHPP
