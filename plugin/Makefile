CPP=g++
CFLAGS=-O3 -fPIC
LDFLAGS=-ldl
DYLIB_SUFFIX=so
SHARED_CMD=-shared

plugin: plugin.cpp traversin.cpp ls.cpp lodepng AdafruitGFX QRencode
	g++ $(CFLAGS) -g -c traversin.cpp
	g++ $(SHARED_CMD) traversin.o lodepng/lodepng.o QR-Code-generator/cpp/qrcodegen.o -o traversin.$(DYLIB_SUFFIX)
	g++ $(CFLAGS) -std=c++17 -g -c ls.cpp
	g++ $(SHARED_CMD) ls.o -o ls.$(DYLIB_SUFFIX)
	rm *.o

lodepng:
	rm -rf lodepng
	git clone https://github.com/lvandeve/lodepng
	cd lodepng && g++ -fPIC -I ./ -W -Wall -Wextra -ansi -pedantic -O3 -c lodepng.cpp -o lodepng.o

AdafruitGFX:
	rm -rf Adafruit-GFX-Library
	git clone https://github.com/adafruit/Adafruit-GFX-Library
	./fontClean.sh

QRencode:
	rm -rf QR-Code-generator
	git clone https://github.com/nayuki/QR-Code-generator
	cd QR-code-generator/cpp && g++ -fPIC -std=c++11 -O3 -c -o qrcodegen.o -MMD -MF .deps/qrcodegen.d qrcodegen.cpp

clean:
	rm -f *.o *.$(DYLIB_SUFFIX)
	rm -rf plugin/lodepng
	rm -rf plugin/QR-code-generator
	rm -rf plugin/Adafruit-GFX-Library
