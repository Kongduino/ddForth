#include <cmath>  // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

extern bool insideString;

bool handlePRINTSTRING() {
  insideString = true;
  isPrinting = true;
  return true;
}

bool handleSTACKSTRING() {
  insideString = true;
  isStackingString = true;
  return true;
}

bool handlePRINTSTACKSTRING() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handlePRINTSTACKSTRING");
    return false;
  }
  cout << s << " ";
  return true;
}

bool handleAPPENDSTACKSTRING() {
  string s, v;
  if (popStringFromStack(&v) == false) {
    logStackOverflow((char *)"handleAPPENDSTACKSTRING");
    return false;
  }
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleAPPENDSTACKSTRING");
    return false;
  }
  s.append(v);
  putStringOnStack(s);
  return true;
}

bool handleLEFT() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  return true;
}

bool handleRIGHT() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  char c = s.back();
  putIntegerOnStack((int)c);
  return true;
}

bool handleMID() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  
  putStringOnStack(s);
  return true;
}

bool handleLEN() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  putStringOnStack(s);
  putIntegerOnStack(s.size());
  return true;
}


