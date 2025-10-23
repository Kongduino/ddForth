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
bool pluginLoaded = false;
void *pluginHandle;

bool handleLoadPlugin() {
  string path;
  if (popStringFromStack(&path) == false) {
    logStackOverflow((char *)"handleLoadPlugin");
    return false;
  }
  // This needs to happen BEFORE dlopen(), IF a library was already opened.
  if (pluginLoaded) dlclose(pluginHandle);
  pluginHandle = dlopen(path.c_str(), RTLD_LAZY);
  if (!pluginHandle) {
    fprintf(stderr, "handleLoadPlugin: %s\n", dlerror());
    exit(EXIT_FAILURE);
  }
  dlerror(); /* Clear any existing error */
  pluginCmdCount_ptr = (int *)dlsym(pluginHandle, "pluginCmdCount");
  if (!pluginCmdCount_ptr) {
    fprintf(stderr, "handleLoadPlugin: Error finding symbol 'pluginCmdCount': %s\n", dlerror());
    dlclose(pluginHandle);
    return false;
  }
  pluginCmdCount = *pluginCmdCount_ptr;
  cout << "Command count: " << pluginCmdCount << endl;
  shared_nativeCommand_ptr = (nativeCommand *)dlsym(pluginHandle, "pluginCommands");
  if (!shared_nativeCommand_ptr) {
    fprintf(stderr, "handleLoadPlugin: Error finding symbol 'pluginCommands': %s\n", dlerror());
    dlclose(pluginHandle);
    return false;
  }
  pluginLoaded = true;
  pluginCommands = shared_nativeCommand_ptr;
  for (int ix = 0; ix < pluginCmdCount; ix++) {
    cout << " • " << pluginCommands[ix].name << ":\t" << pluginCommands[ix].help << endl;
    // bool rslt = pluginCommands[ix].ptr();
  }
  return true;
}
