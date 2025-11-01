CPP=g++
CFLAGS=-O3 -fPIC
LDFLAGS=-ldl
DYLIB_SUFFIX=so
SHARED_CMD=-shared

plugin: plugin.cpp traversin.cpp ls.cpp
	g++ $(CFLAGS) -g -c traversin.cpp
	g++ $(SHARED_CMD) traversin.o lodepng/lodepng.o QR-Code-generator/cpp/qrcodegen.o -o traversin.$(DYLIB_SUFFIX)
	g++ $(CFLAGS) -std=c++17 -g -c ls.cpp
	g++ $(SHARED_CMD) ls.o -o ls.$(DYLIB_SUFFIX)
	rm *.o

clean:
	rm -f *.o *.$(DYLIB_SUFFIX)