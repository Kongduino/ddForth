#include <algorithm> // For std::find
#include <cmath>  // For std::sqrt
#include <cstdio>
#include <fcntl.h>
#include <iostream>
#include <map>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

struct CursorPosition {
  int row;
  int col;
};

CursorPosition getCursorPosition() {
  CursorPosition pos = { 0, 0 };
  struct termios old_tio, new_tio;
  // Get current terminal settings
  tcgetattr(STDIN_FILENO, &old_tio);
  new_tio = old_tio;
  // Disable canonical mode and echo
  new_tio.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &new_tio);
  // Send ANSI escape sequence to query cursor position
  if (write(STDOUT_FILENO, "\033[6n", 4) != 4) {
    std::cerr << "Error writing to terminal" << std::endl;
    tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);  // Restore on error
    return pos;
  }
  char buffer[32];
  int bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer) - 1);
  if (bytesRead > 0) {
    buffer[bytesRead] = '\0';  // Null-terminate the string
    std::string response(buffer);
    // Find the 'R' character and parse the numbers
    size_t r_pos = response.find('R');
    if (r_pos != std::string::npos) {
      // Extract the part between '[' and 'R'
      size_t bracket_pos = response.find('[');
      if (bracket_pos != std::string::npos && bracket_pos < r_pos) {
        std::string coords_str = response.substr(bracket_pos + 1, r_pos - (bracket_pos + 1));
        std::vector<std::string> coords = splitString(coords_str, ';');
        if (coords.size() == 2) {
          pos.row = std::stoi(coords[0]);
          pos.col = std::stoi(coords[1]);
        }
      }
    }
  } else {
    std::cerr << "Error reading from terminal or no response" << std::endl;
  }
  // Restore original terminal settings
  tcsetattr(STDIN_FILENO, TCSANOW, &old_tio);
  return pos;
}

void gotoXY(int x, int y) {
  cout << "\033[" << y << ";" << x << "H";
  flush(cout); // Ensure the escape code is sent immediately
}

bool handleGotoXY() {
  // ANSI escape code for cursor positioning: \033[<line>;<column>H
  int x, y;
  if (popIntegerFromStack(&y) == false) {
    logStackOverflow((char *)"handleGotoXY/0");
    return false;
  }
  if (popIntegerFromStack(&x) == false) {
    logStackOverflow((char *)"handleGotoXY/1");
    return false;
  }
  return true;
}

bool handleClearTerminal() {
  cout << "\033[2J\033[1;1H";
  // Clears screen and moves cursor to top-left
  return true;
}


bool handleHexDump() {
  string mySTRING;
  if (popStringFromStack(&mySTRING) == false) {
    logStackOverflow((char *)"handleHexDump/0");
    return false;
  }
  hexDump((unsigned char *)mySTRING.c_str(), mySTRING.length());
  return true;
}

bool handleShowVars() {
  return showVars();
}

bool showVars(int posx, int posy) {
  if (posy == -1) {
    CursorPosition xy = getCursorPosition();
    posy = xy.col;
  }
#if defined(DEBUG)
  cout << endl << "myVARs.size: " << myVARs.size() << " myFVARs.size: " << myFVARs.size()
       << " varAddresses.size: " << varAddresses.size()
       << " fvarAddresses.size: " << fvarAddresses.size() << endl;
  cout << "myCONSTs.size: " << myCONSTs.size() << " myFCONSTs.size: " << myFCONSTs.size()
       << " constAddresses.size: " << constAddresses.size()
       << " fconstAddresses.size: " << fconstAddresses.size();
#endif
  if (myVARs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     |  VAR Name   | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = varAddresses.begin();
    int ix = 0;
    while (it != varAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d | %-30d |",
        (ix++), myVARs.size(), n.c_str(), it->second, myVARs.at(it->second));
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  if (myFVARs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     |  FVAR Name  | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = fvarAddresses.begin();
    int ix = 0;
    while (it != fvarAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d | %-30f |",
        (ix++), myFVARs.size(), n.c_str(), it->second, myFVARs.at(it->second - 128));
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  if (myCONSTs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     |  CONST Name | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = constAddresses.begin();
    int ix = 0;
    while (it != constAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d | %-30d |",
        (ix++), myCONSTs.size(), n.c_str(), it->second, myCONSTs.at(it->second - 256));
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  if (myFCONSTs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     | FCONST Name | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = fconstAddresses.begin();
    int ix = 0;
    while (it != fconstAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d | %-30f |",
        (ix++), myFCONSTs.size(), n.c_str(), it->second, myFCONSTs.at(it->second - 384));
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  if (mySTRVARs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     |  STR Name   | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = strvarAddresses.begin();
    int ix = 0;
    while (it != strvarAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d |`%-29s` |",
        (ix++), mySTRVARs.size(), n.c_str(), it->second, mySTRVARs.at(it->second - 512).c_str());
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  if (mySTRCONSTs.size() > 0) {
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    gotoXY(posx, posy++);
    cout << "| Num     | SCONST Name | Addr | Value                          |";
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
    std::map<string, int>::iterator it = strconstAddresses.begin();
    int ix = 0;
    while (it != strconstAddresses.end()) {
      string n = it->first;
      gotoXY(posx, posy++);
      printf(
        "| %3d/%-3zu | %-11s | %4d |`%-29s` |",
        (ix++), mySTRCONSTs.size(), n.c_str(), it->second, mySTRCONSTs.at(it->second - 640).c_str());
      it++;
    }
    gotoXY(posx, posy++);
    cout << "+---------------------------------------------------------------+";
  }
  cout << endl;
  return true;
}



// end