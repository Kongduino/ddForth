#include "ddforth.hpp"
bool insideString;

using namespace std;

void StoreCONSTFLOAT(string name, float value) {
  map<string, int>::iterator it;
  it = fconstAddresses.find(name);
  if (it == fconstAddresses.end()) {
    myFCONSTs.push_back(value);
    fconstAddresses[name] = myFCONSTs.size() - 1 + 384;
    xxxxxx = snprintf((char *)msg, 255, "FCONST %s created as %f\n", name.c_str(), value);
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "FCONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreCONSTINT(string name, int value) {
  map<string, int>::iterator it;
  it = constAddresses.find(name);
  if (it == constAddresses.end()) {
    myCONSTs.push_back(value);
    constAddresses[name] = myCONSTs.size() - 1 + 256;
    xxxxxx = snprintf((char *)msg, 255, "CONST %s created as %d\n", name.c_str(), value);
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "CONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreFLOAT(string name, float value) {
  map<string, int>::iterator it;
  it = fvarAddresses.find(name);
  if (it != fvarAddresses.end()) {
    xxxxxx = snprintf((char *)msg, 255, "FVAR %s found at %d\n", name.c_str(), (it->second));
    logThis();
    myFVARs.at(it->second) = value;
  } else {
    myFVARs.push_back(value);
    fvarAddresses[name] = myFVARs.size() - 1 + 128;
    xxxxxx = snprintf(
      (char *)msg, 255,
      "FVAR %s created at %d. fvarAddresses.size: %zu. myFVARs.size: %zu\n",
      name.c_str(), fvarAddresses[name], fvarAddresses.size(), myFVARs.size());
    logThis();
  }
}

void StoreINT(string name, int value) {
  map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    myVARs.at(it->second) = value;
  } else {
    myVARs.push_back(value);
    varAddresses[name] = myVARs.size() - 1;
  }
}

void StoreINTaddress(int ad, int value) {
  myVARs.at(ad) = value;
}

int GetINT(string name) {
  map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    return myVARs.at(it->second);
  } else {
    return -1;
  }
}

int GetINTaddress(string name) {
  map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    return it->second;
  } else {
    return -1;
  }
}

bool handleRput() {
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleRput");
    return false;
  }
  putIntegerOnJumpStack(i0);
  return true;
}

bool handleRget() {
  if (jumpStack.size() == 0) {
    logStackOverflow((char *)"handleRget");
    return false;
  }
  int i0;
  if (popIntegerFromJumpStack(&i0) == false) {
    logJumpStackOverflow((char *)"handleRget");
    return false;
  }
  putIntegerOnStack(i0);
  return true;
}

bool handleWORDS() {
  cout << "Handled in Code:" << endl << "----------------" << endl;
  for (vector<string>::iterator it = computedWords.begin(); it != computedWords.end(); ++it) {
    string s = *it;
    printf(" • %-11s (Handled in code)\n", s.c_str());
  }
  cout << endl << "Native Commands:" << endl << "----------------" << endl;
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    // printf(" • %-11s (Native command)\n", nativeCommands[ix].name.c_str());
    cout << nativeCommands[ix].name << " ";
  }
  cout << endl << endl << "User Commands:" << endl << "--------------" << endl;
  for (vector<userCommand>::iterator it = userCommands.begin(); it != userCommands.end(); ++it) {
    printf(" • %-11s %s\n", it->name.c_str(), it->command.c_str());
  }
  return true;
}

bool handleSETINT() {
  float f0;
  int i0;
  if (popFloatFromStack(&f0) == false) {
    logStackOverflow((char *)"handleSETINT f0");
    return false;
  }
  i0 = f0;
  putIntegerOnStack(i0);
  return true;
}

bool handleDO() {
  // Max min DO ... LOOP
  xxxxxx = snprintf((char *)msg, 255, "\n\n--> DO at executionPointer: %d ", executionPointer);
  logThis();
  if (dataStack.size() < 2) {
    cout << "Stack empty! ";
    return true;
  }
  int max, min;
  if (popIntegerFromStack(&min) == false) {
    logStackOverflow((char *)"handleLOOP");
    return false;
  }
  if (popIntegerFromStack(&max) == false) {
    logStackOverflow((char *)"handleLOOP");
    return false;
  }
  loopStack.push_back(max);
  loopStack.push_back(min);
  xxxxxx = snprintf(
    (char *)msg, 255,
    "Setting up DO...LOOP with min = %d, max = %d.\n",
    min, max);
  logThis();
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xDO);
  return true;
}

