#!/bin/bash

export DOCU_ROOT=$(dirname "$(readlink -f "$0")")/..

TMP_DIR=~/tmp/
if [ ! -d $TMP_DIR ]
then
  echo "~/tmp directory does not exist, exiting"
  exit 1
fi

if [ ! -d $TMP_DIR/xavierxeon.github.io ]
then
  cd $TMP_DIR
  git clone git@github.com:xavierxeon/xavierxeon.github.io.git
fi

cd $DOCU_ROOT
export XX_DOC_PATH=$TMP_DIR/xavierxeon.github.io/XX 
doxygen docu/Doxyfile

cd $TMP_DIR/xavierxeon.github.io
git add *
git commit -m "Update documentation"
git push

echo ""
if read -t 5 -p "open in browser (y/N)? " OPEN_BROWSER
then
   if [ "$OPEN_BROWSER" == "y" ] 
   then
      echo ""
      echo "open docu in default browser"
      if [ $(uname) == "Darwin" ]
      then
         open "$XX_DOC_PATH/html/index.html"
      else
         xdg-open "$XX_DOC_PATH/html/index.html"
      fi
   fi
else
   echo "(no user input)"
fi