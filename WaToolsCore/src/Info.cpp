#include "Info.h"

#include <QSysInfo>

QString Info::getHostName()
{
   static const QString hostName = []()
   {
      QString hostName = QSysInfo::machineHostName();

      int index = hostName.indexOf('.');
      if (index != -1)
         hostName = hostName.left(index);

      return hostName;
   }();

   return hostName;
}