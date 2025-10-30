CPP=g++
CFLAGS=-O3 -rdynamic
LDFLAGS=-ldl

plugin: plugin.cpp traversin.cpp qrencode.cpp ls.cpp
	g++ -O3 -g -c traversin.cpp
	g++ -dynamiclib traversin.o lodepng/lodepng.o QR-Code-generator/cpp/qrcodegen.o -o traversin.dylib
	g++ -O3 -std=c++17 -g -c ls.cpp
	g++ -dynamiclib ls.o -o ls.dylib
	rm *.o

clean:
	rm -f *.o *.dylib
