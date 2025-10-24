#include <cmath> // For sin, cos, tan
#include "lodepng/lodepng.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <map>

using namespace std;

char msg[256];
std::map<string, vector<uint8_t>> myImages;
std::map<string, vector<int>> myImageSizes;

//Decode from disk to raw pixels with a single function call
bool decodeOneStep(string filename, string name) {
  vector<unsigned char> image; //the raw pixels
  vector<int> size;
  unsigned width, height;
unsigned error = lodepng::decode(image, width, height, filename.c_str());
  if (error) {
    std::cout << "decodeOneStep: Error " << error << ": " << lodepng_error_text(error) << std::endl;
    return false;
  }
  //the pixels are now in the vector "image", 4 bytes per pixel, ordered RGBARGBA..., use it as texture, draw it, ...
  myImages[name] = image;
  size.push_back(height);
  size.push_back(width);
  myImageSizes[name] = size;
  return true;
}

bool encodeOneStep(string filename, const unsigned char* image, unsigned width, unsigned height) {
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename.c_str(), image, width, height);
  /*if there's an error, display it*/
  if (error) {
    printf("error %u: %s\n", error, lodepng_error_text(error));
    return false;
  }
  return true;
}

bool handleCreateImage(vector<string>P) {
  if (P.size() != 3) {
    cout << "handleCreateImage: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  int height = std::atoi(P.at(1).c_str());
  int width = std::atoi(P.at(2).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    std::vector<uint8_t> blob(width * height * 4, 0);
    myImages[name] = blob;
    std::vector<int> blobSize;
    blobSize.push_back(height);
    blobSize.push_back(width);
    myImageSizes[name] = blobSize;
    // No need for the user to pass that info every time!
    blob.clear();
  } else {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s already exists!\n", name.c_str());
    cout << msg;
    return false;
  }
  return true;
}

bool handlePNGTest(vector<string>P) {
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
  bool rslt = encodeOneStep(filename, image, width, height);
  free(image);
  return rslt;
}

bool handleDrawPixel(vector<string>P) {
  // x y r g b a name PIXEL
  if (P.size() != 7) {
    cout << "handleDrawPixel: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string name = P.at(0);
  // cout << "\t. Name: " << name << endl;
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int y = std::atoi(P.at(5).c_str());
  int x = std::atoi(P.at(6).c_str());
  // cout << "\t. RGB: " << (int)r << ", "  << (int)g << ", "  << (int)b << ", "  << (int)a << endl;
  // cout << "\t. XY: " << x << ", "  << y << endl;
  // cout << "\t. WH: " << width << ", "  << width << endl;
  // cout << "\t--------------------" << endl;
  // cout << "Looking for image " << name << endl;
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position = y * width * 4 + x * 4;
  image[position++] = r;
  image[position++] = g;
  image[position++] = b;
  image[position++] = a;
  myImages[name] = image;
  return true;
}

bool handleDrawRect(vector<string>P) {
  // x y L H r g b a name RECT
  if (P.size() != 9) {
    cout << "handleDrawRect: Invalid number of args: " << P.size() << "!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int H = std::atoi(P.at(5).c_str());
  int L = std::atoi(P.at(6).c_str());
  int y = std::atoi(P.at(7).c_str());
  int x = std::atoi(P.at(8).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position;
  position = (y) * width * 4 + x * 4;
  for (int ix = 0; ix < L; ix++) {
    image[position++] = r;
    image[position++] = g;
    image[position++] = b;
    image[position++] = a;
    if ((x + ix) >= width)
      ix = L;
  }
  if ((y + H - 1) < height) {
    position = (y + H - 1) * width * 4 + x * 4;
    for (int ix = 0; ix < L; ix++) {
      image[position++] = r;
      image[position++] = g;
      image[position++] = b;
      image[position++] = a;
      if ((x + ix) >= width)
        ix = L;
    }
  }
  for (int jx = 1; jx < H - 1; jx++) {
    position = (y + jx) * width * 4 + x * 4;
    image[position++] = r;
    image[position++] = g;
    image[position++] = b;
    image[position++] = a;
    if ((x + L - 1) < width) {
      position = (y + jx) * width * 4 + (x + L - 1) * 4;
      image[position++] = r;
      image[position++] = g;
      image[position++] = b;
      image[position++] = a;
    }
    if ((y + jx) >= height)
      jx = H;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawHLine(vector<string>P) {
  // x y L r g b a name HLINE
  if (P.size() != 8) {
    cout << "handleDrawHLine: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int L = std::atoi(P.at(5).c_str());
  int y = std::atoi(P.at(6).c_str());
  int x = std::atoi(P.at(7).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position = y * width * 4 + x * 4;
  for (int ix = 0; ix < L; ix ++) {
    image[position++] = r;
    image[position++] = g;
    image[position++] = b;
    image[position++] = a;
    if ((x + ix) >= width)
      ix = L;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawVLine(vector<string>P) {
  // x y H r g b a name VLINE
  if (P.size() != 8) {
    cout << "handleDrawVLine: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int H = std::atoi(P.at(5).c_str());
  int y = std::atoi(P.at(6).c_str());
  int x = std::atoi(P.at(7).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position;
  for (int ix = 0; ix < H; ix ++) {
    position = (y + ix) * width * 4 + x * 4;
    image[position++] = r;
    image[position++] = g;
    image[position++] = b;
    image[position++] = a;
    if ((y + ix) >= height)
      ix = H;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawCircle(vector<string>P) {
  // x y radius r g b a name CIRCLE
  if (P.size() != 8) {
    cout << "handleDrawCircle: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int radius = std::atoi(P.at(5).c_str());
  int y = std::atoi(P.at(6).c_str());
  int x = std::atoi(P.at(7).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position;
  for (double angle=0; angle<=2*3.141592653; angle+=0.001) {
    //You are using radians so you will have to increase by a very small amount
    //This will have the coordinates you want to draw a point at
    int px = x + radius * std::cos(angle);
    int py = y + radius * std::sin(angle);
    if (py < height && px < width) {
      position = py * width * 4 + px * 4;
      image[position++] = r;
      image[position++] = g;
      image[position++] = b;
      image[position++] = a;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleClearImage(vector<string>P) {
  // w h r g b name FILL
  if (P.size() != 4) {
    cout << "handleClearImage: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string name = P.at(0);
  // cout << "\t. Name: " << name << endl;
  uint8_t b = std::atoi(P.at(1).c_str());
  uint8_t g = std::atoi(P.at(2).c_str());
  uint8_t r = std::atoi(P.at(3).c_str());
  // cout << "\t. RGBA: " << (int)r << ", "  << (int)g << ", "  << (int)b << endl;
  // cout << "\t. WH: " << width << ", "  << width << endl;
  // cout << "\t--------------------" << endl;
  // cout << "Looking for image " << name << endl;
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  int position = 0;
  for (int jx = 0; jx < height; jx++) {
    for (int ix = 0; ix < width; ix++) {
      image.at(position++) = r;
      image.at(position++) = g;
      image.at(position++) = b;
      image.at(position++) = 255;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleSavePNG(vector<string>P) {
  // name path SAVEPNG
  if (P.size() != 2) {
    cout << "handleSavePNG: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string path = P.at(0);
  string name = P.at(1);
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  bool rslt = encodeOneStep(path, image.data(), width, height);
  return rslt;
}

bool handleLoadPNG(vector<string>P) {
  // name path LOADPNG
  if (P.size() != 2) {
    cout << "handleLoadPNG: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string path = P.at(0);
  string name = P.at(1);
  bool rslt = decodeOneStep(path, name);
  if (!rslt) return false;
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  return rslt;
}

struct pluginCommand {
  bool (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
};

pluginCommand pluginCommands[] = {
  { handlePNGTest, "PNGTest", "0( -- ) Creates a PNG." },
  { handleCreateImage, "IMAGE", "3SII( w h s -- ) Creates a blank image." },
  { handleDrawPixel, "PIXEL", "7SIIIIII( w h x y r g b a s -- ) Draws an RGBA pixel." },
  { handleDrawHLine, "HLINE", "8SIIIIIII( x y L H r g b a name -- ) Draws an RGBA horizontal line length L." },
  { handleDrawVLine, "VLINE", "8SIIIIIII( L x y r g b a s -- ) Draws an RGBA horizontal line length L." },
  { handleDrawCircle, "CIRCLE", "8SIIIIIII( w h x y radius r g b a s -- ) Draws an RGBA circle radius rad at x,y." },
  { handleDrawRect, "RECT", "9SIIIIIIII( L H x y r g b a s -- ) Draws an RGBA Box width L height H." },
  { handleSavePNG, "SAVEPNG", "2SS( s p -- ) Saves Image s to path p." },
  { handleLoadPNG, "LOADPNG", "2SS( s p -- ) Loads Image at path p as s." },
  { handleClearImage, "FILLIMG", "4SIII( r g b s -- ) Fills Image s with rgb." },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
