#include <cstdio>
#include <cstring>
#include <iostream>
#include <string>
#include <filesystem>
namespace fs = std::filesystem;

using namespace std;

char msg[256];

vector<string> handleInit(vector<string> P) {
  vector<string> R;
  // INIT
  // En fait on s'en tape...
  // Map the fonts that are being used.
  return R;
}

vector<string> handleLS(vector<string> P) {
  vector<string> R;
  // path LS
  if (P.size() != 1) {
    R.push_back("false");
    R.push_back("handleLS: Invalid number of args!\n");
    return R;
  }
  string path = P.at(0);
  fs::path dir_path{ path.c_str() };
  try {
    // Check if the path exists and is a directory
    if (fs::exists(dir_path) && fs::is_directory(dir_path)) {
      std::cout << "Listing contents of: " << dir_path.string() << std::endl;
      // Iterate through the directory entries
      for (const auto& entry : fs::directory_iterator(dir_path)) {
        // Print the full path of each entry
        std::cout << entry.path().string() << std::endl;
        R.push_back("S" + entry.path().string());
      }
    } else {
      R.push_back("false");
      int xxxxxx = snprintf((char*)msg, 255,
        "handleLS: Path `%s` does not exist or is not a directory.\n", path.c_str());
      R.push_back(string(msg));
    }
  } catch (const fs::filesystem_error& e) {
    R.push_back("false");
    int xxxxxx = snprintf((char*)msg, 255, "handleLS: Filesystem error: %s", e.what());
    R.push_back(string(msg));
  }
  return R;
}

struct pluginCommand {
  vector<string> (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
  string params;
};

pluginCommand pluginCommands[] = {
  // handleInit is compulsory, in position 0
  { handleInit, "INIT", "( -- ) Initializes the plugin, if required.", "0" },
  { handleLS, "LS", "( path -- ) Lists file on path", "1S" },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
