#include <cmath>  // For sin, cos, tan
#include "lodepng/lodepng.h"
#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include "Adafruit-GFX-Library/gfxfont.h"
// Include the fonts you want
// comment out #include <Adafruit_GFX.h>
// Remove ` PROGMEM`
#include "Adafruit-GFX-Library/Fonts/FreeMono18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeMonoBold18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeSansBold12pt7b.h"

using namespace std;

char msg[256];
std::map<string, GFXfont> myFonts;
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

bool encodeOneStep(string filename, const unsigned char *image, unsigned width, unsigned height) {
  /*Encode the image*/
  unsigned error = lodepng_encode32_file(filename.c_str(), image, width, height);
  /*if there's an error, display it*/
  if (error) {
    printf("error %u: %s\n", error, lodepng_error_text(error));
    return false;
  }
  return true;
}

bool handleCreateImage(vector<string> P) {
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

bool handlePNGTest(vector<string> P) {
  const char *filename = "test.png";
  /*generate some image*/
  unsigned width = 512, height = 512;
  unsigned char *image = (unsigned char *)malloc(width * height * 4);
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

vector<uint8_t> putPixel(vector<uint8_t> image, int x, int y, int width, int r, int g, int b, int a) {
  int position = y * width * 4 + x * 4;
  image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
  position += 1;
  image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
  position += 1;
  image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
  position += 1;
  image[position] = (image[position] + a) / 2;
  position += 1;
  return image;
}

bool handleDrawPixel(vector<string> P) {
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
  image = putPixel(image, x, y, width, r, g, b, a);
  myImages[name] = image;
  return true;
}

bool handleFillRect(vector<string> P) {
  // x y L H r g b a name FILLRECT
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
  if ((x + L) >= width) L = width - x;
  if ((y + H) >= height) H = height - y;
  cout << "L: " << L << ", H: " << H << endl;
  for (int jx = 0; jx < H; jx++) {
    // line by line, calculate the start position
    int position = (y + jx) * width * 4 + x * 4;
    for (int ix = 0; ix < L; ix++) {
      // Draw a line
      image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
      position += 1;
      image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
      position += 1;
      image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
      position += 1;
      image[position] = (image[position] + a) / 2;
      position += 1;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleDrawRect(vector<string> P) {
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
  position = y * width * 4 + x * 4;
  for (int ix = 0; ix < L; ix++) {
    image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
    position += 1;
    image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
    position += 1;
    image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
    position += 1;
    image[position] = (image[position] + a) / 2;
    position += 1;
    if ((x + ix) >= width)
      ix = L;
  }
  if ((y + H - 1) < height) {
    position = (y + H - 1) * width * 4 + x * 4;
    for (int ix = 0; ix < L; ix++) {
      image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
      position += 1;
      image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
      position += 1;
      image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
      position += 1;
      image[position] = (image[position] + a) / 2;
      position += 1;
      if ((x + ix) >= width)
        ix = L;
    }
  }
  for (int jx = 1; jx < H - 1; jx++) {
    position = (y + jx) * width * 4 + x * 4;
    image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
    position += 1;
    image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
    position += 1;
    image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
    position += 1;
    image[position] = (image[position] + a) / 2;
    position += 1;
    if ((x + L - 1) < width) {
      position = (y + jx) * width * 4 + (x + L - 1) * 4;
      image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
      position += 1;
      image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
      position += 1;
      image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
      position += 1;
      image[position] = (image[position] + a) / 2;
      position += 1;
    }
    if ((y + jx) >= height)
      jx = H;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawHLine(vector<string> P) {
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
  for (int ix = 0; ix < L; ix++) {
    image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
    position += 1;
    image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
    position += 1;
    image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
    position += 1;
    image[position] = (image[position] + a) / 2;
    position += 1;
    if ((x + ix) >= width)
      ix = L;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawVLine(vector<string> P) {
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
  for (int ix = 0; ix < H; ix++) {
    position = (y + ix) * width * 4 + x * 4;
    image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
    position += 1;
    image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
    position += 1;
    image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
    position += 1;
    image[position] = (image[position] + a) / 2;
    position += 1;
    if ((y + ix) >= height)
      ix = H;
  }
  myImages[name] = image;
  return true;
}

bool handleDrawLine(vector<string> P) {
  // x1 y1 x2 y2 r g b a name DLINE
  if (P.size() != 9) {
    cout << "handleDrawVLine: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = std::atoi(P.at(1).c_str());
  uint8_t b = std::atoi(P.at(2).c_str());
  uint8_t g = std::atoi(P.at(3).c_str());
  uint8_t r = std::atoi(P.at(4).c_str());
  int y2 = std::atoi(P.at(5).c_str());
  int x2 = std::atoi(P.at(6).c_str());
  int y1 = std::atoi(P.at(7).c_str());
  int x1 = std::atoi(P.at(8).c_str());
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
  int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
  dx = x2 - x1;
  dy = y2 - y1;
  dx1 = fabs(dx);
  dy1 = fabs(dy);
  px = 2 * dy1 - dx1;
  py = 2 * dx1 - dy1;
  if (dy1 <= dx1) {
    if (dx >= 0) {
      x = x1;
      y = y1;
      xe = x2;
    } else {
      x = x2;
      y = y2;
      xe = x1;
    }
    image = putPixel(image, x, y, width, r, g, b, a);
    for (i = 0; x < xe; i++) {
      x = x + 1;
      if (px < 0) {
        px = px + 2 * dy1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          y = y + 1;
        } else {
          y = y - 1;
        }
        px = px + 2 * (dy1 - dx1);
      }
      image = putPixel(image, x, y, width, r, g, b, a);
    }
  } else {
    if (dy >= 0) {
      x = x1;
      y = y1;
      ye = y2;
    } else {
      x = x2;
      y = y2;
      ye = y1;
    }
    image = putPixel(image, x, y, width, r, g, b, a);
    for (i = 0; y < ye; i++) {
      y = y + 1;
      if (py <= 0) {
        py = py + 2 * dx1;
      } else {
        if ((dx < 0 && dy < 0) || (dx > 0 && dy > 0)) {
          x = x + 1;
        } else {
          x = x - 1;
        }
        py = py + 2 * (dx1 - dy1);
      }
      image = putPixel(image, x, y, width, r, g, b, a);
    }
  }
  myImages[name] = image;
  return true;
}

bool handleDrawCircle(vector<string> P) {
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
  for (double angle = 0; angle <= 2 * 3.141592653; angle += 0.001) {
    //You are using radians so you will have to increase by a very small amount
    //This will have the coordinates you want to draw a point at
    int px = x + radius * std::cos(angle);
    int py = y + radius * std::sin(angle);
    if (py < height && px < width) {
      position = py * width * 4 + px * 4;
      image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
      position += 1;
      image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
      position += 1;
      image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
      position += 1;
      image[position] = (image[position] + a) / 2;
      position += 1;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleClearImage(vector<string> P) {
  // r g b name FILL
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

bool handleNukeChannel(vector<string> P) {
  // [RGB] name X_CHANNEL
  if (P.size() != 2) {
    cout << "handleNukeChannel: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string name = P.at(0);
  string channel = P.at(1);
  if (channel != "R" && channel != "G" && channel != "B") {
    cout << "handleNukeChannel: Invalid Channel Name [RGB]!\n";
    return false;
  }
  int channelIndex = 0;
  if (channel == "G")
    channelIndex = 1;
  else if (channel == "B")
    channelIndex = 2;
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
      image.at(position + channelIndex) = 0;
      position += 4;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleGreyscale(vector<string> P) {
  // [RGB] name GREYSCALE
  if (P.size() != 1) {
    cout << "handleGreyscale: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  // cout << "\t--------------------" << endl;
  string name = P.at(0);
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
      uint8_t col = 0.299 * image.at(position) + 0.587 * image.at(position + 1) + 0.114 * image.at(position + 2);
      image.at(position++) = col;
      image.at(position++) = col;
      image.at(position) = col;
      position += 2;
    }
  }
  myImages[name] = image;
  return true;
}

bool handleSavePNG(vector<string> P) {
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

bool handleLoadPNG(vector<string> P) {
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

bool handleFontInfo(vector<string> P) {
  // font FONTINFO
  if (P.size() != 1) {
    cout << "handleFontInfo: Invalid number of args!\n";
    return false;
  }
  string font = P.at(0);
  std::map<string, GFXfont>::iterator itF;
  itF = myFonts.find(font);
  if (itF == myFonts.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Font %s doesn't exist!\n", font.c_str());
    cout << msg;
    return false;
  }
  GFXfont seoche = myFonts[font];
  int xxxxxx = snprintf(
    (char *)msg, 255,
    " • First char: `%c` [0x%02x], last char: `%c` [0x%02x]\n • yAdvance: %d\n",
    seoche.first, seoche.first, seoche.last, seoche.last, seoche.yAdvance
  );
  cout << msg;
  uint16_t offset = 65 - seoche.first; // index to Glyph array for 'A'
  int fWidth = (seoche.glyph + offset)->width;
  int fHeight = (seoche.glyph + offset)->height;
  int bitmapOffset = (seoche.glyph + offset)->bitmapOffset;
  int xAdvance = (seoche.glyph + offset)->xAdvance;
  int xOffset = (seoche.glyph + offset)->xOffset;
  int yOffset = (seoche.glyph + offset)->yOffset;
  int numBytes = (fWidth * fHeight) >> 3;
  if ((fWidth * fHeight) % 8 > 0) numBytes += 1;
  xxxxxx = snprintf(
    (char *)msg, 255, " # Info for `A`:\n • bitmapOffset: %d\n • Width: %d\n • height: %d\n • xAdvance: %d\n • xOffset: %d\n • yOffset: %d\n",
    bitmapOffset, fWidth, fHeight, xAdvance, xOffset, yOffset
  );
  cout << msg;
  xxxxxx = snprintf(
    (char *)msg, 255, " • Bytes required: %d\n", numBytes
  );
  cout << msg;
  return true;
}

bool handleDrawChar(vector<string> P) {
  // x y r g b a s font name DRAWCHR
  if (P.size() != 9) {
    cout << "handleDrawChar: Invalid number of args!\n";
    return false;
  }
  int ix = 0;
  string name = P.at(0);
  string font = P.at(1);
  string text = P.at(2);
  uint8_t a = std::atoi(P.at(3).c_str());
  uint8_t b = std::atoi(P.at(4).c_str());
  uint8_t g = std::atoi(P.at(5).c_str());
  uint8_t r = std::atoi(P.at(6).c_str());
  int y = std::atoi(P.at(7).c_str());
  int x = std::atoi(P.at(8).c_str());
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    cout << msg;
    return false;
  }
  std::map<string, GFXfont>::iterator itF;
  itF = myFonts.find(font);
  if (itF == myFonts.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Font %s doesn't exist!\n", font.c_str());
    cout << msg;
    return false;
  }
  GFXfont seoche = myFonts[font];
  vector<int> size = myImageSizes[name];
  vector<uint8_t> image = myImages[name];
  int height = size.at(0);
  int width = size.at(1);
  char C = text.at(0);
  if (C < seoche.first || C > seoche.last) {
    int xxxxxx = snprintf((char *)msg, 255, "Char %02x doesn't exist in this font!\n", C);
    cout << msg;
    return false;
  }

  cout << "Drawing " << C << " at " << x << ":" << y << " RGBA: " << (int)r << ", " << (int)g << ", " << (int)b << ", " << (int)a <<
  " with font " << font << endl;
  uint16_t offset = C - seoche.first; // index to Glyph array
  int fWidth = (seoche.glyph + offset)->width;
  int fHeight = (seoche.glyph + offset)->height;
  int bitmapOffset = (seoche.glyph + offset)->bitmapOffset;
  int xAdvance = (seoche.glyph + offset)->xAdvance;
  int xOffset = (seoche.glyph + offset)->xOffset;
  int yOffset = (seoche.glyph + offset)->yOffset;
  int numBytes = (fWidth * fHeight) >> 3;
  if ((fWidth * fHeight) % 8 > 0) numBytes += 1;
  int count = 0;
  uint8_t bit = 0;
  unsigned char n;
  for (int yy = 0; yy < fHeight; yy++) {
    for (int xx = 0; xx < fWidth; xx++) {
      if (!(bit++ & 7)) {
        n = seoche.bitmap[bitmapOffset++];
      }
      if (n & 0b10000000) {
        image = putPixel(image, x + xx + xOffset, y + yy + yOffset, width, r, g, b, a);
      }
      n <<= 1;
      count += 1;
    }
  }

  myImages[name] = image;
  myImageSizes[name] = size;
  return true;
}

bool handleInit(vector<string> P) {
  // INIT
  // if (P.size() != 0) {
  //    cout << "handleInit: Invalid number of args!\n";
  //    return false;
  //  }
  // En fait on s'en tape...
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

struct pluginCommand {
  bool (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
};

pluginCommand pluginCommands[] = {
  // handleInit is compulsory, in position 0
  { handleInit, "INIT", "0( -- ) Initializes the plugin, if required." },
  { handlePNGTest, "PNGTest", "0( -- ) Creates a PNG." },
  { handleCreateImage, "IMAGE", "3SII( w h s -- ) Creates a blank image." },
  { handleClearImage, "FILLIMG", "4SIII( r g b s -- ) Fills Image s with rgb." },
  { handleDrawPixel, "PIXEL", "7SIIIIII( x y r g b a s -- ) Draws an RGBA pixel." },
  { handleDrawHLine, "HLINE", "8SIIIIIII( x y L r g b a s -- ) Draws an RGBA horizontal line length L." },
  { handleDrawVLine, "VLINE", "8SIIIIIII( x y H r g b a s -- ) Draws an RGBA horizontal line length L." },
  { handleDrawLine, "DLINE", "9SIIIIIIII( x1 y1 x2 y2 r g b a s -- ) Draws an RGBA line." },
  { handleDrawCircle, "CIRCLE", "8SIIIIIII( x y rad r g b a s -- ) Draws an RGBA circle radius rad at x,y." },
  { handleDrawRect, "RECT", "9SIIIIIIII( x y L H r g b a s -- ) Draws an RGBA Box width L height H." },
  { handleFillRect, "FILLRECT", "9SIIIIIIII( x y L H r g b a s -- ) Fills an RGBA Box width L height H." },
  { handleNukeChannel, "X_CHANNEL", "2SS( [RGB] s -- ) Nukes channel R, G, or B." },
  { handleGreyscale, "GREYSCALE", "1S( s -- ) Converts image to greyscale." },
  { handleDrawChar, "DRAWCHR", "9SSSIIIIII( x y r g b a s font name -- ) Draws char s in RGBA at position x y, font `font`, image `name`." },
  { handleFontInfo, "FONTINFO", "1S( font -- ) Shows info about font `font`." },

  { handleSavePNG, "SAVEPNG", "2SS( s p -- ) Saves Image s to path p." },
  { handleLoadPNG, "LOADPNG", "2SS( s p -- ) Loads Image at path p as s." },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
