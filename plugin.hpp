#include <cstdio>
#include <cstring>
#include <string>
#include <dlfcn.h>
#include <iostream>
#include <cstdlib> // For getenv

using namespace std;

struct pluginCommand {
  vector<string> (*ptr)(vector<string>);  // Function pointer
  string name;
  string help;
  string params;
};

pluginCommand *shared_pluginCommand_ptr;
int *pluginCmdCount_ptr;
pluginCommand *pluginCommands;
int pluginCmdCount;
bool pluginLoaded = false;
void *pluginHandle;

string dylibSuffix = ".so";
#ifdef __MACH__
  string HOME_DIR = "/Users/";
#else
  string HOME_DIR = "/home/";
#endif

bool StackReturnValues(vector<string> R) {
  if (R.size() == 0) return true;
  if (R.at(0) == "false") {
    cout << R.at(1);
    return false;
  }
  int count = 0;
  for (std::vector<string>::iterator it = R.begin(); it != R.end(); ++it) {
    count += 1;
    string c = *it;
    char Type = c.at(0);
    c.erase(c.begin());
    switch (Type) {
      case 'S':
        {
          putStringOnStack(c);
          break;
        }
      case 'I':
        {
          putIntegerOnStack(stoi(c));
          break;
        }
      case 'F':
        {
          putFloatOnStack(stof(c));
          break;
        }
    }
  }
  // to make it easy to use PICK, stack the count
  putIntegerOnStack(count);
  return true;
}

bool handleLoadPlugin() {
  const char* u = std::getenv("USER");
  if (!u) {
    std::cerr << "Failed to get username (USER environment variable not found)." << std::endl;
    return false;
  }
  string username = u;
  string path;
  if (popStringFromStack(&path) == false) {
    logStackOverflow((char *)"handleLoadPlugin");
    return false;
  }
  string pluginPath = HOME_DIR + username + "/.ddForthPlugins/" + path + dylibSuffix;
  // cout << " ==> Loading " << pluginPath << endl;
  // This needs to happen BEFORE dlopen(), IF a library was already opened.
  if (pluginLoaded) dlclose(pluginHandle);
  pluginHandle = dlopen(pluginPath.c_str(), RTLD_LAZY);
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
  // cout << "Command count: " << pluginCmdCount << endl;
  shared_pluginCommand_ptr = (pluginCommand *)dlsym(pluginHandle, "pluginCommands");
  if (!shared_pluginCommand_ptr) {
    fprintf(stderr, "handleLoadPlugin: Error finding symbol 'pluginCommands': %s\n", dlerror());
    dlclose(pluginHandle);
    return false;
  }
  pluginLoaded = true;
  pluginCommands = shared_pluginCommand_ptr;
  for (int ix = 0; ix < pluginCmdCount; ix++) {
    cout << " • " << pluginCommands[ix].name << ":\t" << pluginCommands[ix].help << endl;
    char V = pluginCommands[ix].params.at(0);
    int argc = V - 48;
    cout << "   - Arg count: [" << V << "] " << argc << endl;
    for (int jx = 0; jx < argc; jx++) {
      cout << "   - Arg #" << jx << ": " << pluginCommands[ix].params.at(jx + 1) << endl;
    }
  }
  cout << "Calling handleInit().\n";
  vector<string> params;
  vector<string> R = pluginCommands[0].ptr(params);

  return true;
}

bool lookupPlugin(string c, bool *r) {
  string cc, d;
  cc = c;
  std::transform(cc.begin(), cc.end(), cc.begin(), ::toupper);
  for (int ix = 0; ix < pluginCmdCount; ix++) {
    d = pluginCommands[ix].name;
    // std::transform(d.begin(), d.end(), d.begin(), ::tolower);
    if (cc == d) {
      // We need to check the stack for the proper parameters
      // and prepare a vector
      vector<string> params;
      char V = pluginCommands[ix].params.at(0);
      int argc = V - 48;
      // cout << "   - Arg count: " << argc << endl;
      for (int jx = 0; jx < argc; jx++) {
        char argType = pluginCommands[ix].params.at(jx + 1);
        // cout << "   - Arg #" << jx << ": " << argType;
        string P;
        int I;
        float F;
        switch (argType) {
          case 'S':
            {
              if (popStringFromStack(&P) == false) {
                // cout << " [x]\n";
                logStackOverflow((char *)"lookupPlugin/STR");
                return false;
              }
              // cout << " [√]\n";
              params.push_back(P);
              break;
            }
          case 'I':
            {
              if (popIntegerFromStack(&I) == false) {
                // cout << " [x]\n";
                logStackOverflow((char *)"lookupPlugin/INT");
                return false;
              }
              // cout << " [√]\n";
              params.push_back(std::to_string(I));
              break;
            }
          case 'F':
            {
              if (popFloatFromStack(&F) == false) {
                // cout << " [x]\n";
                logStackOverflow((char *)"lookupPlugin/FLOAT");
                return false;
              }
              // cout << " [√]\n";
              params.push_back(std::to_string(F));
              break;
            }
        }
      }
      // cout << "calling " << pluginCommands[ix].name << endl;
      vector<string> R = pluginCommands[ix].ptr(params);
      if (R.size() > 0) {
        /*
          Return values:
          Instead of returning TRUE/FALSE, return a vector<string> containing:
            • Either {"false", "error message"}
            • Or return values, if any, as strings, prefixed with their type.
              Example: {"I32", "Stagada"}
          These values are put back on the stack.
        */
        return StackReturnValues(R);
      } else return true;
    }
  }
  return false;
}