bool checkDOLOOPconditions(char *who) {
  if (jumpStack.size() == 0) {
    logJumpStackOverflow(who);
    return false;
  }
  if (loopStack.size() < 2) {
    logLoopStackOverflow(who);
    return false;
  }
  int type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xDO) {
    xxxxxx = snprintf((char *)msg, 255, "%s xDO not on JumpStack!\n", who);
    logThis();
    return false;
  }
  return true;
}

// handleLOOP
// pop two identical-type values
// compare and loop if needed
bool handleLOOP() {
  int min, max;
  if (!checkDOLOOPconditions((char *)"handleLOOP")) return false;
  xxxxxx = snprintf(
    (char *)msg, 255,
    "handleLOOP JumpStack: %zu loopStack: %zu\n",
    jumpStack.size(), loopStack.size());
  logThis();
  if (popFromLoopStack(&min) == false) {
    logStackOverflow((char *)"handleLOOP min");
    return false;
  }
  if (popFromLoopStack(&max) == false) {
    logStackOverflow((char *)"handleLOOP max");
    return false;
  }
  min += 1;
  xxxxxx = snprintf(
    (char *)msg, 255,
    "DO...LOOP: min = %d, max = %d.\n",
    min, max);
  logThis();
  if (min < max) {
    xxxxxx = snprintf((char *)msg, 255, "LOOPing back\n");
    logThis();
    loopStack.push_back(max);
    loopStack.push_back(min);
    executionPointer = jumpStack.at(jumpStack.size() - 1);
  } else {
    xxxxxx = snprintf((char *)msg, 255, "LOOP THE END.\n");
    logThis();
    jumpStack.pop_back();
    jumpStackType.pop_back();
  }
#if defined(DEBUG)
  showStack();
#endif
  return true;
}

bool handleI() {
  if (!checkDOLOOPconditions((char *)"handleI")) return false;
  putIntegerOnStack(loopStack.at(loopStack.size() - 1));
  return true;
}

bool handleIprime() {
  if (!checkDOLOOPconditions((char *)"handleIprime")) return false;
  putIntegerOnStack(loopStack.at(loopStack.size() - 2));
  return true;
}

bool handleJ() {
  if (!checkDOLOOPconditions((char *)"handleJ")) return false;
  if (loopStack.size() < 4) return false;
  putIntegerOnStack(loopStack.at(loopStack.size() - 3));
  return true;
}

bool handleBEGIN() {
  // BEGIN ... <condition> UNTIL
  xxxxxx = snprintf((char *)msg, 255, "\n\n--> BEGIN at ");
  logThis();
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xBEGIN);
  xxxxxx = snprintf((char *)msg, 255, "%d\n", executionPointer);
  logThis();
  return true;
}

bool isUNTIL = true;
bool handleUNTILWHILE() {
  xxxxxx = snprintf((char *)msg, 255, "\n--> UNTILWHILE at %d. JumpStack size: %zu\n", executionPointer, jumpStack.size());
  logThis();
  int i0, type0;
  if (jumpStack.size() == 0) {
    xxxxxx = snprintf((char *)msg, 255, "handleUNTILWHILE JumpStack overflow!\n");
    logThis();
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
    xxxxxx = snprintf((char *)msg, 255, "handleUNTILWHILE xBEGIN not on JumpStack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleUNTILWHILE");
    return false;
  }
#if defined(DEBUG)
  showStack();
#endif
  if (i0 < 0 || i0 > 1) {
    xxxxxx = snprintf((char *)msg, 255, "handleUNTILWHILE %d is not a BOOLEAN!\n", i0);
    logThis();
    return false;
  }
  xxxxxx = snprintf((char *)msg, 255, "Condition is %s\n", ((i0 == 1) ? "true" : "false"));
  logThis();
  if ((i0 == 0 && isUNTIL) || (i0 == 1 && !isUNTIL)) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
    xxxxxx = snprintf((char *)msg, 255, " looping back to %d. Condition: %d.\n", executionPointer, i0);
    logThis();
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
    xxxxxx = snprintf((char *)msg, 255, " Ending BEGIN. Condition: %d.\n", i0);
    logThis();
  }
  return true;
}

