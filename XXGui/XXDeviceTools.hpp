#ifndef XXDeviceToolsHPP
#define XXDeviceToolsHPP

#include "XXDeviceTools.h"

// needs to be inline to function!
inline void XX::DeviceTools::enableWindowsConsole()
{
#ifdef Q_OS_WINDOWS
   if (AttachConsole(ATTACH_PARENT_PROCESS))
   {
      FILE* fpstdout = stdout;
      freopen_s(&fpstdout, "CONOUT$", "w", stdout);

      FILE* fpstderr = stderr;
      freopen_s(&fpstderr, "CONOUT$", "w", stderr);
   }
#endif
}

#endif // NOT XXDeviceToolsHPP
