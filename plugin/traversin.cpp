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
  encodeOneStep(filename, image, width, height);
  free(image);
  return true;
}

bool handleCreateImage(vector<string>P) {
  if (P.size() != 3) {
    cout << "handleCreateImage: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string name = P.at(0);
  // cout << "\t. Name: " << name << endl;
  int height = std::atoi(P.at(1).c_str());
  // cout << "\t. Height: " << height << endl;
  int width = std::atoi(P.at(2).c_str());
  // cout << "\t. Width: " << height << endl;
  // cout << "\t--------------------" << endl;
  // cout << "Looking for image " << name << endl;
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    // cout << "Image unknown! Perfect...\n";
    std::vector<uint8_t> blob(width * height * 4, 0);
    // cout << "Created blob...\n";
    myImages[name] = blob;
    // cout << "Saved blob...\n";
    blob.clear();
  } else {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s already exists!\n", name.c_str());
    cout << msg;
    return false;
  }
  return true;
}

bool handleDrawPixel(vector<string>P) {
  // w h x y r g b a name PIXEL
  if (P.size() != 9) {
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
  int height = std::atoi(P.at(7).c_str());
  int width = std::atoi(P.at(8).c_str());
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
  vector<uint8_t> image = myImages[name];
  int position = y * width * 4 + x * 4;
  image[position++] = r;
  image[position++] = g;
  image[position++] = b;
  image[position++] = a;
  myImages[name] = image;
  return true;
}

bool handleClearImage(vector<string>P) {
  // w h r g b name FILL
  if (P.size() != 6) {
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
  int height = std::atoi(P.at(4).c_str());
  int width = std::atoi(P.at(5).c_str());
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
  vector<uint8_t> image = myImages[name];
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
  // w h name path SAVEPNG
  if (P.size() != 4) {
    cout << "handleSavePNG: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string path = P.at(0);
  string name = P.at(1);
  // cout << "\t. Path: " << path << endl;
  // cout << "\t. Name: " << name << endl;
  int height = std::atoi(P.at(2).c_str());
  int width = std::atoi(P.at(3).c_str());
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
  vector<uint8_t> image = myImages[name];
  encodeOneStep(path.c_str(), image.data(), width, height);
  return true;
}

struct pluginCommand {
  bool (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
};

pluginCommand pluginCommands[] = {
  { handlePNGTest, "PNGTest", "0( -- ) Creates a PNG." },
  { handleCreateImage, "IMAGE", "3SII( w h s -- ) Creates a blank image." },
  { handleDrawPixel, "PIXEL", "9SIIIIIIII( w h x y r g b a s -- ) Draws an RGBA pixel." },
  { handleSavePNG, "SAVEPNG", "4SSII( w h s p -- ) Saves Image s to path p." },
  { handleClearImage, "FILLIMG", "6SIIIII( w h r g b s -- ) Fills Image s with rgb." },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
