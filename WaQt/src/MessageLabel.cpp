
#include "MessageLabel.h"

#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QToolTip>

#include "LogSymbol.h"

MessageLabel::MessageLabel(QWidget* parent, int stackSize)
   : QLabel(parent)
   , Logger::Target(stackSize)
   , showToolTip(true)
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

void MessageLabel::setShowToolTip(bool newShowToolTip)
{
   showToolTip = newShowToolTip;
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

void MessageLabel::update(const Entry::Buffer& buffer)
{
   static const QColor neutral(Qt::black);

   QString toolTip;

   for (int index = 0; index < buffer.size(); index++)
   {
      const Entry& entry = buffer.at(index);
      const QString symbol = (entry.color == neutral) ? LogSymbol::Info : LogSymbol::Warning;

      const QString message = symbol + " " + entry.text;
      toolTip += message + "\n";

      if (index + 1 == buffer.size())
         setText(message);
   }

   if (showToolTip)
      setToolTip(toolTip);
}

void MessageLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
   setText("");
}
