#!/bin/sh
make clean
python3 incrementVersion.py
git add *.hpp *.cpp README.md Tutorial.md server/*.*
git add tests/*.fs tests/*.sh Fonts/Roboto* assets/*.* Makefile addAll.sh *.py sdl_helpers/*.* in.sh
rm plugin/*.so
git add plugin/*.* plugin/Makefile
git commit -m "$1"
git push
echo "Making plugins"
cd plugin; make clean; make; cd ../
echo "Making ddForth"
make clean
make
