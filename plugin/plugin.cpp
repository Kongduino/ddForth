#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>

using namespace std;

bool handleTagada() {
  cout << "\t\tRien de rien...\n";
  return true;
}

struct nativeCommand {
  bool (*ptr)(void); // Function pointer
  string name;
  string help;
};

nativeCommand nativeCommands[] = {
  { handleTagada, "TAGADA", "( -- ) Does nothing." },
  { handleTagada, "TRUCMUCHE", "( -- ) Does nothing." },
  { handleTagada, "BISTORK", "( -- ) Does nothing." },
};
int nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);

int numFunc() {
  return nativeCmdCount;
}

nativeCommand commandX(int x) {
  return nativeCommands[x];
}



// end