CPP=g++
CFLAGS=-O3 -rdynamic
LDFLAGS=-ldl

plugin: foo.cpp plugin.cpp
	g++ -O3 -g -c encode.cpp
	g++ -dynamiclib encode.o lodepng/lodepng.o -o encode.dylib
	g++ -O3 $(CFLAGS) foo.cpp -o foo $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o *.dylib foo
