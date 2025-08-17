#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

mkdir -p $HERE/build/release_cmd_line
cd $HERE/build/release_cmd_line
cmake .. -DCMAKE_BUILD_TYPE=Release
make

mkdir -p $HERE/build/debug_cmd_line
cd $HERE/build/debug_cmd_line
cmake .. -DCMAKE_BUILD_TYPE=Debug
make

cd $HERE
doxygen CMakePackage.doxy
cd $HERE/documentation/latex
make
cp $HERE/documentation/latex/refman.pdf $HERE/CMakePackage.pdf

cd $HERE
