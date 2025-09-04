#include "FS.h"
#include "SPIFFS.h"

using namespace std;

string readFile(const char *);
void writeFile(const char *, const char *);
void listDir(const char *, uint8_t);

string readFile(const char *path) {
  Serial.printf("Reading file: %s\r\n", path);
  string code;
  File file = SPIFFS.open(path);
  if (!file || file.isDirectory()) {
    Serial.printf("- failed to open file %s for reading.\n", path);
    listDir("/", 1);
    return code;
  }
  while (file.available()) {
    code.push_back(file.read());
  }
  file.close();
  return code;
}

void writeFile(const char *path, const char *message) {
  Serial.printf("Writing file: %s\r\n", path);
  File file = SPIFFS.open(path, FILE_WRITE);
  if (!file) {
    Serial.printf("- failed to open file %s for writing.\n", path);
    return;
  }
  if (file.print(message)) {
    Serial.println("- file written");
  } else {
    Serial.println("- write failed");
  }
  file.close();
}

void listDir(const char *dirname, uint8_t levels) {
  Serial.printf("Listing directory: %s\n", dirname);
  File root = SPIFFS.open(dirname);
  if (!root) {
    Serial.println("- failed to open directory");
    return;
  }
  if (!root.isDirectory()) {
    Serial.println(" - not a directory");
    return;
  }

  File file = root.openNextFile();
  while (file) {
    if (file.isDirectory()) {
      Serial.print("  DIR : ");
      Serial.println(file.name());
      if (levels) {
        listDir(file.path(), levels - 1);
      }
    } else {
      Serial.print("  FILE: ");
      Serial.print(file.name());
      Serial.print("\tSIZE: ");
      Serial.println(file.size());
    }
    file = root.openNextFile();
  }
}
