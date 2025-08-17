#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

PDF_TEST=$(which pdflatex)
if [ ! -z "$PDF_TEST" ]; then
   cd $HERE
   doxygen CMakePackage.doxy
   cd $HERE/documentation/latex
   make
   cp $HERE/documentation/latex/refman.pdf $HERE/CMakePackage.pdf
fi

cd $HERE
