#include "Info.h"

#include <QMap>

#include <QSysInfo>

QString Info::getHostName()
{
   static const QString hostName = []()
   {
      QString hostName = QSysInfo::machineHostName();

      size_t index = hostName.indexOf('.');
      if (index != -1)
         hostName = hostName.left(index);

      return hostName;
   }();

   return hostName;
}

QString Info::whatCppStandard()
{
   static const QMap<long, QString> versionMap =
      {
         // clang-format: off
         {1L, "pre-standard C++"},
         {199711L, "C++98"},
         {201103L, "C++11"},
         {201402L, "C++14"},
         {201703L, "C++17"},
         {201707L, "C++20 clang"},
         {202002L, "C++20"}
         // clang-format: on
      };

   if (!versionMap.contains(__cplusplus))
      return QString("Unkown C++ standard:") + QString::number(__cplusplus) + QString("L");
   else
      return versionMap[__cplusplus];
}
