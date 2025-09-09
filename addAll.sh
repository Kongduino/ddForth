#!/bin/sh
git add *.hpp *.cpp README.md tests/*.* Fonts/Roboto* assets/*.*
git commit -m "$1"
git push