bool handleUNTIL() {
  isUNTIL = true;
  return handleUNTILWHILE();
}

bool handleWHILE() {
  isUNTIL = false;
  return handleUNTILWHILE();
}

bool showVars() {
  cout << "myVARs.size: " << myVARs.size() << " myFVARs.size: " << myFVARs.size()
       << " varAddresses.size: " << varAddresses.size()
       << " fvarAddresses.size: " << fvarAddresses.size() << endl;
  cout << "myCONSTs.size: " << myCONSTs.size() << " myFCONSTs.size: " << myFCONSTs.size()
       << " constAddresses.size: " << constAddresses.size()
       << " fconstAddresses.size: " << fconstAddresses.size() << endl;
  if (myVARs.size() > 0) {
    cout << "+-----------------------------------------+" << endl;
    cout << "| Num     |  VAR Name   | Addr | Value    |";
    cout << endl << "+-----------------------------------------+" << endl;
    map<string, int>::iterator it = varAddresses.begin();
    int ix = 0;
    while (it != varAddresses.end()) {
      string n = it->first;
      printf(
        "| %3d/%-3zu | %-11s | %4d |%9d |\n",
        (ix++), myVARs.size(), n.c_str(), it->second, myVARs.at(it->second));
      it++;
    }
    cout << "+-----------------------------------------+" << endl;
  }
  if (myFVARs.size() > 0) {
    cout << "+-----------------------------------------+" << endl;
    cout << "| Num     | FVAR Name   | Addr | Value    |";
    cout << endl << "+-----------------------------------------+" << endl;
    map<string, int>::iterator it = fvarAddresses.begin();
    int ix = 0;
    while (it != fvarAddresses.end()) {
      string n = it->first;
      printf(
        "| %3d/%-3zu | %-11s | %4d |%8f |\n",
        (ix++), myFVARs.size(), n.c_str(), it->second, myFVARs.at(it->second - 128));
      it++;
    }
    cout << "+-----------------------------------------+" << endl;
  }
  if (myCONSTs.size() > 0) {
    cout << "+-----------------------------------------+" << endl;
    cout << "| Num     |  CONST Name | Addr | Value    |";
    cout << endl << "+-----------------------------------------+" << endl;
    map<string, int>::iterator it = constAddresses.begin();
    int ix = 0;
    while (it != constAddresses.end()) {
      string n = it->first;
      printf(
        "| %3d/%-3zu | %-11s | %4d |%9d |\n",
        (ix++), myCONSTs.size(), n.c_str(), it->second, myCONSTs.at(it->second - 256));
      it++;
    }
    cout << "+-----------------------------------------+" << endl;
  }
  if (myFCONSTs.size() > 0) {
    cout << "+-----------------------------------------+" << endl;
    cout << "| Num     | FCONST Name | Addr | Value    |";
    cout << endl << "+-----------------------------------------+" << endl;
    map<string, int>::iterator it = fconstAddresses.begin();
    int ix = 0;
    while (it != fconstAddresses.end()) {
      string n = it->first;
      printf(
        "| %3d/%-3zu | %-11s | %4d |%8f |\n",
        (ix++), myFCONSTs.size(), n.c_str(), it->second, myFCONSTs.at(it->second - 384));
      it++;
    }
    cout << "+-----------------------------------------+" << endl;
  }
  return true;
}

bool handleCR() {
  cout << endl;
  return true;
}

