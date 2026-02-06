#!/bin/bash

if [[ -f /proc/version && $(grep -i Microsoft /proc/version) ]]
then
   cmd.exe /c "windows_update.bat"
   exit 0
fi

PLATFORM=$(uname -ms)
echo "Platform: $PLATFORM"

PLATFORM_RASPI="armv7l GNU/Linux"
echo "Platform: $PLATFORM_RASPI"
exit 0

HERE=$(dirname "$(readlink -f "$0")")

mkdir -p $HERE/build/cmd_line_debug
cd $HERE/build/cmd_line_debug
cmake  $HERE  -DCMAKE_BUILD_TYPE=Debug
cmake --build . --parallel --config Debug

mkdir -p $HERE/build/cmd_line_release
cd $HERE/build/cmd_line_release
cmake  $HERE  -DCMAKE_BUILD_TYPE=Release
cmake --build . --parallel --config Release


