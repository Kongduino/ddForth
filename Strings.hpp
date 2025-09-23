#include <cmath>  // For std::sqrt
#include <fcntl.h>
#include <map>
#include <cstdio>
#include <iostream>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

extern bool insideString;
extern bool isHelping;

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
  isStackingString = false;
  return true;
}

bool handleHELPSTRING() {
  insideString = true;
  isHelping = true;
  isPrinting = false;
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
  printf("%s", s.c_str());
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

inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}
// Trim from the end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// Trim from both ends (in place)
inline void trim(std::string &s) {
    rtrim(s);
    ltrim(s);
}

// Trim from the start (copying)
inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// Trim from the end (copying)
inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// Trim from both ends (copying)
inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

bool handleSTRIPSTR() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleSTRIPSTR");
    return false;
  }
  s = trim_copy(s);
  putStringOnStack(s);
  return true;
}

bool handleLSTRIPSTR() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleSTRIPSTR");
    return false;
  }
  s = ltrim_copy(s);
  putStringOnStack(s);
  return true;
}

bool handleRSTRIPSTR() {
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleSTRIPSTR");
    return false;
  }
  s = rtrim_copy(s);
  putStringOnStack(s);
  return true;
}

bool handleSTRINT() {
  string s;
  int i0;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleINTSTR");
    return false;
  }
  i0 = std::atoi(s.c_str());
  putIntegerOnStack(i0);
  return true;
}

bool handleINTSTR() {
  string s;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleSTRINT");
    return false;
  }
  s = std::to_string(i0);
  putStringOnStack(s);
  return true;
}

bool handleCSPLIT() {
  // s" this is a string!" 32 CSPLIT
  // this/is/a/string!/4 on the stack
  int i0;
  unsigned char x;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleCSPLIT/1");
    return false;
  }
  x = (i0 & 0xFF);
  string s, T;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleCSPLIT/0");
    return false;
  }
  int ln, ix, lastIX = 0, count = 0;
  ln = s.size();
  for(ix = 0; ix < ln; ix++) {
    char c = s.at(ix);
    if (c == x) {
      T = s.substr (lastIX, ix - lastIX);
      putStringOnStack(T);
      // cout << "Push `" << T << "`." << endl;
      lastIX = ix + 1;
      count += 1;
    }
  }
  if(lastIX < ix) {
    T = s.substr (lastIX, ix - lastIX);
    putStringOnStack(T);
    // cout << "Push `" << T << "`." << endl;
    count += 1;
  }
  putIntegerOnStack(count);
  return true;
}

bool handleSPLITDELIM() {
  string sentence;
  string word;
  string delim;
  int delimLen, count = 0;
  size_t start = 0, end;
  if (popStringFromStack(&delim) == false) {
    logStackOverflow((char *)"handleSPLITDELIM/0");
    return false;
  }
  delimLen = delim.size();
  if (popStringFromStack(&sentence) == false) {
    logStackOverflow((char *)"handleSPLITDELIM/1");
    return false;
  }

  while ((end = sentence.find(delim.c_str(), start)) != string::npos) {
    putStringOnStack(sentence.substr(start, end - start));
    start = end + delimLen;
    count += 1;
  }
  putStringOnStack(sentence.substr(start));
  count += 1;
  putIntegerOnStack(count);
  return true;
}
