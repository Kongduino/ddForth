using namespace std;
#include <fstream>
#include <cmath> // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

void printText(char *);
bool putIntegerOnStack(int);
unsigned char getRND();

extern char msg[256];
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

bool getRandomBuffer() {
#if defined(DEBUG)
  hexDump(randomBuffer, 256);
#endif
  randomIndex = 0;
  return true;
}

unsigned char getRND() {
  if (randomIndex == 256) getRandomBuffer();
  uint8_t x = randomBuffer[randomIndex++];
  return x;
}

unsigned char getRandomByte() {
  uint8_t x = 0, b;
  for (uint8_t j = 0; j < 8; j++) {
    b = (getRND() & 0b00000001);
    while (b == (getRND() & 0b00000001)) {
      // von Neumann extractor.
      b = (getRND() & 0b00000001);
    }
    x = (x << 1) | b;
  }
  return x;
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
