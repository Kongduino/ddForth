#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>

using namespace std;

nativeCommand *shared_nativeCommand_ptr;
int *pluginCmdCount_ptr;
nativeCommand *pluginCommands;
int pluginCmdCount;

bool handleLoadPlugin() {
  void *handle;
  string path;
  if (popStringFromStack(&path) == false) {
    logStackOverflow((char *)"handleLoadPlugin");
    return false;
  }
  handle = dlopen(path.c_str(), RTLD_LAZY);
  if (!handle) {
    fprintf(stderr, "handleLoadPlugin: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  dlerror(); /* Clear any existing error */
  pluginCmdCount_ptr = (int *)dlsym(handle, "pluginCmdCount");
  if (!pluginCmdCount_ptr) {
    fprintf(stderr, "handleLoadPlugin: Error finding symbol 'pluginCmdCount': %s\n", dlerror());
    dlclose(handle);
    return false;
  }
  pluginCmdCount = *pluginCmdCount_ptr;
  cout << "Command count: " << pluginCmdCount << endl;
  shared_nativeCommand_ptr = (nativeCommand *)dlsym(handle, "pluginCommands");
  if (!shared_nativeCommand_ptr) {
    fprintf(stderr, "handleLoadPlugin: Error finding symbol 'pluginCommands': %s\n", dlerror());
    dlclose(handle);
    return false;
  }
  pluginCommands = shared_nativeCommand_ptr;
  for (int ix = 0; ix < pluginCmdCount; ix++) {
    cout << " • " << pluginCommands[ix].name << ":\t" << pluginCommands[ix].help << endl;
    // bool rslt = pluginCommands[ix].ptr();
  }

  // dlclose(handle);
  return true;
}