bool handleStore() {
  xxxxxx = snprintf((char *)msg, 255, "handleStore: userIntegers.size %zu dataStack.size() %zu ", userIntegers.size(), dataStack.size());
  logThis();
  if (dataStack.size() < 2) {
    logStackOverflow((char *)"handleStore");
    return false;
  }
  // We are not necessarily storing an int
  // check the type of the address vs type in the stack
  // ie 0-127, 256-383 = int, else float
  int ad, x;
  float fx;
  if (dataStack.at(dataStack.size() - 1) == xINTEGER) {
    if (popIntegerFromStack(&x) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleStore on top!\n");
      logThis();
      return false;
    }
    xxxxxx = snprintf((char *)msg, 255, "handleStore pop Int successful!\n");
    logThis();
  } else if (dataStack.at(dataStack.size() - 1) == xFLOAT) {
    if (popFloatFromStack(&fx) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleStore No Float on top!\n");
      logThis();
      return false;
    }
    xxxxxx = snprintf((char *)msg, 255, "handleStore pop Float successful!\n");
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "handleStore no Int nor Float on top!\n");
    logThis();
    return true;
  }
  if (dataStack.at(dataStack.size() - 1) != xINTEGER) {
    xxxxxx = snprintf((char *)msg, 255, "handleStore No Int Address!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
    logStackOverflow((char *)"handleStore2");
    return false;
  }
  xxxxxx = snprintf((char *)msg, 255, "handleStore Int Address : %d.\n", ad);
  logThis();
  if (ad < 128) {
    xxxxxx = snprintf((char *)msg, 255, "storing %d into myVARs[%d].\n", x, ad);
    logThis();
    myVARs.at(ad) = x;
  } else if (ad < 256) {
    xxxxxx = snprintf((char *)msg, 255, "storing %f into myFVARs[%d].\n", fx, ad);
    logThis();
    myFVARs.at(ad - 128) = fx;
  } else if (ad < 384) {
    xxxxxx = snprintf((char *)msg, 255, "storing %d into myCONSTs[%d].\n", x, ad);
    logThis();
    myCONSTs.at(ad - 256) = x;
  } else {
    xxxxxx = snprintf((char *)msg, 255, "storing %f into myFCONSTs[%d].\n", fx, ad);
    logThis();
    myFCONSTs.at(ad - 384) = fx;
  }
  return true;
}

bool handleStorePlus() {
  xxxxxx = snprintf((char *)msg, 255, "handleStorePlus: userIntegers.size %zu dataStack.size() %zu ", userIntegers.size(), dataStack.size());
  logThis();
  if (dataStack.size() < 1) {
    logStackOverflow((char *)"handleStorePlus");
    return false;
  }
  // We are not necessarily storing an int
  // check the type of the address vs type in the stack
  // ie 0-127, 256-383 = int, else float
  int ad, x;
  float fx;
  if (dataStack.at(dataStack.size() - 1) != xINTEGER) {
    xxxxxx = snprintf((char *)msg, 255, "handleStorePlus No Int Address!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
    logStackOverflow((char *)"handleStorePlus2");
    return false;
  }
  xxxxxx = snprintf((char *)msg, 255, "handleStorePlus Int Address : %d.\n", ad);
  logThis();
  if (ad < 128) {
    xxxxxx = snprintf((char *)msg, 255, "storing %d into myVARs[%d].\n", x, ad);
    logThis();
    myVARs.at(ad) += 1;
    return true;
  } else if (ad < 256) {
    xxxxxx = snprintf((char *)msg, 255, "storing %f into myFVARs[%d].\n", fx, ad);
    logThis();
    myFVARs.at(ad - 128) += 1.0;
    return true;
  }
  return false;
}

bool handleRetrieve() {
  logStack((char *)"handleRetrieve");
  if (!checkTypes(1, xINTEGER)) {
    xxxxxx = snprintf((char *)msg, 255, "handleRetrieve Not enough integers!\n");
    logThis();
    return false;
  }
  int ad;
  if (popIntegerFromStack(&ad) == false) {
    logStackOverflow((char *)"handleRetrieve1");
    return false;
  }
  xxxxxx = snprintf((char *)msg, 255, "handleRetrieve end %d ", ad);
  logThis();
  if (ad < 128) return putIntegerOnStack(myVARs.at(ad));
  else if (ad < 256) return putFloatOnStack(myFVARs.at(ad - 128));
  else if (ad < 384) putIntegerOnStack(myCONSTs.at(ad - 256));
  else return putFloatOnStack(myFCONSTs.at(ad - 384));
  return true;
}

bool printOtherBases(int number, unsigned int base) {
  if (base > 16) {
    StoreINT("BASE", 16);
    base = 16;
  }
  unsigned int uNumber = number;
  xxxxxx = snprintf((char *)msg, 255, " Printing %d in base %d\n", uNumber, base);
  logThis();
  char buffer[32] = { 0 };
  unsigned char ix = 0;
  while (uNumber >= base) {
    int q = uNumber % base;
    uNumber = uNumber / base;
    buffer[ix++] = numerics[q];
  }
  buffer[ix] = numerics[uNumber];
  int n = 0;
  while (n < (ix >> 1)) {
    unsigned char b = buffer[n];
    buffer[n] = buffer[ix - n];
    buffer[ix - n] = b;
    n += 1;
  }
  printf("%s ", buffer);
  return true;
}

bool handleKEY() {
  xxxxxx = snprintf((char *)msg, 255, "handleKEY\n");
  logThis();
  char ch;
  // Set the terminal to raw mode
  system("stty raw");
  ch = getchar();
  // Set the terminal to normal mode
  system("stty sane");
  xxxxxx = snprintf((char *)msg, 255, "handleKEY has received char `%c`, ASCII 0x%02x\n", ch, ch);
  logThis();
  putIntegerOnStack(ch);
  return true;
}

bool handleLINE() {
  string s;
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, s); // Reads the entire line
  return putStringOnStack(s);
}

