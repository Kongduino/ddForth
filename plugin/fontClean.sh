#!/bin/sh
perl -pi -e 's/^#include /\/\/#include /' Adafruit-GFX-Library/Fonts/*.h
perl -pi -e 's/\] PROGMEM = \{/\] = \{/' Adafruit-GFX-Library/Fonts/*.h
