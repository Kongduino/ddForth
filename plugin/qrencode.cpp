#include <climits>
#include <cmath> // For sin, cos, tan
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <dlfcn.h>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>
#include "QR-Code-generator/cpp/qrcodegen.hpp"

using namespace std;
using qrcodegen::QrCode;
using qrcodegen::QrSegment;

char msg[256];

struct pluginCommand {
  vector<string> (*ptr)(vector<string>); // Function pointer
  string name;
  string help;
  string params;
};

vector<string> handleInit(vector<string> P) {
  vector<string> R;
  // INIT
  return R;
}

// Prints the given QRCode object to the console.
static void printQr(const QrCode &qr) {
  int border = 4;
  for (int y = -border; y < qr.getSize() + border; y++) {
    for (int x = -border; x < qr.getSize() + border; x++) {
      std::cout << (qr.getModule(x, y) ? "██" : "  ");
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

// Creates a single QR Code, then prints it to the console.
vector<string> handleSimpleQRCode(vector<string> P) {
  // name text QRCODE
  vector<string> R; // the return vector
  if (P.size() != 2) {
    R.push_back("false");
    R.push_back("handleSimpleQRCode: Invalid number of args!\n");
    return R;
  }
  int ix = 0;
  string text = P.at(0);
  string name = P.at(1);
  const QrCode::Ecc errCorLvl = QrCode::Ecc::LOW; // Error correction level
  // Make and print the QR Code symbol
  const QrCode qr = QrCode::encodeText(text.c_str(), errCorLvl);
  printQr(qr);
  return R;
}

pluginCommand pluginCommands[] = {
  // handleInit is compulsory, in position 0
  { handleInit, "INIT", "( -- ) Initializes the plugin, if required.", "0" },
  { handleSimpleQRCode, "QRCODE", "( -- ) Creates a siomple QR code.", "1S" },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
