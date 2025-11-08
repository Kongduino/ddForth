#include <cmath> // For sin, cos, tan
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
#define PROGMEM
#include "Adafruit-GFX-Library/Fonts/FreeMono18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeMonoBold18pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeSansBold12pt7b.h"
#include "Adafruit-GFX-Library/Fonts/FreeSans12pt7b.h"
#include "QR-Code-generator/cpp/qrcodegen.hpp"

using namespace std;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

vector<string> handleCreateImage(vector<string>);
vector<string> handleFillRect(vector<string>);
vector<uint8_t> putPixel(vector<uint8_t>, int, int, int, int, int, int, int);
vector<string> handleClearImage(vector<string>);

char msg[256];
std::map<string, GFXfont> myFonts;
std::map<string, vector<uint8_t>> myImages;
std::map<string, vector<int>> myImageSizes;
// Making px:py for text global, so we can draw characters without having to decide the position
int textPX = 0, textPY = 0;
vector<int> RGBA = { 0, 0, 0, 255 };
string FontName;

// --------------------------------------------------------
// Helper Functions
// --------------------------------------------------------

// Prints the given QRCode object to the console.
static void saveQr(const QrCode &qr, string name, int border, int nPixels) {
  vector<string> P;
  int fullSize = (qr.getSize() + border + border);
  int widthHeight = fullSize * nPixels;
  P.push_back(name);
  P.push_back(std::to_string(widthHeight));
  P.push_back(std::to_string(widthHeight));
  P = handleCreateImage(P);
  P.clear();
  P.push_back(name);
  P.push_back("255");
  P.push_back("255");
  P.push_back("255");
  P = handleClearImage(P);
  // r g b name FILL

  vector<uint8_t> image = myImages[name];
  uint8_t rrggbb;
  for (int y = -border; y < qr.getSize() + border; y++) {
    for (int x = -border; x < qr.getSize() + border; x++) {
      P.clear();
      if(qr.getModule(x, y)) {
        rrggbb = 0;
      } else {
        rrggbb = 255;
      }
      if (nPixels == 1) {
        image = putPixel(image, x, y, widthHeight, rrggbb, rrggbb, rrggbb, 255);
      } else {
        RGBA.at(0) = rrggbb;
        RGBA.at(1) = rrggbb;
        RGBA.at(2) = rrggbb;
        RGBA.at(3) = 255;
        P.push_back(name);
        P.push_back(std::to_string(nPixels));
        P.push_back(std::to_string(nPixels));
        P.push_back(std::to_string((y + border) * nPixels));
        P.push_back(std::to_string((x + border) * nPixels));
        P = handleFillRect(P);
      }
    }
  }
}

