CPP=g++
CFLAGS=-O3 -rdynamic
LDFLAGS=-Wl -ldl

plugin: foo.cpp plugin.cpp
	g++ -g -c plugin.cpp
	g++ -dynamiclib plugin.o -o plugin.dylib
	g++ -o foo foo.cpp
	rm *.o

clean:
	rm *.o *.dylib foo