bool handlePRINT() {
  logStack((char *)"handlePRINT");
  if (dataStack.size() == 0) {
    logStackOverflow((char *)"handlePRINT");
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        int i0;
        if (popIntegerFromStack(&i0) == false) {
          logStackOverflow((char *)"handlePRINT1");
          return false;
        }
        int base = GetINT("BASE");
        if (base == 10) cout << i0 << " ";
        else printOtherBases(i0, base);
        break;
      }
    case xFLOAT:
      {
        float f0;
        if (popFloatFromStack(&f0) == false) {
          logStackOverflow((char *)"handlePRINT2");
          return false;
        }
        printf("%f ", f0);
        break;
      }
  }
  return true;
}

bool handleUPRINT() {
  logStack((char *)"handleUPRINT");
  if (dataStack.size() == 0) {
    logStackOverflow((char *)"handleUPRINT");
    return false;
  }
  if (GetINT("BASE") != 10) {
    xxxxxx = snprintf((char *)msg, 255, "handleUPRINT only works in base 10!\n");
    logThis();
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        unsigned int i0;
        if (popIntegerFromStack((int *)&i0) == false) {
          logStackOverflow((char *)"handleUPRINT1");
          return false;
        }
        cout << i0 << " ";
        break;
      }
    case xFLOAT:
      {
        xxxxxx = snprintf((char *)msg, 255, "handleUPRINT only works with integers!\n");
        logThis();
        return false;
      }
  }
  return true;
}

bool lookupVAR(string name) {
  map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    // found it
    putIntegerOnStack(it->second);
    return true;
  }
  it = fvarAddresses.find(name);
  if (it != fvarAddresses.end()) {
    // found it
    putIntegerOnStack(it->second);
    return true;
  }

  it = constAddresses.find(name);
  if (it != constAddresses.end()) {
    // found it
    putIntegerOnStack(it->second);
    // 0 --> 255 = var
    // 256 --> xxx = const
    return true;
  }
  it = fconstAddresses.find(name);
  if (it != fconstAddresses.end()) {
    // found it
    putIntegerOnStack(it->second);
    // 0 --> 255 = var
    // 256 --> xxx = const
    return true;
  }
  xxxxxx = snprintf((char *)msg, 255, "No VAR/CONST called: %s\n", name.c_str());
  logThis();
  return false;
}

bool lookupUC(string name) {
  xxxxxx = snprintf((char *)msg, 255, "lookupUC %s ", name.c_str());
  logThis();
  for (int ix = 0; ix < userCommands.size(); ix++) {
    xxxxxx = snprintf((char *)msg, 255, "%s ", userCommands[ix].name.c_str());
    logThis();
    if (name == userCommands[ix].name) {
      char cc[256];
      strcpy(cc, userCommands[ix].command.c_str());
      xxxxxx = snprintf((char *)msg, 255, "tokenize %s ", userCommands[ix].command.c_str());
      logThis();
      int savedExecutionPointer = executionPointer;
      vector<string> myChunks;
      myChunks = tokenize(cc, myChunks);
      evaluate(myChunks);
      executionPointer = savedExecutionPointer;
      return true;
    }
  }
  xxxxxx = snprintf((char *)msg, 255, "No user word called: %s\n", name.c_str());
  logThis();
  return false;
}

