CPP=g++
CFLAGS=-O3 -rdynamic
LDFLAGS=-ldl

plugin: foo.cpp plugin.cpp
	g++ -O3 -g -c traversin.cpp
	g++ -dynamiclib traversin.o lodepng/lodepng.o -o traversin.dylib
	g++ -O3 $(CFLAGS) foo.cpp -o foo $(LDFLAGS)
	rm *.o

clean:
	rm -f *.o *.dylib foo
