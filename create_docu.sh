#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

doxygen CMakePackage.doxy

cd $HERE/documentation/latex
make

cp $HERE/documentation/latex/refman.pdf $HERE/CMakePackage.pdf