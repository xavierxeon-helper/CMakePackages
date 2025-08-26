#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

cd $HERE
doxygen WaTools.doxy

echo "create PDF (y/N)?"
read CREATE_PDF
if [ "$CREATE_PDF" == "y" ] 
then
   cd $HERE/documentation/latex
   make

   cp $HERE/documentation/latex/refman.pdf $HERE/documentation/WaTools.pdf
   cd $HERE
fi

