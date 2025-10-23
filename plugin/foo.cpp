#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>

using namespace std;

struct nativeCommand {
  bool (*ptr)(void); // Function pointer
  string name;
  string help;
};
// This definition comes from ddForth

nativeCommand *shared_nativeCommand_ptr;
int *nativeCmdCount_ptr;

int main(int argc, char **argv) {
  void *handle;

  handle = dlopen("plugin.dylib", RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "%s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  dlerror(); /* Clear any existing error */
  nativeCmdCount_ptr = (int *)dlsym(handle, "nativeCmdCount");
  if (!nativeCmdCount_ptr) {
    fprintf(stderr, "Error finding symbol 'nativeCmdCount': %s\n", dlerror());
    dlclose(handle);
    return 1;
  }
  int nativeCmdCount = *nativeCmdCount_ptr;
  cout << "Command count: " << nativeCmdCount << endl;
  shared_nativeCommand_ptr = (nativeCommand *)dlsym(handle, "nativeCommands");
  if (!shared_nativeCommand_ptr) {
    fprintf(stderr, "Error finding symbol 'nativeCommands': %s\n", dlerror());
    dlclose(handle);
    return 1;
  }
  nativeCommand *pluginCommands;
  pluginCommands = shared_nativeCommand_ptr;
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    cout << " • " << pluginCommands[ix].name << ":\t" << pluginCommands[ix].help << endl;
    bool rslt = pluginCommands[ix].ptr();
  }

  dlclose(handle);
  exit(EXIT_SUCCESS);
}
