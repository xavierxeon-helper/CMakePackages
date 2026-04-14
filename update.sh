#!/bin/bash

if [[ -f /proc/version && $(grep -i Microsoft /proc/version) && $1 != "--wsl" ]]
then
   cmd.exe /c "windows_msvc_update.bat"
   exit 0
fi

PLATFORM=$(uname -ms)
PLATFORM_RASPI="Linux aarch64"

if [ "$PLATFORM" == "$PLATFORM_RASPI" ]
then   
   echo "Running on Raspberry Pi, do not use parallel build"
else   
   PARALLEL_BUILD=--parallel
fi

HERE=$(dirname "$(readlink -f "$0")")

mkdir -p $HERE/build/unix_debug
cd $HERE/build/unix_debug
cmake $HERE -DCMAKE_BUILD_TYPE=Debug

cmake --build . $PARALLEL_BUILD --config Debug

mkdir -p $HERE/build/unix_release
cd $HERE/build/unix_release
cmake $HERE -DCMAKE_BUILD_TYPE=Release

cmake --build . $PARALLEL_BUILD --config Release