bool lookup(string c, bool *r) {
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    if (c == nativeCommands[ix].name) {
      *r = nativeCommands[ix].ptr();
      return true;
    }
  }
  return false;
}

bool isInteger(string c, int *i0) {
  int sign = 1;
  if (c.length() == 0) return false;
  int base = GetINT("BASE");
  xxxxxx = snprintf((char *)msg, 255, "isInteger/%d/%s", base, c.c_str());
  logThis();
  string nums("0123456789ABCDEF");
  nums = nums.substr(0, base);
  if (base == 10 && c.at(0) == '-') {
    sign = -1;
    c.erase(0, 1);
  }
  string::const_iterator it = c.begin();
  while (it != c.end() && nums.find(*it) != string::npos) ++it;
  if (c.empty() || it != c.end()) {
    xxxxxx = snprintf((char *)msg, 255, "%s is not an int.\n", c.c_str());
    logThis();
    return false;
  }
  try {
    *i0 = stoi(c, nullptr, base) * sign;
    return true;
  } catch (const invalid_argument &e) {
    xxxxxx = snprintf((char *)msg, 255, "Invalid argument for '%s': %s\n", c.c_str(), e.what());
    logThis();
  } catch (const out_of_range &e) {
    xxxxxx = snprintf((char *)msg, 255, "Out of range for '%s': %s\n", c.c_str(), e.what());
    logThis();
  }
  return false;
}

bool isFloat(string c, float *f0) {
  if (c.length() == 0) return false;
  xxxxxx = snprintf((char *)msg, 255, "isFloat: %s?\n", c.c_str());
  logThis();
  if (GetINT("BASE") == 10) {
    try {
      *f0 = stof(c);
      return true;
    } catch (const invalid_argument &e) {
      xxxxxx = snprintf((char *)msg, 255, "Invalid argument for '%s': %s\n", c.c_str(), e.what());
      logThis();
    } catch (const out_of_range &e) {
      xxxxxx = snprintf((char *)msg, 255, "Out of range for '%s': %s\n", c.c_str(), e.what());
      logThis();
    }
  } else {
    xxxxxx = snprintf((char *)msg, 255, "Only works for base 10!\n");
    logThis();
  }
  return false;
}

bool handleEXEC() {
  string s;
  if(popStringFromStack(&s) == false) {
    logStackOverflow((char *)"handleEXEC");
    return false;
  }
  cout << s << endl;
  int savedExecutionPointer = executionPointer;
  vector<string> myChunks;
  myChunks = tokenize((char *)s.c_str(), myChunks);
  evaluate(myChunks);
  executionPointer = savedExecutionPointer;
  return true;
}

void evaluate(vector<string> chunks) {
  bool r;
  int i0;
  float f0;
  xxxxxx = snprintf((char *)msg, 255, "Evaluating:\n");
  logThis();
#if defined(DEBUG)
  for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) cout << *it << " ";
  cout << endl;
  showStack();
