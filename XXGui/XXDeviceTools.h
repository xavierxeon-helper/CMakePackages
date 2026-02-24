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
         iPadPro13,
         NoteAir5C
      };
      Q_ENUM(DeviceIdentifier)

   public:
      static QSize getSize(const DeviceIdentifier& deviceId);
      static void fixSize(QQmlApplicationEngine* engine, const DeviceIdentifier& deviceId);
      static void fixSize(QWindow* window, const DeviceIdentifier& deviceId);

      static void forceDisplayMode(bool light = true);
   };
} // namespace XX

// does not work when encapsulated in function!
#ifdef Q_OS_WINDOWS
#define ENABLE_WINDOWS_CONSOLE                      \
   if (AttachConsole(ATTACH_PARENT_PROCESS))        \
   {                                                \
      FILE* fpstdout = stdout;                      \
      freopen_s(&fpstdout, "CONOUT$", "w", stdout); \
      FILE* fpstderr = stderr;                      \
      freopen_s(&fpstderr, "CONOUT$", "w", stderr); \
   }
#else
#define ENABLE_WINDOWS_CONSOLE
#endif // Q_OS_WINDOWS

#endif // NOT XXDeviceToolsH
