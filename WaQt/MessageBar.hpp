#ifndef MessageBarHPP
#define MessageBarHPP

#include "MessageBar.h"


inline MessageBar::MessageBar(QWidget* parent)
   : QStatusBar(parent)
   , Logger()
{
   setSizeGripEnabled(false);


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