#endif
  executionPointer = 0;
  while (executionPointer < chunks.size()) {
    // executionPointer is global so that BEGIN – and later others – can change it.
    string c = chunks.at(executionPointer);
    xxxxxx = snprintf((char *)msg, 255, "\nEvaluating '%s' executionPointer: %d \n", c.c_str(), executionPointer);
    logThis();
#if defined(DEBUG)
    cout << "+-------+---------------------------------------------------+" << endl;
    for (int xx = 0; xx < chunks.size(); xx++) {
      printf("|%c%-5d | %-50s|\n", ((xx == executionPointer) ? '*' : ' '), xx, chunks.at(xx).c_str());
    }
    cout << "+-------+---------------------------------------------------+" << endl;
#endif
    if (lookupVAR(c)) {
      xxxxxx = snprintf((char *)msg, 255, "Put address of %s on stack. ", c.c_str());
      logThis();
      executionPointer += 1;
    } else if (c == "VAR" || c == "CONST") {
      // creation of a variable
      executionPointer += 1;
      string d = chunks.at(executionPointer++);
      int i0;
      float f0;
      bool valid = true;
      if (isInteger(d, &i0)) valid = false;
      else if (isFloat(d, &f0)) valid = false;
      if (!valid) {
        cout << endl << ((c == "VARINT") ? "VAR" : "CONST") << " name: `" << c << "` is not valid!" << endl;
        return;
      }
      bool thisIsInt = false;
      bool thisIsFloat = false;
      // we need a number
      if (popIntegerFromStack(&i0) == false) {
        xxxxxx = snprintf((char *)msg, 255, "No INT on the stack!\n");
        logThis();
        if (popFloatFromStack(&f0) == false) {
          xxxxxx = snprintf((char *)msg, 255, "No FLOAT on the stack either!\n");
          logThis();
        } else {
          thisIsFloat = true;
        }
      } else thisIsInt = true;
      if (!thisIsFloat && !thisIsInt) return;
      if (c == "VAR" && thisIsInt) {
        xxxxxx = snprintf((char *)msg, 255, "INT VAR name: %s initialized with %d\n", d.c_str(), i0);
        logThis();
        StoreINT(d, i0);
      } else if (c == "VAR" && thisIsFloat) {
        xxxxxx = snprintf((char *)msg, 255, "FLOAT VAR name: %s initialized with %f\n", d.c_str(), f0);
        logThis();
        StoreFLOAT(d, f0);
      } else if (c == "CONST" && thisIsInt) {
        xxxxxx = snprintf((char *)msg, 255, "INT CONST name: %s initialized with %d\n", d.c_str(), i0);
        logThis();
        StoreCONSTINT(d, i0);
      } else if (c == "CONST" && thisIsFloat) {
        xxxxxx = snprintf((char *)msg, 255, "FLOAT CONST name: %s initialized with %f\n", d.c_str(), f0);
        logThis();
        StoreCONSTFLOAT(d, f0);
      }
    } else if (insideString && c.back() == '"') {
      c.pop_back();
      insideString = false;
      if(isStackingString) {
        isStackingString = false;
        putStringOnStack(c);
#if defined(NEED_SDL)
      } else if(isDrawing) {
        drawText(c);
#endif
      } else {
        cout << c << " ";
        isPrinting = false;
      }
      executionPointer += 1;
    } else if (c == ":") {
      // creation of a word
      executionPointer += 1;
      bool done = false, error = true;
      string miniChunks, dictName;
      dictName = chunks.at(executionPointer++);
      xxxxxx = snprintf((char *)msg, 255, "WORD name: %s: ", dictName.c_str());
      logThis();
      while (executionPointer < chunks.size() && !done) {
        c = chunks.at(executionPointer);
        xxxxxx = snprintf((char *)msg, 255, "%s %d / %zu ", c.c_str(), executionPointer, chunks.size());
        logThis();
        if (c == ";") {
          done = true;
          error = false;
          executionPointer += 1;
          xxxxxx = snprintf((char *)msg, 255, " got a ;! ");
          logThis();
        } else {
          miniChunks.append(c);
          miniChunks.append(" ");
          executionPointer += 1;
        }
      }
      if (error) {
        xxxxxx = snprintf((char *)msg, 255, "Missing ; after : sequence! %s\n", miniChunks.c_str());
        logThis();
        return;
      }
      xxxxxx = snprintf((char *)msg, 255, "Adding word `%s` with `%s`\n", dictName.c_str(), miniChunks.c_str());
      logThis();
      userCommand x = { dictName, miniChunks };
      userCommands.push_back(x);
    } else {
      if (lookup(c, &r)) {
        if (r == false) {
          cout << c << " returned false. Aborting!" << endl;
          return;
        }
        executionPointer += 1;
      } else if (lookupUC(c)) {
        xxxxxx = snprintf((char *)msg, 255, "%s lookupUC\n", c.c_str());
        logThis();
        executionPointer += 1;
      } else if (isInteger(c, &i0)) {
        putIntegerOnStack(i0);
        executionPointer += 1;
        xxxxxx = snprintf((char *)msg, 255, "%s is an INT %d ", c.c_str(), i0);
        logThis();
      } else if (isFloat(c, &f0)) {
        putFloatOnStack(f0);
        executionPointer += 1;
        xxxxxx = snprintf((char *)msg, 255, "%s is a FLOAT %f ", c.c_str(), f0);
        logThis();
      } else {
        xxxxxx = snprintf((char *)msg, 255, "\nERROR! Unknown: %s at executionPointer %d\n", c.c_str(), executionPointer);
        logThis();
        return;
      }
    }
  }
}

