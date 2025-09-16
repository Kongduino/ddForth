using namespace std;
#include <fstream>
#include <cmath>  // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "esp_random.h"
// https://docs.espressif.com/projects/esp-idf/en/stable/esp32/api-reference/system/random.html
#include "mbedtls/aes.h"
// https://gist.github.com/AxelLin/41451f2e82da78df2a394155a5b7aa9d

bool putIntegerOnStack(int);
unsigned char getRandomByte();
bool getRandomBuffer();

unsigned char randomBuffer[256];
int randomIndex = 0;

void hexDump(unsigned char *buf, int len) {
  char alphabet[17] = "0123456789abcdef";
  printf("%s\n", "   +------------------------------------------------+ +----------------+");
  printf("%s\n", "   |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |");
  for (int i = 0; i < len; i += 16) {
    if (i % 128 == 0)
      printf("%s\n", "   +------------------------------------------------+ +----------------+");
    char s[] = "|                                                | |................|";
    char ix = 1, iy = 52;
    for (char j = 0; j < 16; j++) {
      if (i + j < len) {
        char c = buf[i + j];
        s[ix++] = alphabet[(c >> 4) & 0x0F];
        s[ix++] = alphabet[c & 0x0F];
        ix++;
        if ((int)c > 31 && (int)c < 128) s[iy++] = c;
      }
    }
    char index = i / 16;
    if (i < 256) printf("%s", " ");
    printf("%x.", index);
    printf("%s\n", s);
  }
  printf("%s\n", "   +------------------------------------------------+ +----------------+");
}

unsigned char getRND() {
  uint8_t x = 0, b;
  for (uint8_t j = 0; j < 8; j++) {
    b = (esp_random() & 0b00000001);
    while (b == (esp_random() & 0b00000001)) {
      // von Neumann extractor.
      b = (esp_random() & 0b00000001);
    }
    x = (x << 1) | b;
  }
  return x;
}

unsigned char getRandomByte() {
  if (randomIndex == 256) getRandomBuffer();
  uint8_t x = randomBuffer[randomIndex++];
  return x;
}

bool getRandomBuffer() {
  for (int ix = 0; ix < 256; ix++)
    randomBuffer[ix] = getRandomByte();
  hexDump(randomBuffer, 256);
  randomIndex = 0;
  return true;
}

bool putRandomByteOnStack() {
  uint8_t x = getRandomByte();
  putIntegerOnStack((int)x);
  return true;
}

bool putRandomUIntOnStack() {
  int i0;
  i0 = getRandomByte() + (getRandomByte() << 8);
  putIntegerOnStack(i0);
  return true;
}
