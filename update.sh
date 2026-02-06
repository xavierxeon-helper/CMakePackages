#!/bin/bash

if [[ -f /proc/version && $(grep -i Microsoft /proc/version) ]]
then
   cmd.exe /c "windows_update.bat"
   exit 0
fi

PLATFORM=$(uname -ms)
PLATFORM_RASPI="Linux aarch64"

if [ "$PLATFORM" == "$PLATFORM_RASPI" ]
then
   echo "Running on Raspberry Pi, do not use parallel build"
fi

HERE=$(dirname "$(readlink -f "$0")")

mkdir -p $HERE/build/cmd_line_debug
cd $HERE/build/cmd_line_debug
cmake  $HERE  -DCMAKE_BUILD_TYPE=Debug

if [ "$PLATFORM" == "$PLATFORM_RASPI" ]
then
    cmake --build . --config Debug
else
   cmake --build . --parallel --config Debug
fi

mkdir -p $HERE/build/cmd_line_release
cd $HERE/build/cmd_line_release
cmake  $HERE  -DCMAKE_BUILD_TYPE=Release

if [ "$PLATFORM" == "$PLATFORM_RASPI" ]
then
    cmake --build . --config Release
else
   cmake --build . --parallel --config Release
fi

