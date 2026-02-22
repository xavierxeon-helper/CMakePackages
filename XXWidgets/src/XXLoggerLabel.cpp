
#include "XXLoggerLabel.h"

#include <QEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QToolTip>

#include "XXLogSymbol.h"

XX::LoggerLabel::LoggerLabel(QWidget* parent, int stackSize)
   : QLabel(parent)
   , Logger::Target(stackSize)
   , showToolTip(true)
   , messageExpiration()
{
   setMinimumSize(QSize(50, 20));
   setFrameShape(QFrame::NoFrame);
   setFrameShadow(QFrame::Plain);

   QTimer* messageTimer = new QTimer(this);
   connect(messageTimer, &QTimer::timeout, this, &LoggerLabel::slotUpdateTimeout);
   messageTimer->setInterval(1000);
   messageTimer->start();
}

void XX::LoggerLabel::setShowToolTip(bool newShowToolTip)
{
   showToolTip = newShowToolTip;
}

void XX::LoggerLabel::slotUpdateTimeout()
{
   if (messageExpiration.isNull())
      return;

   if (QDateTime::currentDateTime() < messageExpiration)
      return;

   messageExpiration = QDateTime();
   setText("");
}

void XX::LoggerLabel::update(const Entry::Buffer& buffer)
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

void XX::LoggerLabel::mouseDoubleClickEvent(QMouseEvent* event)
{
   setText("");
}
