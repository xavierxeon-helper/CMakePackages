#!/bin/bash

HERE=$(dirname "$(readlink -f "$0")")

export XX_DOC_PATH=$HERE/documentation
doxygen XX.doxy
exit 0

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

cd $HERE
export XX_DOC_PATH=$TMP_DIR/xavierxeon.github.io/XX
doxygen XX.doxy

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
      echo "open docu.html in default browser"
      if [ $(uname) == "Darwin" ]
      then
         open "https://xavierxeon.github.io/XX/html/index.html"
      else
         xdg-open "https://xavierxeon.github.io/XX/html/index.html"
      fi
   fi
else
   echo "(no user input)"
fi