#include "SPIFFS.h"

extern char code[256];
extern int xxxxxx;
extern char msg[256];
void logThis();

using namespace std;

bool spiffsInited = false;

vector<string> loadFile(char *);

int listAllFiles() {
  Serial.println("listAllFiles");
  if (!spiffsInited) {
    Serial.println("SPIFFS.begin");
    if (!SPIFFS.begin(true)) {
      Serial.println("An Error has occurred while mounting SPIFFS");
    }
    spiffsInited = true;
  }
  int fc = 0;
  File root = SPIFFS.open("/");
  File file = root.openNextFile();
  while (file) {
    fc += 1;
    Serial.print(" * FILE: ");
    Serial.println(file.name());
    file = root.openNextFile();
  }
  Serial.println("====================");
  return fc;
}

vector<string> loadFile(char *fn) {
  vector<string> thisBlock;
  if (!spiffsInited) {
    if (!SPIFFS.begin(true)) {
      Serial.println("An Error has occurred while mounting SPIFFS");
      return thisBlock;
    }
    spiffsInited = true;
  }
  xxxxxx = snprintf((char *)msg, 255, "loadFile %s\n", fn);
  logThis();
  File file = SPIFFS.open(fn, FILE_READ);
  if (!file) {
    Serial.println("There was an error opening the file for writing");
    return thisBlock;
  }

  char linebuffer[256];
  while (file.available()) {
    int l = file.readBytesUntil('\n', linebuffer, 255);
    linebuffer[l] = 0;
    thisBlock.push_back(linebuffer);
  }
  file.close();
  return thisBlock;
}