vector<string> tokenize(char *cc, vector<string> chunks) {
  // adds to the string vector chunks.
  // enables multi-line code
  unsigned int ln = strlen(cc), ix = 0;
  char buffer[256] = { 0 };
  unsigned int buffIndex = 0;
  insideString = false;
  while (ix < ln) {
    char c = cc[ix++];
    if (c == ' ' && insideString) {
      buffer[buffIndex++] = ' ';
    } else if (c < '!' && !insideString) {
      // skip if not yet in a string
      // else add chunk
      if (buffIndex > 0) {
        buffer[buffIndex] = 0;
        chunks.push_back(buffer);
        string bf = chunks.at(chunks.size() - 1);
        if ((bf == ".\"" || bf == ".DT\"" || bf == "s\"") && !insideString) {
          insideString = true;
          xxxxxx = snprintf((char *)msg, 255, "inside string ");
          logThis();
        }
        xxxxxx = snprintf((char *)msg, 255, "\n* Adding `%s`\n", buffer);
        logThis();
        memset(buffer, 0, 256);
        buffIndex = 0;
      }
    } else if (c == '\\' && insideString) {
      char esc = cc[ix++];
      if (esc == 'n') esc = '\n';
      else if (esc == 'r') esc = '\r';
      else if (esc == '0') esc = '\0';
      else if (esc == 't') esc = '\t';
      else if (esc == 'x') {
        char xxx[3] = { 0 };
        xxx[0] = cc[ix++];
        xxx[1] = cc[ix++];
        esc = stoi(string(xxx), nullptr, 16);
      }
      buffer[buffIndex++] = esc;
    } else if (c == '"' && insideString /* && cc[ix + 1] < '!'*/) {
      xxxxxx = snprintf((char *)msg, 255, " Ending \"\n");
      logThis();
      insideString = false;
      buffer[buffIndex++] = c;
      buffer[buffIndex] = 0;
      string ss(buffer);
      //ss.append("\"");
      ix += 1;
      xxxxxx = snprintf((char *)msg, 255, "ss: %s\n", ss.c_str());
      logThis();
      chunks.push_back(ss);
      memset(buffer, 0, 256);
      buffIndex = 0;
    } else {
      xxxxxx = snprintf((char *)msg, 255, "%c", c);
      logThis();
      buffer[buffIndex++] = c;
    }
  }
  if (buffIndex > 0) {
    buffer[buffIndex + 1] = 0;
    xxxxxx = snprintf((char *)msg, 255, "\n** Adding `%s`\n", buffer);
    logThis();
    chunks.push_back(buffer);
  }
  return chunks;
}

bool handleLOAD() {
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleLOAD");
    return false;
  }
  if (blocks.size() < i0) {
    logUnknownBlock((char *)"handleLOAD");
    return false;
  }
  string c = blocks.at(i0);
  strcpy(code, c.c_str());
  return true;
  // The idea is now the buffer has code in it.
  // The user can call EXEC or something similar. TBD.
  // Later on add a buffer editor.
}

int main(int argc, char **argv) {
  vector<string> chunks;
  initForth();
#if defined(NEED_SDL)
#include "sdl_inc2.hpp"
#else
  if (argc == 3) {
    if (strcmp(argv[1], "-f") == 0) {
      vector<string> thisBlock = loadFile(argv[2]);
      if (thisBlock.size() == 0) {
        cerr << "Unable to open file!" << endl;
        return -1;
      }
      int lineCount = 0;
      string line;
      for (vector<string>::iterator it = thisBlock.begin(); it != thisBlock.end(); ++it) {
        line = *it;
        while (!line.empty() && line.back() == '\n')
          line.pop_back();
        lineCount += 1;
        strcpy(code, line.c_str());
        chunks = tokenize(code, chunks);
        cout << " • Read: " << line << endl;
      }
      cout << "Read: " << lineCount << " line" << (lineCount > 1 ? "s," : ",") << " chunks: " << chunks.size() << endl;
    } else {
      cerr << argv[1] << "!= -f" << endl;
      return 0;
    }
  } else if (argc == 2) {
    strcpy(code, argv[1]);
    chunks = tokenize(code, chunks);
  } else {
    strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
    chunks = tokenize(code, chunks);
  }
  evaluate(chunks);
  memset(code, 0, 256);
#endif

  cout << endl << endl;
  return 0;
}
