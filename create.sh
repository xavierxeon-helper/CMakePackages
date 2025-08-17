#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

mkdir -p $HERE/build/cmd_line_release
cd $HERE/build/cmd_line_release
cmake  $HERE -DCMAKE_BUILD_TYPE=Release
make

mkdir -p $HERE/build/cmd_line_debug
cd $HERE/build/cmd_line_debug
cmake $HERE -DCMAKE_BUILD_TYPE=Debug
make

cd $HERE
