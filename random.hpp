#include <fstream>
#include <iostream>

bool putIntegerOnStack(int);

unsigned char randomBuffer[256];
int randomIndex = 0;

void hexDump(unsigned char *buf, int len) {
  char alphabet[17]="0123456789abcdef";
  printf("%s\n", "   +------------------------------------------------+ +----------------+");
  printf("%s\n", "   |.0 .1 .2 .3 .4 .5 .6 .7 .8 .9 .a .b .c .d .e .f | |      ASCII     |");
  for (int i = 0; i < len; i += 16) {
    if (i % 128 == 0)
      printf("%s\n", "   +------------------------------------------------+ +----------------+");
    char s[]="|                                                | |................|";
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
    if(i<256) printf("%s", " ");
    printf("%x.", index);
    printf("%s\n", s);
  }
  printf("%s\n", "   +------------------------------------------------+ +----------------+");
}

bool getRandom() {
  std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
  if (urandom.is_open()) {
    std::vector<char> random_bytes(256);
    urandom.read(random_bytes.data(), 256);
    urandom.close();
    memcpy(randomBuffer, random_bytes.data(), 256);
#if defined(DEBUG)
    hexDump(randomBuffer, 256);
#endif
    randomIndex = 0;
    return true;
  } else {
    std::cerr << "Error: Could not open /dev/urandom" << std::endl;
    return false;
  }
}

bool getRandomByte() {
  int i0;
  if (randomIndex == 256) getRandom();
  i0 = randomBuffer[randomIndex++];
  putIntegerOnStack(i0);
  return true;
}

bool getRandomUInt() {
  int i0;
  unsigned char c0, c1;
  if (randomIndex == 256) getRandom();
  c0 = randomBuffer[randomIndex++];
  if (randomIndex == 256) getRandom();
  c1 = randomBuffer[randomIndex++];
  i0 = c0 + (c1 << 8);
  putIntegerOnStack(i0);
  return true;
}
