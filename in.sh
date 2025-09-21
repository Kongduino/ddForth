#!/bin/sh
install_name_tool -add_rpath /usr/local/lib bin/ddforth_SDL
install_name_tool -add_rpath /usr/local/lib bin/ddforth_SDL_debug
rm bin/*.o
