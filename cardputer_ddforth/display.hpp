#include <stdio.h>
#include <vector>
#include <string>
#include "M5Cardputer.h"
#include "M5GFX.h"
#include "FS.h"
#include "SPIFFS.h"

#define display M5Cardputer.Display
extern char msg[256];

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
