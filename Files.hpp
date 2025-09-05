#include <fstream> // For ifstream

extern char code[256];
extern int xxxxxx;
extern char msg[256];
void logThis();

using namespace std;

vector<string> loadFile(char *);

vector<string> loadFile(char *fn) {
  xxxxxx = snprintf((char *)msg, 255, "loadFile %s\n", fn);
  logThis();
  vector<string> thisBlock;
  ifstream inputFile(fn);
  if (!inputFile.is_open()) {
    cerr << "Unable to open file!" << endl;
    return thisBlock;
  }
  string line;
  while (std::getline(inputFile, line)) {
    thisBlock.push_back(line);
  }
  return thisBlock;
}
