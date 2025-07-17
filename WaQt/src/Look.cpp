#include "Look.h"

#include <QFile>

void Look::applyStlyeSheet(const QString& fileName, QWidget* widget)
{
   QFile file(fileName);
   if (!file.open(QIODevice::ReadOnly))
      return;

   const QString styleSheet = file.readAll();
   widget->setStyleSheet(styleSheet);
   file.close();
}
