#!/bin/sh
install_name_tool -add_rpath /usr/local/lib ddforth_SDL_debug
rm *.o
