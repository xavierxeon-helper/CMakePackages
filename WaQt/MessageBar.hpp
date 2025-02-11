#ifndef MessageBarHPP
#define MessageBarHPP

#include "MessageBar.h"

#include <QTimer>
#include <QEvent>
#include <QMouseEvent>
#include <QToolTip>

#include "LogSymbol.h"

inline MessageBar::MessageBar(QWidget* parent, int stackSize)
   : QStatusBar(parent)
   , Logger()
   , messageLabel(nullptr)
   , stackSize(stackSize)
   , messageStack()
   , messageExpiration()
{
   setSizeGripEnabled(false);

   messageLabel = new QLabel(this);
   messageLabel->setMinimumWidth(50);
   messageLabel->setFrameShape(QFrame::Panel);
   messageLabel->setFrameShadow(QFrame::Sunken);

   messageLabel->installEventFilter(this);
   addPermanentWidget(messageLabel);

   QTimer* messageTimer = new QTimer(this);
   connect(messageTimer, &QTimer::timeout, this, &MessageBar::slotUpdateTimeout);

   messageTimer->setInterval(1000);
   messageTimer->start();

}

inline void MessageBar::slotUpdateTimeout()
{
   if(messageExpiration.isNull())
      return;

   if(QDateTime::currentDateTime() < messageExpiration)
      return;

   messageExpiration = QDateTime();
   messageLabel->setText("");
}

inline void MessageBar::print(const QString& text, bool isWarning)
{
   auto addMessage = [&](const QString& message, const QString& symbol, int length = -1)
   {
      messageLabel->setText(message + " " + symbol);

      if(0 == stackSize)
         return;

      messageStack.append(symbol + " " + message);
      while(messageStack.size() > stackSize)
         messageStack.removeFirst();

      if(-1 == length)
         messageExpiration = QDateTime();
      else
         messageExpiration = QDateTime::currentDateTime().addMSecs(length);

      messageLabel->setToolTip(messageStack.join("\n"));
   };

   if (isWarning)
   {
      messageLabel->setStyleSheet("QLabel{color: red; margin-right: 10px;}");
      messageLabel->toolTip();
      addMessage(text, LogSymbol::Attention);
   }
   else
   {
      messageLabel->setStyleSheet("QLabel{margin-right: 10px;}");
      addMessage(text, LogSymbol::Info, 2000);
   }
}

inline bool MessageBar::eventFilter(QObject* obj, QEvent* event)
{
   if(obj == messageLabel)
   {
      if(QEvent::MouseButtonDblClick == event->type())
         messageLabel->setText("");
   }
   return QStatusBar::eventFilter(obj, event);
}

#endif // NOT MessageBarHPP
