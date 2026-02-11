#include "XXLook.h"

#include <QApplication>
#include <QFile>

void Look::applyStlyeSheet(const QString& fileName, QWidget* widget)
{
   QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly))
      return;

   const QString styleSheet = file.readAll();
   file.close();

   widget->setStyleSheet(styleSheet);
}

void Look::doNotShowMenuIcons()
{
   if (!QApplication::instance())
   {
      qWarning() << __FUNCTION__ << ": No QApplication instance exists!";
      return;
   }
   QApplication::setAttribute(Qt::AA_DontShowIconsInMenus, true);
}

void Look::forceAppMenuBar()
{
   QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar, true);
}
