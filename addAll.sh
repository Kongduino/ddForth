#!/bin/sh
python3 incrementVersion.py
git add *.hpp *.cpp README.md tests/*.* Fonts/Roboto* assets/*.* Makefile addAll.sh incrementVersion.py
git commit -m "$1"
git push