// Prints the given QRCode object to the console.
static void printQr(const QrCode &qr, int border) {
  // int border = 4;
  for (int y = -border; y < qr.getSize() + border; y++) {
    for (int x = -border; x < qr.getSize() + border; x++) {
      std::cout << (qr.getModule(x, y) ? "██" : "  ");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Creates a single QR Code, then prints it to the console.
vector<string> handleSimpleQRCode(vector<string> P) {
  // border size name text QRCODE
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleSimpleQRCode: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string text = P.at(0);
  string name = P.at(1);
  int nPixels = std::atoi(P.at(2).c_str());
  int border = std::atoi(P.at(3).c_str());
  const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW; // Error correction level
  // Make and print the QR Code symbol
  const QrCode qr = QrCode::encodeText(text.c_str(), errCorLvl);
  printQr(qr, border);
  saveQr(qr, name, border, nPixels);
  return R;
}

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

vector<uint8_t> putPixel(vector<uint8_t> image, int x, int y, int width, int r, int g, int b, int a) {
  int position = y * width * 4 + x * 4;
  if (a == 255) {
    // No computing alpha channel
    image[position++] = r;
    image[position++] = g;
    image[position++] = b;
    image[position++] = a;
  } else {
    image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
    position += 1;
    image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
    position += 1;
    image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
    position += 1;
    image[position] = (image[position] + a) / 2;
  }
  return image;
}

// --------------------------------------------------------
// Main Code
// --------------------------------------------------------

vector<string> handleCreateImage(vector<string> P) {
  vector<string> R; // the return vector
  if (P.size() != 3) {
    R.push_back("false");
    R.push_back("handleCreateImage: Invalid number of args!\n");
    return R;
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
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  return R;
}

vector<string> handleGetSize(vector<string> P) {
  vector<string> R; // the return vector
  if (P.size() != 1) {
    R.push_back("false");
    R.push_back("handleGetSize: Invalid number of args!\n");
    return R;
  }
  string name = P.at(0);
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  R.push_back("I" + std::to_string(height));
  R.push_back("I" + std::to_string(width));
  return R;
}

vector<string> handleSetRGBA(vector<string> P) {
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleSetRGBA: Invalid number of args!\n");
    cout << "handleSetRGBA: Invalid number of args!\n";
    return R;
  }
  for (int i = 0; i < 4; i++) {
    RGBA.at(i) = std::atoi(P.at(i).c_str());
    cout << "RGBA.at(" << i << ") = " << P.at(i) << endl;
  }
  return R;
}

vector<string> handleSetFont(vector<string> P) {
  vector<string> R; // the return vector
  if (P.size() != 1) {
    R.push_back("false");
    R.push_back("handleSetFont: Invalid number of args!\n");
    return R;
  }
  FontName = P.at(0);
  return R;
}

vector<string> handlePNGTest(vector<string> P) {
  vector<string> R; // the return vector
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
  R.push_back("Stest.png");
  return R;
}

vector<string> handleDrawPixel(vector<string> P) {
  // x y name PIXEL
  vector<string> R; // the return vector
  if (P.size() != 3) {
    R.push_back("false");
    R.push_back("handleDrawPixel: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int y = std::atoi(P.at(1).c_str());
  int x = std::atoi(P.at(2).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  image = putPixel(image, x, y, width, r, g, b, a);
  myImages[name] = image;
  return R;
}

vector<string> handleGetPixel(vector<string> P) {
  // x y name PIXEL?
  vector<string> R; // the return vector
  if (P.size() != 3) {
    R.push_back("false");
    R.push_back("handleGetPixel: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  int y = std::atoi(P.at(1).c_str());
  int x = std::atoi(P.at(2).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  //int position = y * 4 * width + (x * 4);
  int position = (y * width * 4) + (x * 4);
  uint8_t r = image.at(position++);
  uint8_t g = image.at(position++);
  uint8_t b = image.at(position++);
  uint8_t a = image.at(position);
  R.push_back("I" + std::to_string(a));
  R.push_back("I" + std::to_string(b));
  R.push_back("I" + std::to_string(g));
  R.push_back("I" + std::to_string(r));
  return R;
}

vector<string> handleFillRect(vector<string> P) {
  // x y L H name FILLRECT
  vector<string> R;  // the return vector
  if (P.size() != 5) {
    R.push_back("false");
    R.push_back("handleFillRect: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  int H = std::atoi(P.at(1).c_str());
  int L = std::atoi(P.at(2).c_str());
  int y = std::atoi(P.at(3).c_str());
  int x = std::atoi(P.at(4).c_str());
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleFillRect: Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleFillRect: Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  if ((x + L) >= width) L = width - x;
  if ((y + H) >= height) H = height - y;
  // cout << "L: " << L << ", H: " << H << endl;
  for (int jx = 0; jx < H; jx++) {
    // line by line, calculate the start position
    int position = (y + jx) * width * 4 + x * 4;
    for (int ix = 0; ix < L; ix++) {
      // Draw a line
      if (a == 255) {
        // No computing alpha channel
        image[position++] = r;
        image[position++] = g;
        image[position++] = b;
        image[position++] = a;
      } else {
        image[position] = (r * a / 255 + image[position] * image[position + 3] / 255) / 2;
        position += 1;
        image[position] = (g * a / 255 + image[position] * image[position + 2] / 255) / 2;
        position += 1;
        image[position] = (b * a / 255 + image[position] * image[position + 1] / 255) / 2;
        position += 1;
        image[position] = (image[position] + a) / 2;
      }
    }
  }
  myImages[name] = image;
  return R;
}

vector<string> handleDrawRect(vector<string> P) {
  // x y L H name RECT
  vector<string> R; // the return vector
  if (P.size() != 5) {
    R.push_back("false");
    R.push_back("handleDrawRect: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int H = std::atoi(P.at(1).c_str());
  int L = std::atoi(P.at(2).c_str());
  int y = std::atoi(P.at(3).c_str());
  int x = std::atoi(P.at(4).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleDrawHLine(vector<string> P) {
  // x y L name HLINE
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleDrawHLine: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int L = std::atoi(P.at(1).c_str());
  int y = std::atoi(P.at(2).c_str());
  int x = std::atoi(P.at(3).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleDrawVLine(vector<string> P) {
  // x y H name VLINE
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleDrawVLine: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int H = std::atoi(P.at(1).c_str());
  int y = std::atoi(P.at(2).c_str());
  int x = std::atoi(P.at(3).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleDrawLine(vector<string> P) {
  // x1 y1 x2 y2 name DLINE
  vector<string> R; // the return vector
  if (P.size() != 5) {
    R.push_back("false");
    R.push_back("handleDrawLine: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int y2 = std::atoi(P.at(1).c_str());
  int x2 = std::atoi(P.at(2).c_str());
  int y1 = std::atoi(P.at(3).c_str());
  int x1 = std::atoi(P.at(4).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleDrawCircle(vector<string> P) {
  // x y radius name CIRCLE
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleDrawCircle: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  int radius = std::atoi(P.at(1).c_str());
  int y = std::atoi(P.at(1).c_str());
  int x = std::atoi(P.at(3).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleClearImage(vector<string> P) {
  // r g b name FILL
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    R.push_back("handleClearImage: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  uint8_t b = std::atoi(P.at(1).c_str());
  uint8_t g = std::atoi(P.at(2).c_str());
  uint8_t r = std::atoi(P.at(3).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleNukeChannel(vector<string> P) {
  // [RGB] name X_CHANNEL
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleNukeChannel: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  string channel = P.at(1);
  if (channel != "R" && channel != "G" && channel != "B") {
    R.push_back("false");
    R.push_back("handleNukeChannel: Invalid Channel Name [RGB]!\n");
    return R;
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
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleGreyscale(vector<string> P) {
  // [RGB] name GREYSCALE
  vector<string> R; // the return vector
  if (P.size() != 1) {
    R.push_back("false");
    R.push_back("handleGreyscale: Invalid number of args!\n");
    return R;
  }
  if (P.size() != 1) {
    cout << "handleGreyscale: Invalid number of args!\n";
    R.push_back("false");
    R.push_back("handleGreyscale: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
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
  return R;
}

vector<string> handleSavePNG(vector<string> P) {
  // name path SAVEPNG
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleSavePNG: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string path = P.at(0);
  string name = P.at(1);
  std::map<string, vector<uint8_t>>::iterator it;
  it = myImages.find(name);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image = myImages[name];
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  bool rslt = encodeOneStep(path, image.data(), width, height);
  return R;
}

vector<string> handleLoadPNG(vector<string> P) {
  // name path LOADPNG
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleLoadPNG: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string path = P.at(0);
  string name = P.at(1);
  bool rslt = decodeOneStep(path, name);
  if (!rslt) {
    R.push_back("false");
    R.push_back("handleLoadPNG: decodeOneStep() failed\n");
    return R;
  }
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<int> size = myImageSizes[name];
  int height = size.at(0);
  int width = size.at(1);
  return R;
}

vector<string> handleFontInfo(vector<string> P) {
  // char font FONTINFO
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleFontInfo: Invalid number of args!\n");
    return R;
  }
  string font = P.at(0);
  string myChar = P.at(1);
  std::map<string, GFXfont>::iterator itF;
  itF = myFonts.find(font);
  if (itF == myFonts.end()) {
    R.push_back("false");
    int xxxxxx = snprintf((char *)msg, 255, "Font %s doesn't exist!\n", font.c_str());
    R.push_back(msg);
    return R;
  }
  GFXfont seoche = myFonts[font];
  int xxxxxx = snprintf(
    (char *)msg, 255,
    " • First char: `%c` [0x%02x], last char: `%c` [0x%02x]\n • yAdvance: %d\n",
    seoche.first, seoche.first, seoche.last, seoche.last, seoche.yAdvance);
  cout << msg;
  char C = myChar.at(0);
  uint16_t offset = C - seoche.first; // index to Glyph array for 'A'
  int fWidth = (seoche.glyph + offset)->width;
  R.push_back("I" + std::to_string(fWidth));
  int fHeight = (seoche.glyph + offset)->height;
  R.push_back("I" + std::to_string(fHeight));
  int bitmapOffset = (seoche.glyph + offset)->bitmapOffset;
  int xAdvance = (seoche.glyph + offset)->xAdvance;
  R.push_back("I" + std::to_string(xAdvance));
  int xOffset = (seoche.glyph + offset)->xOffset;
  int yOffset = (seoche.glyph + offset)->yOffset;
  int numBytes = (fWidth * fHeight) >> 3;
  if ((fWidth * fHeight) % 8 > 0) numBytes += 1;
  xxxxxx = snprintf(
    (char *)msg, 255, " # Info for `%c`:\n • bitmapOffset: %d\n • Width: %d\n • height: %d\n • xAdvance: %d\n • xOffset: %d\n • yOffset: %d\n",
    C, bitmapOffset, fWidth, fHeight, xAdvance, xOffset, yOffset);
  cout << msg;
  xxxxxx = snprintf(
    (char *)msg, 255, " • Bytes required: %d\n", numBytes);
  cout << msg;
  return R;
}

vector<string> handleStringWidth(vector<string> P) {
  // string font FONTINFO
  vector<string> R;  // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleStringWidth: Invalid number of args!\n");
    return R;
  }
  string font = P.at(0);
  string myString = P.at(1);
  std::map<string, GFXfont>::iterator itF;
  itF = myFonts.find(font);
  if (itF == myFonts.end()) {
    R.push_back("false");
    int xxxxxx = snprintf((char *)msg, 255, "Font %s doesn't exist!\n", font.c_str());
    R.push_back(msg);
    return R;
  }
  GFXfont seoche = myFonts[font];
  int strLen = 0;
  for (int xx = 0; xx < myString.length(); xx++) {
    char C = myString.at(xx);
    uint16_t offset = C - seoche.first; // index to Glyph array for C
    strLen += (seoche.glyph + offset)->xAdvance;
  }
  R.push_back("I" + std::to_string(strLen));
  return R;
}

vector<string> handleSetTextPXPY(vector<string> P) {
  // x y TEXTXY
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleSetTextPXPY: Invalid number of args!\n");
    return R;
  }
  textPY = std::atoi(P.at(0).c_str());
  textPX = std::atoi(P.at(1).c_str());
  return R;
}

vector<string> handleDrawChar(vector<string> P) {
  // s name DRAWCHR
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleDrawChar: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string name = P.at(0);
  string text = P.at(1);
  uint8_t a = RGBA.at(3);
  uint8_t b = RGBA.at(2);
  uint8_t g = RGBA.at(1);
  uint8_t r = RGBA.at(0);
  std::map<string, vector<int>>::iterator itS;
  itS = myImageSizes.find(name);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Size Record for Image %s doesn't exist!\n", name.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  std::map<string, GFXfont>::iterator itF;
  itF = myFonts.find(FontName);
  if (itF == myFonts.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "Font %s doesn't exist!\n", FontName.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  GFXfont seoche = myFonts[FontName];
  vector<int> size = myImageSizes[name];
  vector<uint8_t> image = myImages[name];
  int height = size.at(0);
  int width = size.at(1);
  char C = text.at(0);
  if (C < seoche.first || C > seoche.last) {
    int xxxxxx = snprintf((char *)msg, 255, "Char %02x doesn't exist in this font!\n", C);
    R.push_back("false");
    R.push_back(msg);
    return R;
  }

  // cout << "Drawing " << C << " at " << textPX << ":" << textPY << " RGBA: " << (int)r << ", " << (int)g << ", " << (int)b << ", " << (int)a << " with font " << FontName << endl;
  uint16_t offset = C - seoche.first; // index to Glyph array
  int fWidth = (seoche.glyph + offset)->width;
  int fHeight = (seoche.glyph + offset)->height;
  int bitmapOffset = (seoche.glyph + offset)->bitmapOffset;
  int xAdvance = (seoche.glyph + offset)->xAdvance;
  int xOffset = (seoche.glyph + offset)->xOffset;
  int yOffset = (seoche.glyph + offset)->yOffset;
  int yAdvance = seoche.yAdvance;
  int count = 0;
  uint8_t bit = 0;
  unsigned char n;
  for (int yy = 0; yy < fHeight; yy++) {
    if ((textPY + yy) >= height) {
      // Same for py. Let's make sure we draw within the confines of the image
      // and, most importantly, of the buffer...
      textPY = 0 - yOffset;
    }
    for (int xx = 0; xx < fWidth; xx++) {
      if (!(bit++ & 7)) {
        n = seoche.bitmap[bitmapOffset++];
      }
      if ((textPX + xx + xOffset) >= width) {
        // for the moment loop around to px = 0, py += yAdvance
        textPX = 0;
        textPY += yAdvance;
        if ((textPY + yy) >= height) {
          // Same for py. Let's make sure we draw within the confines of the image
          // and, most importantly, of the buffer...
          textPY = 0 - yOffset;
        }
      }
      if (n & 0b10000000) {
        image = putPixel(image, textPX + xx + xOffset, textPY + yy + yOffset, width, r, g, b, a);
      }
      n <<= 1;
      count += 1;
    }
  }
  textPX += xAdvance;

  myImages[name] = image;
  myImageSizes[name] = size;
  return R;
}

vector<string> handleCopyImage(vector<string> P) {
  // x y name1 name0 PIXEL
  // copy image name0 onto image name1 at x, y
  vector<string> R; // the return vector
  if (P.size() != 4) {
    R.push_back("false");
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Invalid number of args [%zu]!\n", P.size());
    R.push_back(msg);
    return R;
  }
  int ix = 0;
  string name0 = P.at(0);
  string name1 = P.at(1);
  int y = std::atoi(P.at(2).c_str());
  int x = std::atoi(P.at(3).c_str());
  std::map<string, vector<uint8_t>>::iterator it;
  std::map<string, vector<int>>::iterator itS;
  it = myImages.find(name0);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Image %s doesn't exist!\n", name0.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  itS = myImageSizes.find(name0);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Size Record for Image %s doesn't exist!\n", name0.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image0 = myImages[name0];
  vector<int> size0 = myImageSizes[name0];
  int height0 = size0.at(0);
  int width0 = size0.at(1);

  it = myImages.find(name1);
  if (it == myImages.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Image %s doesn't exist!\n", name1.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  itS = myImageSizes.find(name1);
  if (itS == myImageSizes.end()) {
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Size Record for Image %s doesn't exist!\n", name1.c_str());
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  vector<uint8_t> image1 = myImages[name1];
  vector<int> size1 = myImageSizes[name1];
  int height1 = size1.at(0);
  int width1 = size1.at(1);
  
  // We now have the two images.
  // Check that image0 fits into image1
  if ((x + width0) >= width1 || (y + height0) >= height1) {
    int xxxxxx = snprintf((char *)msg, 255, "handleCopyImage: Image %s doesn't fit into Image %s! %d x %d vs %d x %d\n", name0.c_str(), name1.c_str(), (x + width0), (y + height0), height1, width1);
    R.push_back("false");
    R.push_back(msg);
    return R;
  }
  
  int position0 = 0;
  int position1 = 0;
  for (int jx = 0; jx < height0; jx++) {
    position1 = (jx * width1 * 4) + (x * 4);
    for (int ix = 0; ix < width0; ix++) {
      image1[position1++] = image0[position0++];
      image1[position1++] = image0[position0++];
      image1[position1++] = image0[position0++];
      image1[position1++] = image0[position0++];
    }
  }
  myImages[name1] = image1;
  return R;
}

vector<string> handleInit(vector<string> P) {
  vector<string> R;
  // INIT
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
  FontName = "FreeSans12pt7b";
  return R;
}

struct pluginCommand {
  vector<string> (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
  string params;
};

pluginCommand pluginCommands[] = {
  // handleInit is compulsory, in position 0
  { handleInit, "INIT", "( -- ) Initializes the plugin, if required.", "0" },
  { handlePNGTest, "PNGTest", "( -- ) Creates a PNG.", "0" },
  { handleCreateImage, "IMAGE", "( w h s -- ) Creates a blank image.", "3SII" },
  { handleGetSize, "IMGSIZE", "( -- w h s ) Puts image's width and height on stack.", "1S" },
  { handleSetRGBA, "DRAWRGBA", "( r g b a -- ) Sets the drawing colour.", "4IIII" },
  { handleSetFont, "SETFONT", "( font -- ) Sets the drawing font to `font`.", "1S" },
  { handleClearImage, "FILLIMG", "( r g b s -- ) Fills Image s with rgb.", "4SIII" },
  { handleDrawPixel, "PIXEL", "( x y s -- ) Draws an RGBA pixel.", "3SII" },
  { handleGetPixel, "PIXEL?", "( x y s -- r g b a ) Puts RGBA value of a pixel on the stack.", "3SII" },
  { handleDrawHLine, "HLINE", "( x y L s -- ) Draws an RGBA horizontal line length L.", "4SIII" },
  { handleDrawVLine, "VLINE", "( x y H s -- ) Draws an RGBA horizontal line length L.", "4SIII" },
  { handleDrawLine, "DLINE", "( x1 y1 x2 y2 s -- ) Draws an RGBA line.", "5SIIII" },
  { handleDrawCircle, "CIRCLE", "( x y rad s -- ) Draws an RGBA circle radius rad at x,y.", "4SIII" },
  { handleDrawRect, "RECT", "( x y L H s -- ) Draws an RGBA Box width L height H.", "5SIIII" },
  { handleFillRect, "FILLRECT", "( x y L H s -- ) Fills an RGBA Box width L height H.", "5SIIII" },
  { handleNukeChannel, "X_CHANNEL", "( [RGB] s -- ) Nukes channel R, G, or B.", "2SS" },
  { handleGreyscale, "GREYSCALE", "( s -- ) Converts image to greyscale.", "1S" },
  { handleSetTextPXPY, "TEXTXY", "( x y -- ) Sets px:py for text drawing.", "2II" },
  { handleDrawChar, "DRAWCHR", "( s name -- ) Draws char s in RGBA at global position textPX, textPY, `font`, image `name`.", "2SS" },
  { handleFontInfo, "FONTINFO", "( C font -- ) Shows info about char C in `font`.", "2SS" },
  { handleStringWidth, "STRWIDTH", "( s font -- ) Returns length in pixels of s in `font`.", "2SS" },
  { handleSimpleQRCode, "QRCODE", "( border size name text -- ) Creates a simple QR code.", "4SSII" },

  { handleSavePNG, "SAVEPNG", "( s p -- ) Saves Image s to path p.", "2SS" },
  { handleLoadPNG, "LOADPNG", "( s p -- ) Loads Image at path p as s.", "2SS" },
  { handleCopyImage, "COPYIMG", "( x y name1 name0 -- ) Copies image name0 onto image name1 at x, y.", "4SSII" },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
