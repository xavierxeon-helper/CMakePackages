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

PDF_TEST=$(which pdflatex)
if [ ! -z "$PDF_TEST" ]; then
   cd $HERE
   doxygen CMakePackage.doxy
   cd $HERE/documentation/latex
   make
   cp $HERE/documentation/latex/refman.pdf $HERE/CMakePackage.pdf
fi

cd $HERE
