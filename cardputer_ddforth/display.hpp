#include <stdio.h>
#include <vector>
#include <string>
#include "M5Cardputer.h"
#include "M5GFX.h"
#include "FS.h"
#include "SPIFFS.h"

bool popFloatFromStack(float *);
bool popFromLoopStack(int *);
bool popIntegerFromJumpStack(int *);
bool popIntegerFromStack(int *);
bool popStringFromStack(string *);
bool putFloatOnStack(float);
bool putIntegerOnJumpStack(int);
bool putIntegerOnStack(int);
bool putStringOnStack(string);
bool showStack();
bool showVars();
void logStack(char *);
void logInconsistent(char *who);
void logStackOverflow(char *who);
void logThis();
bool handleDrawPixel();
bool handleDRAWSTRING();
bool handleDRAWSTACKSTRING();

#define display M5Cardputer.Display
extern char msg[256];
LGFX_Sprite gfxSprite(&display);
LGFX_Sprite kbdSprite(&display);
char kbdData[256];
uint8_t kbdIdx;
uint16_t cl16 = 0;
uint8_t clR = 0, clG = 0, clB = 0;
extern bool isDrawing;
extern bool isPrinting;
extern bool insideString;

void commonPrint(char *);

void Matrix() {
  LGFX_Sprite matrixSprite(&display);
  char characters[256];
  matrixSprite.createSprite(240, 128);
  matrixSprite.setTextSize(1.0);
  matrixSprite.setTextFont(&fonts::FreeMonoBold12pt7b);
  matrixSprite.setTextColor(TFT_GREEN);
  uint8_t fw = 17;  //matrixSprite.fontWidth();
  uint8_t nCols = 240 / fw;
  uint8_t fh = matrixSprite.fontHeight();
  uint8_t nRows = 128 / fh;
  Serial.printf("Font width: %d px\n", fw);
  Serial.printf("Font height: %d px\n", fh);
  Serial.printf("nCols: %d\n", nCols);
  Serial.printf("nRows: %d\n", nRows);
  uint8_t ix, iy;
  uint16_t n;
  uint8_t bufferColor[nCols];
  uint8_t bufferLetters[nCols];
  uint8_t delays[nCols];
  for (n = 0; n < 256; n++) {
    uint32_t number = esp_random();
    characters[n] = (number % 95) + 32;
  }
  for (n = 0; n < nCols; n++) {
    uint32_t number = esp_random();
    delays[n] = (number & 0b1111);
  }
  for (iy = 0; iy < 32; iy++) {
    if (iy == 28) {
      memset(bufferColor, 0xff, nCols);
      memset(bufferLetters, 0x00, nCols);
      strcpy((char *)bufferLetters, msg);
    } else {
      esp_fill_random((void *)bufferColor, nCols);
      esp_fill_random((void *)bufferLetters, nCols);
    }
    matrixSprite.copyRect(0, fh, 240, 128 - fh, 0, 0);
    matrixSprite.fillRect(0, 0, 240, fh, TFT_BLACK);
    for (ix = 0; ix < nCols; ix++) {
      if (iy > delays[ix]) {
        uint8_t g = bufferColor[ix];
        uint16_t myColor = matrixSprite.color565(0, g, 0);
        g--;
        bufferColor[ix] = g;
        matrixSprite.setTextColor(myColor);
        char tmp[2];
        if (iy == 28)
          tmp[0] = bufferLetters[ix];
        else
          sprintf(tmp, "%c", characters[bufferLetters[ix]]);
        // Serial.write(characters[bufferLetters[ix]]);
        matrixSprite.drawString(tmp, ix * fw, 0);
      }
    }
    // Serial.write('\n');
    matrixSprite.pushSprite(0, 0);
    delay(100);
  }
  delay(500);
  matrixSprite.fillRect(0, 2 * fh, 240, fh, TFT_BLACK);
  matrixSprite.fillRect(0, 4 * fh, 240, fh, TFT_BLACK);
  matrixSprite.pushSprite(0, 0);
  delay(100);
  matrixSprite.fillRect(0, 0, 240, fh * 2, TFT_BLACK);
  matrixSprite.fillRect(0, 5 * fh, 240, fh, TFT_BLACK);
  matrixSprite.pushSprite(0, 0);
  delay(100);
  matrixSprite.fillRect(0, 0, 240, fh, TFT_BLACK);
  matrixSprite.pushSprite(0, 0);
  delay(500);
}

void commonPrint(char *text) {
  cout << text;
  display.print(text);
}

