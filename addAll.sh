#!/bin/sh
python3 incrementVersion.py
git add *.hpp *.cpp README.md tests/*.* Fonts/Roboto* assets/*.* Makefile addAll.sh *.py  esp32v4_ddforth/*.* cardputer_ddforth/*.*
git commit -m "$1"
git push
make clean
make

