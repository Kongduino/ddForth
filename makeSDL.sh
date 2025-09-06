#!/bin/sh
g++ -g -c ddforth_sdl.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
g++ -o sdl_test ddforth_sdl.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
install_name_tool -add_rpath /usr/local/lib sdl_test
rm -f ddforth_sdl.o

g++ -g -c ddforth_sdl.cpp -DDEBUG -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
g++ -o sdl_test_debug ddforth_sdl.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
install_name_tool -add_rpath /usr/local/lib sdl_test_debug
rm -f ddforth_sdl.o
