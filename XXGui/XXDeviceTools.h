#ifndef XXDeviceToolsH
#define XXDeviceToolsH

#include "XXGuiExportDef.h"
#include <QObject>

#ifdef Q_OS_WINDOWS
#include <windows.h>
#endif

#include <QQmlApplicationEngine>
#include <QSize>
#include <QWindow>

namespace XX
{
   //! @brief tools for device specific features
   //! @ingroup XXGui

   class XXGUI_DECLSPEC DeviceTools
   {
      Q_GADGET

   public:
      enum DeviceIdentifier
      {
         iPadMini,
         iPadPro13
      };
      Q_ENUM(DeviceIdentifier)

   public:
      static QSize getSize(const DeviceIdentifier& deviceId);
      static void fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId);
      static void fixSize(QWindow* window, const DeviceIdentifier& deviceId);

      static void forceDisplayMode(bool light = true);
      static void enableWindowsConsole();
   };
} // namespace XX

#ifndef XXDeviceToolsHPP
#include "XXDeviceTools.hpp"
#endif // NOT XXDeviceToolsHPP

#endif // NOT XXDeviceToolsH
