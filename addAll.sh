#!/bin/sh
python3 incrementVersion.py
git add *.hpp *.cpp README.md Tutorial.md server/*.*
git add tests/*.fs tests/*.sh Fonts/Roboto* assets/*.* Makefile addAll.sh *.py sdl_helpers/*.* in.sh
git add esp32v4_ddforth/*.* cardputer_ddforth/*.* cardputer_ddforth/data/*.* 
git add plugin/*.cpp plugin/Makefile plugin/README
git commit -m "$1"
git push
make clean
make