bool handleCLS() {
    int r, g, b;
  if (popIntegerFromStack(&b) == false) {
    logStackOverflow((char *)"handleSetColor/B");
    return false;
  }
  if (popIntegerFromStack(&g) == false) {
    logStackOverflow((char *)"handleSetColor/G");
    return false;
  }
  if (popIntegerFromStack(&r) == false) {
    logStackOverflow((char *)"handleSetColor/R");
    return false;
  }
  uint16_t mycl16 = (((uint8_t)r << 11) | ((uint8_t)g << 5) | (uint8_t)b);
  display.clear(mycl16);
  gfxSprite.createSprite(240, 128);
  gfxSprite.clear(mycl16);
  gfxSprite.setTextSize(1.0);
  gfxSprite.setTextFont(&fonts::FreeMonoBold12pt7b);
  uint16_t invCL = 0xFFFF - mycl16;
  gfxSprite.setTextColor(invCL);
  gfxSprite.pushSprite(0, 0);
  return true;
}

bool handleGetWidth() {
  putIntegerOnStack(240);
  return true;
}

bool handleGetHeight() {
  putIntegerOnStack(128);
  return true;
}

bool handleSetColor() {
  // void setColor(uint8_t r, uint8_t g, uint8_t b)
  int r, g, b;
  if (popIntegerFromStack(&b) == false) {
    logStackOverflow((char *)"handleSetColor/B");
    return false;
  }
  if (popIntegerFromStack(&g) == false) {
    logStackOverflow((char *)"handleSetColor/G");
    return false;
  }
  if (popIntegerFromStack(&r) == false) {
    logStackOverflow((char *)"handleSetColor/R");
    return false;
  }
  clR = (uint8_t)r;
  clG = (uint8_t)g;
  clB = (uint8_t)b;
  gfxSprite.setColor(clR, clG, clB);
  cl16 = (((uint8_t)r << 11) | ((uint8_t)g << 5) | (uint8_t)b);
  gfxSprite.setTextColor(cl16);
  return true;
}

bool handleDrawline() {
  // void drawLine( int32_t x0, int32_t y0, int32_t x1, int32_t y1)
  int x0, y0, x1, y1;
  if (popIntegerFromStack(&y1) == false) {
    logStackOverflow((char *)"handleDrawline/y1");
    return false;
  }
  if (popIntegerFromStack(&x1) == false) {
    logStackOverflow((char *)"handleDrawline/x1");
    return false;
  }
  if (popIntegerFromStack(&y0) == false) {
    logStackOverflow((char *)"handleDrawline/y0");
    return false;
  }
  if (popIntegerFromStack(&x0) == false) {
    logStackOverflow((char *)"handleDrawline/x0");
    return false;
  }
  gfxSprite.drawLine((int32_t)x0, (int32_t)y0, (int32_t)x1, (int32_t)y1);
  return true;
}

bool handleDrawPixel() {
  // void drawLine( int32_t x0, int32_t y0, int32_t x1, int32_t y1)
  int x0, y0;
  if (popIntegerFromStack(&y0) == false) {
    logStackOverflow((char *)"handleDrawPixel/y0");
    return false;
  }
  if (popIntegerFromStack(&x0) == false) {
    logStackOverflow((char *)"handleDrawPixel/x0");
    return false;
  }
  gfxSprite.drawPixel(x0, y0, cl16);
  return true;
}

bool handleDisplay() {
  gfxSprite.pushSprite(0, 0);
  return true;
}

bool handleDelay() {
  int seconds;
  if (popIntegerFromStack(&seconds) == false) {
    logStackOverflow((char *)"handleDelay/1");
    return false;
  }
  delay(seconds * 1000);
  return true;
}

bool handleDRAWSTRING() {
  isPrinting = false;
  isDrawing = true;
  insideString = true;
  return true;
}

void drawText(string c) {
  // void drawLine( int32_t x0, int32_t y0, int32_t x1, int32_t y1)
  int x0, y0;
  if (popIntegerFromStack(&y0) == false) {
    logStackOverflow((char *)"drawText/y0");
    return;
  }
  if (popIntegerFromStack(&x0) == false) {
    logStackOverflow((char *)"drawText/x0");
    return;
  }
  gfxSprite.drawString(c.c_str(), x0, y0);
}

bool handleDRAWSTACKSTRING() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleDRAWSTACKSTRING");
    return false;
  }
  drawText(s.c_str());
  return true;
}


// end