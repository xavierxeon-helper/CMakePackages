#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

cd $HERE
doxygen CMakePackage.doxy

#cd $HERE/documentation/latex
#make
#cp $HERE/documentation/latex/refman.pdf $HERE/CMakePackage.pdf
#cd $HERE
