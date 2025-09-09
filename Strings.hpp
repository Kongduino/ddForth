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

bool handleEMIT() {
  char c;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleEMIT1");
    return false;
  }
  c = i0;
  printf("%c", c);
  return true;
}

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
  // cout << "handlePRINTSTACKSTRING ";
  printf("%s ", s.c_str());
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

bool handlePREPENDSTACKSTRING() {
  string s, v;
  if (popStringFromStack(&v) == false) {
    logStackOverflow((char *)"handleAPPENDSTACKSTRING");
    return false;
  }
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleAPPENDSTACKSTRING");
    return false;
  }
  v.append(s);
  putStringOnStack(v);
  return true;
}

bool handleLEFT() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  char c = s.front();
  putStringOnStack(s);
  putIntegerOnStack((int)c);
  return true;
}

bool handleRIGHT() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLEFT");
    return false;
  }
  char c = s.back();
  putStringOnStack(s);
  putIntegerOnStack((int)c);
  return true;
}

bool handleMID() {
  string s;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleMID1");
    return false;
  }
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleMID2");
    return false;
  }
  putStringOnStack(s);
  putIntegerOnStack(s.at(i0));
  return true;
}

bool handleSUBSTR() {
  string s;
  int i0, i1;
  if (popIntegerFromStack(&i1) == false) {
    logStackOverflow((char *)"handleMID1");
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleMID2");
    return false;
  }
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleMID3");
    return false;
  }
  putStringOnStack(s);
  // cout << "handleSUBSTR `" << s << "` "<< i0 << ":" << i1 <<" ie `" << s.substr(i0, i1) << "` ";
  putStringOnStack(s.substr(i0, i1));
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

bool handleLowercase() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleLowercase");
    return false;
  }
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  putStringOnStack(s);
  return true;
}

bool handleUppercase() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleUppercase");
    return false;
  }
  std::transform(s.begin(), s.end(), s.begin(), ::toupper);
  putStringOnStack(s);
  return true;
}

bool handleMULTSTR() {
  string s, v;
  int i, i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleMULTSTR1");
    return false;
  }
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleMULTSTR2");
    return false;
  }
  for(i = 0; i < i0; i++)
    v.append(s);
  putStringOnStack(v);
  return true;
}
