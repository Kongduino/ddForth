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
string hexDigits = "0123456789abcdef";

bool handleEMIT() {
  char c;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleEMIT/0");
    return false;
  }
  c = i0;
  printf("%c", c);
  return true;
}

bool handleASC2CHR() {
  char c;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleASC2CHR/0");
    return false;
  }
  c = i0;
  xxxxxx = snprintf((char *)msg, 255, "%c", c);
  putStringOnStack(msg);
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
    logStackOverflow((char *)"handleLEN");
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
    logStackOverflow((char *)"handleSTRINT");
    return false;
  }
  i0 = std::atoi(s.c_str());
  putIntegerOnStack(i0);
  return true;
}

bool handleSTRFLOAT() {
  string s;
  float f0;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleSTRFLOAT");
    return false;
  }
  f0 = std::atof(s.c_str());
  putFloatOnStack(f0);
  return true;
}

bool handleINTSTR() {
  string s;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleINTSTR");
    return false;
  }
  s = std::to_string(i0);
  putStringOnStack(s);
  return true;
}

bool handleFLOATSTR() {
  string s;
  float f0;
  if (popFloatFromStack(&f0) == false) {
    logStackOverflow((char *)"handleFLOATSTR");
    return false;
  }
  s = std::to_string(f0);
  putStringOnStack(s);
  return true;
}

bool handleCSPLIT() {
  // s" this is a string!" 32 CSPLIT
  // this/is/a/string!/4 on the stack
  int i0;
  unsigned char x;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleCSPLIT/i0");
    return false;
  }
  x = (i0 & 0xFF);
  string s, T;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleCSPLIT/s0");
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
  if (delimLen == 0) {
    // Special case!
    int i, j;
    j = sentence.length();
    for (int i = 0; i < j; ++i) {
      string nn = sentence.substr(i, 1);
      putStringOnStack(nn);
    }
    putIntegerOnStack(j);
    return true;
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

bool handleStringReverse() {
  // ( s0 s1 s2 s3 s4... n -- sx... s4 s3 s2 s1 n )
  // Reverses a stack of strings prefixed by count
  int ix, jx, number;
  if(popIntegerFromStack(&number) == false) {
    logStackOverflow((char *)"handleStringReverse/0");
    return false;
  }
  for (ix = 0; ix < number; ix++) {
    if(dataStack.at(dataStack.size() - 1 - ix) != xSTRING) {
      logInconsistent((char*)"handleStringReverse");
      return false;
    }
  }
  jx = ix >> 1;
  for (ix = 0; ix < jx; ix++) {
    string tmp = userStrings.at(userStrings.size() - 1 - ix);
    userStrings.at(userStrings.size() - 1 - ix) = userStrings.at(userStrings.size() - (number - ix));
    userStrings.at(userStrings.size() - (number - ix)) = tmp;
  }
  putIntegerOnStack(number);
  return true;
}

bool handleStringEqual() {
  string s0, s1;
  if (popStringFromStack(&s0) == false) {
    logStackOverflow((char *)"handleStringEqual/0");
    return false;
  }
  if (popStringFromStack(&s1) == false) {
    logStackOverflow((char *)"handleStringEqual/1");
    return false;
  }
  putIntegerOnStack((s0 == s1));
  return true;
}

bool handleDINSERT() {
  string s0, s1, fnStr;
  int ix, n, ln;
  if(popIntegerFromStack(&n) == false) {
    logStackOverflow((char *)"handleDINSERT/1");
    return false;
  }
  if (popStringFromStack(&s0) == false) {
    logStackOverflow((char *)"handleDINSERT/0");
    return false;
  }
  if (popStringFromStack(&s1) == false) {
    logStackOverflow((char *)"handleDINSERT/2");
    return false;
  }
  ln = s1.size();
  fnStr = s1.substr(0, n);
  for (ix = n ; ix < ln; ix += n) {
    fnStr.append(s0);
    fnStr.append(s1.substr(ix, n));
  }
  putStringOnStack(fnStr);
  return true;
}

bool handleStringReplace() {
  string s0, s1, s2;
  if (popStringFromStack(&s2) == false) {
    logStackOverflow((char *)"handleDINSERT/0");
    return false;
  }
  if (popStringFromStack(&s1) == false) {
    logStackOverflow((char *)"handleDINSERT/1");
    return false;
  }
  if (popStringFromStack(&s0) == false) {
    logStackOverflow((char *)"handleDINSERT/2");
    return false;
  }
  size_t pos = s0.find(s1);
  // Iterate through the string and replace all
  // occurrences
  while (pos != string::npos) {
    s0.replace(pos, s1.size(), s2);
    pos = s0.find(s1, pos + s2.size());
  }
  putStringOnStack(s0);
  return true;
}

bool handleSlicer() {
  int ln, ix, i0, runlength = 0, count = 0;
  if (popIntegerFromStack(&ln) == false) {
    logStackOverflow((char *)"handleSlicer/0");
    return false;
  }
  vector<int> slices;
  for(ix = 0; ix < ln; ix++) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSlicer/1");
      return false;
    }
    slices.push_back(i0);
    count += i0;
  }
  string s0;
  if (popStringFromStack(&s0) == false) {
    logStackOverflow((char *)"handleDINSERT/2");
    return false;
  }
  if (count != s0.length()) {
    cout << "Slices don't match string length!\n";
    return false;
  }
  for(ix = 0; ix < ln; ix++) {
    i0 = slices.at(ln - ix - 1);
    putStringOnStack(s0.substr(runlength, i0));
    runlength += i0;
  }
  return true;
}

bool handleHEX2NUM() {
  // ( s -- n )
  string s;
  if (popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleHEX2NUM/0");
    return false;
  }
  std::transform(s.begin(), s.end(), s.begin(), ::tolower);
  size_t found;
  uint32_t result = 0;
  for (int ix = 0; ix < s.length(); ix++) {
    result = result * 16;
    found = hexDigits.find(s.at(ix));
    if (found == string::npos) {
      logInconsistent((char*)"handleHEX2NUM");
      return false;
    }
    result += found;
    // cout << s.at(ix) << " = " << found << ", result = " << result << endl;
  }
  putIntegerOnStack(result);
  return true;
}


// end