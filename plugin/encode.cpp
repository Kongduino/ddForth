#include "lodepng/lodepng.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>

using namespace std;

/*
Example 1
Encode from raw pixels to disk with a single function call
The image argument has width * height RGBA pixels or width * height * 4 bytes
*/
void encodeOneStep(const char* filename, const unsigned char* image, unsigned width, unsigned height) {
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename, image, width, height);
  /*if there's an error, display it*/
  if (error) printf("error %u: %s\n", error, lodepng_error_text(error));
}

bool handlePNGTest() {
  const char* filename = "test.png";
  /*generate some image*/
  unsigned width = 512, height = 512;
  unsigned char* image = (unsigned char*)malloc(width * height * 4);
  unsigned x, y;
  for (y = 0; y < height; y++)
    for (x = 0; x < width; x++) {
      image[4 * width * y + 4 * x + 1] = x ^ y;
      image[4 * width * y + 4 * x + 2] = x | y;
      image[4 * width * y + 4 * x + 0] = 255 * !(x & y);
      image[4 * width * y + 4 * x + 3] = 255;
    }
  encodeOneStep(filename, image, width, height);
  free(image);
  return true;
}

struct nativeCommand {
  bool (*ptr)(void); // Function pointer
  string name;
  string help;
};

nativeCommand pluginCommands[] = {
  { handlePNGTest, "PNGTest", "( -- ) Creates a PNG." },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(nativeCommand);
