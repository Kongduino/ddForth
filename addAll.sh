#!/bin/sh
python3 incrementVersion.py
git add *.hpp *.cpp README.md Tutorial.md
git add tests/*.* Fonts/Roboto* assets/*.* Makefile addAll.sh *.py sdl_helpers/*.* in.sh
git add esp32v4_ddforth/*.* cardputer_ddforth/*.* cardputer_ddforth/data/*.* 
git commit -m "$1"
git push
make clean
make
