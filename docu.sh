#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

ROOT_DIR=~/tmp/

if [ ! -d $ROOT_DIR/xavierxeon.github.io ]
then
  cd $ROOT_DIR
  git clone git@github.com:xavierxeon/xavierxeon.github.io.git
fi

cd $HERE
export WATOOLS_DOC_PATH=$ROOT_DIR/xavierxeon.github.io/WaTools
doxygen WaTools.doxy

cd $ROOT_DIR/xavierxeon.github.io
git add *
git commit -m "Update documentation"
git push