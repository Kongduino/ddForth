# PLUGINS Extra Steps

Do this before making the main project.

## cURL

### Linux:

```
sudo apt-get install libcurl-dev #(will install the default alternative)
sudo apt-get install libcurl4-openssl-dev #(the OpenSSL variant)
sudo apt-get install libcurl4-gnutls-dev #(the gnutls variant)
```

### Mac OS X:

It should be pre-installed, If you want the latest:

```
brew install curl
```

## QR Encode

We only need that one bin.

```
git clone https://github.com/nayuki/QR-Code-generator
cd QR-Code-generator/cpp/
g++ -fPIC -std=c++11 -O3 -c -o qrcodegen.o -MMD -MF .deps/qrcodegen.d qrcodegen.cpp
cd ../../
```


## lodepng

We only need that one bin. plugin.hpp uses `lodepng.o`.

```
git clone https://github.com/lvandeve/lodepng
cd lodepng
g++ -fPIC -I ./ -W -Wall -Wextra -ansi -pedantic -O3 -c lodepng.cpp -o lodepng.o
```

## Adafruit-GFX

No compilation needed: we want the fonts.

```
git clone https://github.com/adafruit/Adafruit-GFX-Library
```

### In each font file:

* Comment out #include <Adafruit_GFX.h>:

```
//#include <Adafruit_GFX.h>
```

* Comment out (or remove) PROGMEM:

```
const uint8_t FreeMono...Bitmaps[] /* PROGMEM */ = {

const GFXglyph FreeMono...Glyphs[] /* PROGMEM */ = {
```
This can be achieved with the `fontClean.sh` command in the plugin folder:

```sh
#!/bin/sh
perl -pi -e 's/^#include /\/\/#include /' Adafruit-GFX-Library/Fonts/*.h
perl -pi -e 's/\] PROGMEM = \{/\] = \{/' Adafruit-GFX-Library/Fonts/*.h
```

I still love Perl a little...

`traversin.cpp` uses fonts. Here's how:

```
#include "Adafruit-GFX-Library/gfxfont.h"

#include "Adafruit-GFX-Library/Fonts/FreeMono18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeMonoBold18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeSansBold12pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeSans12pt7b.h"
```

Running `make` on Mac, or `make -f Makefile.linux` will build both traversin and ls:

The `handleInit` method is compulsory in any plugin, and will be called when loading the plugin. In `handleInit`, traversin makes sure they are listed and usable:

```
  // Map the fonts that are being used.
  myFonts["FreeMono18pt7b"] = FreeMono18pt7b;
  cout << "\t• FreeMono18pt7b" << endl;
  myFonts["FreeMonoBold18pt7b"] = FreeMonoBold18pt7b;
  cout << "\t• FreeMonoBold18pt7b" << endl;
  myFonts["FreeSansBold12pt7b"] = FreeSansBold12pt7b;
  cout << "\t• FreeSansBold12pt7b" << endl;
  myFonts["FreeSans12pt7b"] = FreeSans12pt7b;
  cout << "\t• FreeSans12pt7b" << endl;
  return true;
}
```

This has to be done manually for the moment. Other plugins could use the same strategy.

Run `test43` first (after getting and setting an API key, see [test43.md](../tests/test43.md)). It'll get you a `map.png` image. The next 2 tests use it. Just in case I put a copy in [assets](../assets/).

![map_text](../assets/map_text.png)

## Making

For Linux and Mac OS X `make` alone should work fine. It does, on my computers. :-)

```sh
~/ddForth/plugin$ make
g++ -O3 -fPIC -g -c traversin.cpp
g++ -shared traversin.o lodepng/lodepng.o QR-Code-generator/cpp/qrcodegen.o -o traversin.so
g++ -O3 -fPIC -std=c++17 -g -c ls.cpp
g++ -shared ls.o -o ls.so
rm *.o
```
On Ubuntu and Mac I get the same output.

## New in Plugins

### Traversin

* PIXEL? `( x y s -- r g b a )` Puts the RGBA value of a pixel on the stack.