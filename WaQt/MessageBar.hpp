#ifndef MessageBarHPP
#define MessageBarHPP

#include "MessageBar.h"

#include <QApplication>
#include <QTimer>

inline MessageBar* MessageBar::me = nullptr;

inline MessageBar::MessageBar(QWidget* parent)
   : QStatusBar(parent)
   , messageChannel(nullptr)
   , warningChannel(nullptr)
{
   me = this;

   auto printFunction = [&](bool isWarning)
   {
      return std::bind(&MessageBar::print, this, std::placeholders::_1, isWarning);
   };

   messageChannel = new IOChannel(this, printFunction(false));
   warningChannel = new IOChannel(this, printFunction(true));

   setSizeGripEnabled(false);
}

inline MessageBar::~MessageBar()
{
   me = nullptr;
}

inline QTextStream MessageBar::message()
{
   if (!me)
      return QTextStream();

   return me->messageChannel->stream();
}

inline QTextStream MessageBar::warning()
{
   if (!me)
      return QTextStream();

   return me->warningChannel->stream();
}

inline void MessageBar::print(const QString& text, bool isWarning)
{
   static const QString urgentSymbol = QString::fromUtf8("\u2622");
   if (isWarning)
   {
      setStyleSheet("color: red");
      showMessage(urgentSymbol + " " + text);
   }
   else
   {
      setStyleSheet("");
      showMessage(text, 2000);
   }
}

#endif // NOT MessageBarHPP
