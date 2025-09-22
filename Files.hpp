#include <fstream> // For ifstream

extern char code[256];
extern int xxxxxx;
extern char msg[256];
void logThis();

using namespace std;

vector<string> loadFile(char *);

vector<string> loadAndTokenize(char* fn) {
  vector<string> chunks;
  vector<string> thisBlock = loadFile(fn);
  if (thisBlock.size() == 0) {
    cerr << "Unable to open file!" << endl;
    return chunks;
  }
  int lineCount = 0;
  string line;
  for (vector<string>::iterator it = thisBlock.begin(); it != thisBlock.end(); ++it) {
    line = *it;
    while (!line.empty() && line.back() == '\n')
      line.pop_back();
    lineCount += 1;
    strcpy(code, line.c_str());
    chunks = tokenize(code, chunks);
    cout << " • Read: " << line << endl;
  }
  cout << "Read: " << lineCount << " line" << (lineCount > 1 ? "s," : ",") << " chunks: " << chunks.size() << endl;
  return chunks;
}

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
  inputFile.close();
  return thisBlock;
}

bool handleFLOAD() {
  string name;
  if (popStringFromStack(&name) == false) {
    logStackOverflow((char *)"handleFLOAD/0");
    return false;
  }
  vector<string> tempChunks = loadAndTokenize((char*)name.c_str());
  evaluate(tempChunks);
  tempChunks.clear();
  executionPointer = 1e6;
  return true;
}