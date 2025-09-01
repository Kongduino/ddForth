#include "ddforth.hpp"

using namespace std;

nativeCommand nativeCommands[] = {
  { handleWORDS, "WORDS" },
  { handlePlus, "+" },
  { handleMinus, "-" },
  { handleMult, "*" },
  { handleDiv, "/" },
  { handleFact, "FACT" },
  { handleEMIT, "EMIT" },
  { handlePRINT, "." },
  { handlePRINTSTRING, ".\"" },
  { handleUPRINT, "U." },
  { handleDUP, "DUP" },
  { handleDROP, "DROP" },
  { handleSWAP, "SWAP" },
  { handleDEPTH, "DEPTH" },
  { handleROT, "ROT" },
  { handleOVER, "OVER" },
  { handleBASE, "BASE" },
  { handleBASE2, "BIN" },
  { handleBASE10, "DEC" },
  { handleBASE16, "HEX" },
  { handleStore, "!" },
  { handleRetrieve, "@" },
  { handleCR, "CR" },
  { showStack, ".S" },
  { showVars, ".V" },
  { handleEqual, "=" },
  { handleLower, "<" },
  { handleHigher, ">" },
  { handleDifferent, "<>" },
  { handleBEGIN, "BEGIN" },
  { handleUNTIL, "UNTIL" },
  { handleWHILE, "WHILE" },
};
int nativeCmdCount = 0;
struct userCommand {
  string name;
  string command;
};

vector<userCommand> userCommands;
int userCmdCount = 0;
unsigned char dictionary[64 * 1024] = { 0 };
char numerics[] = "0123456789abcdef";
enum dataType {
  xINVALID,
  xINTEGER,
  xFLOAT,
  xSTRING,
};
enum JumpType {
  xBEGIN
};

void StoreCONSTFLOAT(string name, float value) {
  map<string, int>::iterator it;
  it = fconstAddresses.find(name);
  if (it == fconstAddresses.end()) {
    myFCONSTs.push_back(value);
    fconstAddresses[name] = myFCONSTs.size() - 1 + 384;
    snprintf((char*)msg, 255, "FCONST %s created as %f\n", name.c_str(), value);
    logThis();
  } else {
    snprintf((char*)msg, 255, "FCONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreCONSTINT(string name, int value) {
  map<string, int>::iterator it;
  it = constAddresses.find(name);
  if (it == constAddresses.end()) {
    myCONSTs.push_back(value);
    constAddresses[name] = myCONSTs.size() - 1 + 256;
    snprintf((char*)msg, 255, "CONST %s created as %d\n", name.c_str(), value);
    logThis();
  } else {
    snprintf((char*)msg, 255, "CONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreFLOAT(string name, float value) {
  map<string, int>::iterator it;
  it = fvarAddresses.find(name);
  if (it != fvarAddresses.end()) {
    snprintf((char*)msg, 255, "FVAR %s found at %d\n", name.c_str(), (it->second));
    logThis();
    myFVARs.at(it->second) = value;
  } else {
    myFVARs.push_back(value);
    fvarAddresses[name] = myFVARs.size() - 1 + 128;
    snprintf((char*)msg, 255, "FVAR %s created at %d\n", name.c_str(), (fvarAddresses[name]));
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

bool checkTypes(int levels, unsigned char n) {
  if (dataStack.size() < levels) return false;
  for (int ix = 0; ix < levels; ix++) {
    if (dataStack.at(dataStack.size() - 1 - ix) != n) return false;
  }
  return true;
}

void initForth() {
  snprintf((char*)msg, 255, "init ");
  logThis();
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  userCmdCount = userCommands.size();
  StoreINT("BASE", 10);
  string name("0=");
  string code("0 =");
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  userCommand x = { name, code };
  userCommands.push_back(x);

  name = "0>";
  code = "0 >";
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  x = { name, code };
  userCommands.push_back(x);

  name = "0<";
  code = "0 <";
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  x = { name, code };
  userCommands.push_back(x);

  name = "TRUE";
  code = "1 =";
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  x = { name, code };
  userCommands.push_back(x);

  name = "FALSE";
  code = "0 =";
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  x = { name, code };
  userCommands.push_back(x);

  name = "?";
  code = "@ .";
  snprintf((char*)msg, 255, "Adding word %s with `%s`\n", name.c_str(), code.c_str());
  logThis();
  x = { name, code };
  userCommands.push_back(x);
  StoreINT("VER.", 1051);
  // words that are handled in code (evaluate)
  computedWords.push_back("VAR");
  computedWords.push_back("CONST");
  computedWords.push_back(": ... ;");
}

bool handleWORDS() {
  cout << endl << "WORDS" << endl;
  for (vector<string>::iterator it = computedWords.begin() ; it != computedWords.end(); ++it)
    cout << " • " << *it << "     \t (Handled in code)" << endl;
  for (int ix = 0; ix < nativeCmdCount; ix++)
    cout << " • " << nativeCommands[ix].name << "     \t (Native command)" << endl;
  for (vector<userCommand>::iterator it = userCommands.begin() ; it != userCommands.end(); ++it)
    cout << " • " << it->name << "\t\t" << it->command << endl;
  return true;
}


bool handleFact() {
  int factorial = 1;
  int n;
  if (popIntegerFromStack(&n) == false) {
    logStackOverflow((char*)"handleFact");
    return false;
  }
  if (n < 0) {
    snprintf((char*)msg, 255, "Factorial is not defined for negative numbers.");
    logThis();
    return false;
  }
  for (int i = 1; i <= n; ++i)
    factorial *= i;
  putIntegerOnStack(factorial);
  return true;
}

bool handleBEGIN() {
// BEGIN ... <condition> UNTIL
  snprintf((char*)msg, 255, "\n\n--> BEGIN at ");
  logThis();
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xBEGIN);
  snprintf((char*)msg, 255, "%d\n", executionPointer);
  logThis();
  return true;
}

bool isUNTIL = true;
bool handleUNTILWHILE() {
  snprintf((char*)msg, 255, "\n--> UNTILWHILE at %d. JumpStack size: %zu\n", executionPointer, jumpStack.size());
  logThis();
  int i0, type0;
  if (jumpStack.size() == 0) {
    snprintf((char*)msg, 255, "handleUNTILWHILE JumpStack overflow!\n");
    logThis();
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
    snprintf((char*)msg, 255, "handleUNTILWHILE xBEGIN not on JumpStack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char*)"handleUNTILWHILE");
    return false;
  }
#if defined(DEBUG)
  showStack();
#endif
  if (i0 < 0 || i0 > 1) {
    snprintf((char*)msg, 255, "handleUNTILWHILE %d is not a BOOLEAN!\n", i0);
    logThis();
    return false;
  }
  snprintf((char*)msg, 255, "Condition is %s\n", ((i0 == 1) ? "true" : "false"));
  logThis();
  if ((i0 == 0 && isUNTIL) || (i0 == 1 && !isUNTIL)) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
    snprintf((char*)msg, 255, " looping back to %d. Condition: %d.\n", executionPointer, i0);
    logThis();
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
    snprintf((char*)msg, 255, " Ending BEGIN. Condition: %d.\n", i0);
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
  cout << endl << "+---------------------------------------+" << endl;
  cout << "| Num\t| Name\t\t| Addr\t| Value\t|";
  cout << endl << "+---------------------------------------+" << endl;
  if (myVARs.size() > 0) {
    map<string, int>::iterator it = varAddresses.begin();
    int ix = 0;
    while (it != varAddresses.end()) {
      cout << "| " << (ix++) << "/" << myVARs.size() << "\t| ";
      cout << it->first << "\t\t| ";
      cout << it->second << "\t|";
      cout << myVARs.at(it->second) << "\t|" << endl;
      it++;
    }
    cout << "+---------------------------------------+" << endl;
  }
  if (myVARs.size() > 0) {
    map<string, int>::iterator it = fvarAddresses.begin();
    int ix = 0;
    while (it != fvarAddresses.end()) {
      cout << "| " << (ix++) << "/" << fvarAddresses.size() << "\t| ";
      cout << it->first << "\t\t| ";
      cout << (it->second) << "\t|";
      cout << myFVARs.at(it->second - 128) << "\t|" << endl;
      it++;
    }
    cout << "+---------------------------------------+" << endl;
  }
  if (myCONSTs.size() > 0) {
    map<string, int>::iterator it = constAddresses.begin();
    int ix = 0;
    while (it != constAddresses.end()) {
      cout << "| " << (ix++) << "/" << constAddresses.size() << "\t| ";
      cout << it->first << "\t\t| ";
      cout << (it->second) << "\t|";
      cout << myCONSTs.at(it->second - 256) << "\t|" << endl;
      it++;
    }
    cout << "+---------------------------------------+" << endl;
  }
  if (myFCONSTs.size() > 0) {
    map<string, int>::iterator it = fconstAddresses.begin();
    int ix = 0;
    while (it != fconstAddresses.end()) {
      cout << "| " << (ix++) << "/" << fconstAddresses.size() << "\t| ";
      cout << it->first << "\t\t| ";
      cout << (it->second) << "\t|";
      cout << myFCONSTs.at(it->second - 384) << "\t|" << endl;
      it++;
    }
    cout << "+---------------------------------------+" << endl;
  }
  return true;
}

bool showStack() {
  int count = 0;
  if (dataStack.size() == 0) {
    cout << "Stack empty! ";
    return true;
  }
  cout << endl; // << "showStack " << dataStack.size();
  int x = dataStack.size() - 1;
  int myInts = intCounter - 1;
  int myFloats = floatCounter - 1;
  int myStrings = stringCounter - 1;
  logStackOverflow((char*)"handleUNTILWHILE");
  cout << "\tdataStack.size()\t" << (dataStack.size());
  cout << "\tmyInts\t" << (myInts + 1);
  cout << "\tmyFloats\t" << (myFloats + 1);
  cout << "\tmyStrings\t" << (myStrings + 1) << endl;
  cout << "+-----------------------+" << endl;
  while (x > -1) {
    int type0 = dataStack.at(x);
    cout << "| " << (count++) << "\t| ";
    switch (type0) {
      case xINTEGER:
        cout << "INT.\t| " << userIntegers.at(myInts--) << "\t|" << endl;
        break;
      case xFLOAT:
        cout << "FLOAT\t| ";
        printf("%.3f\t|\n", userFloats.at(myFloats--));
        break;
      case xSTRING:
        cout << "STR.\t| " << userStrings.at(myStrings--) << "\t|" << endl;
        break;
    }
    x -= 1;
  }
  cout << "+-----------------------+" << endl;
  return true;
}

bool handleCR() {
  cout << endl;
  return true;
}

bool handleStore() {
  snprintf((char*)msg, 255, "handleStore: intCounter %d dataStack.size() %zu ", intCounter, dataStack.size());
  logThis();
  if (dataStack.size() < 2) {
    logStackOverflow((char*)"handleStore");
    return false;
  }
  // We are not necessarily storing an int
  // check the type of the address vs type in the stack
  // ie 0-127, 256-383 = int, else float
  int ad, x;
  float fx;
  if (dataStack.at(dataStack.size() - 1) == xINTEGER) {
    if (popIntegerFromStack(&x) == false) {
      snprintf((char*)msg, 255, "handleStore on top!\n");
      logThis();
      return false;
    }
    snprintf((char*)msg, 255, "handleStore pop Int successful!\n");
    logThis();
  } else if (dataStack.at(dataStack.size() - 1) == xFLOAT) {
    if (popFloatFromStack(&fx) == false) {
      snprintf((char*)msg, 255, "handleStore No Float on top!\n");
      logThis();
      return false;
    }
    snprintf((char*)msg, 255, "handleStore pop Float successful!\n");
    logThis();
  } else {
    snprintf((char*)msg, 255, "handleStore no Int nor Float on top!\n");
    logThis();
    return true;
  }
  if (dataStack.at(dataStack.size() - 1) != xINTEGER) {
    snprintf((char*)msg, 255, "handleStore No Int Address!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
    logStackOverflow((char*)"handleStore2");
    return false;
  }
  snprintf((char*)msg, 255, "handleStore Int Address : %d.\n", ad);
  logThis();
  if (ad < 128) {
    snprintf((char*)msg, 255, "storing %d into myVARs[%d].\n", x, ad);
    logThis();
    myVARs.at(ad) = x;
  } else if (ad < 256) {
    snprintf((char*)msg, 255, "storing %f into myFVARs[%d].\n", fx, ad);
    logThis();
    myFVARs.at(ad - 128) = fx;
  } else if (ad < 384) {
    snprintf((char*)msg, 255, "storing %d into myCONSTs[%d].\n", x, ad);
    logThis();
    myCONSTs.at(ad - 256) = x;
  } else {
    snprintf((char*)msg, 255, "storing %f into myFCONSTs[%d].\n", fx, ad);
    logThis();
    myFCONSTs.at(ad - 384) = fx;
  }
  return true;
}

bool handleRetrieve() {
  logStack((char*)"handleRetrieve");
  if (!checkTypes(1, xINTEGER)) {
    snprintf((char*)msg, 255, "handleRetrieve Not enough integers!\n");
    logThis();
    return false;
  }
  int ad;
  if (popIntegerFromStack(&ad) == false) {
    logStackOverflow((char*)"handleRetrieve1");
    return false;
  }
  snprintf((char*)msg, 255, "handleRetrieve end %d ", ad);
  logThis();
  if (ad < 128) return putIntegerOnStack(myVARs.at(ad));
  else if (ad < 256) return putFloatOnStack(myFVARs.at(ad - 128));
  else if (ad < 384) putIntegerOnStack(myCONSTs.at(ad - 256));
  else return putFloatOnStack(myFCONSTs.at(ad - 384));
  return true;
}

bool handleBASE() {
  snprintf((char*)msg, 255, "handleBASE ");
  logThis();
  return putIntegerOnStack(GetINTaddress("BASE"));
}

bool handleBASE2() {
  snprintf((char*)msg, 255, "handleBASE2 ");
  logThis();
  StoreINT("BASE", 2);
  return true;
}

bool handleBASE10() {
  snprintf((char*)msg, 255, "handleBASE10 ");
  logThis();
  StoreINT("BASE", 10);
  return true;
}

bool handleBASE16() {
  snprintf((char*)msg, 255, "handleBASE16 ");
  logThis();
  StoreINT("BASE", 16);
  return true;
}

bool printOtherBases(int number, unsigned int base) {
  if (base > 16) {
    StoreINT("BASE", 16);
    base = 16;
  }
  unsigned int uNumber = number;
  snprintf((char*)msg, 255, " Printing %d in base %d\n", uNumber, base);
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
  while (n < (ix>>1)) {
    unsigned char b = buffer[n];
    buffer[n] = buffer[ix - n];
    buffer[ix - n] = b;
    n += 1;
  }
  printf("%s ", buffer);
  return true;
}

bool handleEMIT() {
  int i0;
  char c;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char*)"handleEMIT1");
    return false;
  }
  c = i0;
  printf("%c", c);
  return true;
}

bool handlePRINTSTRING() {
  isPrinting = true;
  return true;
}

bool handlePRINT() {
  logStack((char*)"handlePRINT");
  if (dataStack.size() == 0) {
    logStackOverflow((char*)"handlePRINT");
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        int i0;
        if (popIntegerFromStack(&i0) == false) {
          logStackOverflow((char*)"handlePRINT1");
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
          logStackOverflow((char*)"handlePRINT2");
          return false;
        }
        printf("%f ", f0);
        break;
      }
  }
  return true;
}

bool handleUPRINT() {
  logStack((char*)"handleUPRINT");
  if (dataStack.size() == 0) {
    logStackOverflow((char*)"handleUPRINT");
    return false;
  }
  if (GetINT("BASE") != 10) {
    snprintf((char*)msg, 255, "handleUPRINT only works in base 10!\n");
    logThis();
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        unsigned int i0;
        if (popIntegerFromStack((int *)&i0) == false) {
          logStackOverflow((char*)"handleUPRINT1");
          return false;
        }
        cout << i0 << " ";
        break;
      }
    case xFLOAT:
      {
        snprintf((char*)msg, 255, "handleUPRINT only works with integers!\n");
        logThis();
        return false;
      }
  }
  return true;
}

bool handleOVER() {
  logStack((char*)"handleOVER");
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleOVER");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleOVER1");
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleOVER2");
        return false;
      }
      putIntegerOnStack(i1);
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleOVER3");
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleOVER4");
        return false;
      }
      snprintf((char*)msg, 255, "2 FLOATs ");
      logThis();
      putFloatOnStack(f1);
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  } else {
// one int one float
    snprintf((char*)msg, 255, "OVER requires 2 ints or 2 floats!\n");
    logThis();
    return false;
  }
  return false;
}

bool handleDROP() {
  if (dataStack.size() == 0) {
    logStackOverflow((char*)"handleDROP");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  switch (type0) {
    case xINTEGER:
      int i0;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleDROP1");
        return false;
      }
      return true;
      break;
    case xFLOAT:
      float f0;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleDROP2");
        return false;
      }
      return true;
      break;
  }
  return false;
}

bool handleDUP() {
  if (dataStack.size() == 0) {
    logStackOverflow((char*)"handleDUP");
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        int i0 = userIntegers.at(userIntegers.size() - 1);
        return putIntegerOnStack(i0);
        break;
      }
    case xFLOAT:
      {
        float f0 = userFloats.at(userFloats.size() - 1);
        return putFloatOnStack(f0);
        break;
      }
    case xSTRING:
      {
        string s0 = userStrings.at(userStrings.size() - 1);
        return putStringOnStack(s0);
        break;
      }
  }
  return false;
}

bool handleHigher() {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleHigher");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleHigher1");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleHigher2");
        return false;
      }
      if (i0 > i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleHigher3");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleHigher4");
        return false;
      }
      if (f0 > f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
    snprintf((char*)msg, 255, "1 INT 1 FLOAT ");
    logThis();
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handleHigher5");
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char*)"handleHigher6");
      return false;
    }
    if (i0 > i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handleLower() {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleLower");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      snprintf((char*)msg, 255, "2 INTs ");
      logThis();
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleLower");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleLower1");
        return false;
      }
      if (i0 < i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleLower2");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleLower3");
        return false;
      }
      if (f0 < f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
    snprintf((char*)msg, 255, "1 INT 1 FLOAT ");
    logThis();
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handleLower4");
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char*)"handleLower5");
      return false;
    }
    if (i0 < i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handleEqual() {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleEqual");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      snprintf((char*)msg, 255, "2 INTs ");
      logThis();
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleEqual1");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleEqual2");
        return false;
      }
      if (i0 == i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleEqual3");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleEqual4");
        return false;
      }
      if (f0 == f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
    snprintf((char*)msg, 255, "1 INT 1 FLOAT");
    logThis();
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handleEqual5");
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char*)"handleEqual6");
      return false;
    }
    if (i0 == i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handleDifferent() {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleLower");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      snprintf((char*)msg, 255, "2 INTs ");
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
      logStackOverflow((char*)"handleDifferent1");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char*)"handleDifferent2");
        return false;
      }
      if (i0 != i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
      logStackOverflow((char*)"handleDifferent3");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handleDifferent4");
        return false;
      }
      if (f0 != f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
    snprintf((char*)msg, 255, "1 INT 1 FLOAT");
    logThis();
    int i0, i1;
    float f0, f1;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handleDifferent5");
      return false;
    }
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char*)"handleDifferent6");
      return false;
    }
    f1 = i0;
    if (f0 != f1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handle2Nums(unsigned char X) {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handle2Nums");
    showStack();
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      snprintf((char*)msg, 255, "2 INTs ");
      logThis();
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
      logStackOverflow((char*)"handle2Nums1");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handle2Nums2");
        return false;
      }
      switch (X) {
        case math_PLUS:
          putIntegerOnStack(i0 + i1);
          break;
        case math_MINUS:
          putIntegerOnStack(i0 - i1);
          break;
        case math_MULT:
          putIntegerOnStack(i0 * i1);
          break;
        case math_DIV:
          putIntegerOnStack(i0 / i1);
          break;
      }
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handle2Nums3");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handle2Nums4");
        return false;
      }
      snprintf((char*)msg, 255, "2 FLOATs ");
      logThis();
      switch (X) {
        case math_PLUS:
          putFloatOnStack(f0 + f1);
          break;
        case math_MINUS:
          putFloatOnStack(f0 - f1);
          break;
        case math_MULT:
          putFloatOnStack(f0 * f1);
          break;
        case math_DIV:
          putFloatOnStack(f0 / f1);
          break;
      }
      return true;
    }
  } else {
// one int one float
      snprintf((char*)msg, 255, "1 INT 1 FLOAT ");
      logThis();
    int i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char*)"handle2Nums5");
      return false;
    }
    if (popIntegerFromStack(&i1) == false) {
      logStackOverflow((char*)"handle2Nums6");
      return false;
    }
    switch (X) {
      case math_PLUS:
        putFloatOnStack(f0 + i1);
        break;
      case math_MINUS:
        putFloatOnStack(f0 - i1);
        break;
      case math_MULT:
        putFloatOnStack(f0 * i1);
        break;
      case math_DIV:
        putFloatOnStack(f0 / i1);
        break;
    }
    return true;
  }
  return false;
}

bool handlePlus() {
  return handle2Nums(math_PLUS);
}

bool handleMinus() {
  return handle2Nums(math_MINUS);
}
bool handleMult() {
  return handle2Nums(math_MULT);
}

bool handleDiv() {
  return handle2Nums(math_DIV);
}

bool handleDEPTH() {
  logStack((char*)"handleDEPTH");
  putIntegerOnStack(dataStack.size());
  return true;
}


bool handleROT() {
  logStack((char*)"handleROT");
  if (dataStack.size() < 3) {
    logStackOverflow((char*)"handleROT");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  unsigned char type2 = dataStack.at(dataStack.size() - 3);
  if (
    type0 == xSTRING || type0 == xINVALID ||
    type1 == xSTRING || type1 == xINVALID ||
    type2 == xSTRING || type2 == xINVALID
  ) {
    logInconsistent((char*)"handleROT");
    return false;
  }
  if (type0 == type1 && type0 == type2) {
    if (type0 == xINTEGER) {
      if (intCounter < 3) {
        logStackOverflow((char*)"handleROT1");
        return false;
      }
      int i0, i1, i2;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleROT2");
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleROT3");
        return false;
      }
      if (popIntegerFromStack(&i2) == false) {
        logStackOverflow((char*)"handleROT4");
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i2);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1, f2;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleROT6");
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleROT7");
        return false;
      }
      if (popFloatFromStack(&f2) == false) {
        logStackOverflow((char*)"handleROT8");
        return false;
      }
      putFloatOnStack(f0);
      putFloatOnStack(f2);
      putFloatOnStack(f1);
      return true;
    }
  } else {
    return false;
  }
  return false;
}

bool handleSWAP() {
  logStack((char*)"handleROT");
  if (dataStack.size() < 2) {
    logStackOverflow((char*)"handleSWAP");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char*)"handleSWAP");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (intCounter < 2) {
        logStackOverflow((char*)"handleSWAP1");
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char*)"handleSWAP2");
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char*)"handleSWAP3");
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      if (floatCounter < 2) {
        logStackOverflow((char*)"handleSWAP4");
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char*)"handleSWAP5");
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char*)"handleSWAP6");
        return false;
      }
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  }
  return false;
}

bool putStringOnStack(string n) {
  enum dataType type = xSTRING;
  userStrings.push_back(n);
  dataStack.push_back(type);
  stringCounter += 1;
  return true;
}

bool putIntegerOnStack(int n) {
  enum dataType type = xINTEGER;
  userIntegers.push_back(n);
  dataStack.push_back(type);
  intCounter += 1;
  return true;
}

bool popIntegerFromStack(int *value) {
  enum dataType type = xINTEGER;
  if (dataStack.at(dataStack.size() - 1) != type) {
    return false;
  }
  *value = userIntegers.at(intCounter - 1);
  userIntegers.pop_back();
  dataStack.pop_back();
  intCounter -= 1;
  return true;
}

bool popFloatFromStack(float *value) {
  enum dataType type = xFLOAT;
  if (dataStack.at(dataStack.size() - 1) != type) {
    return false;
  }
  *value = userFloats.at(floatCounter - 1);
  userFloats.pop_back();
  floatCounter -= 1;
  dataStack.pop_back();
  return true;
}

bool putFloatOnStack(float n) {
  enum dataType type = xFLOAT;
  userFloats.push_back(n);
  dataStack.push_back(type);
  floatCounter += 1;
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
  snprintf((char*)msg, 255, "No such VAR/CONST: %s\n", name.c_str());
  logThis();
  return false;
}

bool lookupUC(string c) {
  snprintf((char*)msg, 255, "lookupUC %s ", c.c_str());
  logThis();
  for (int ix = 0; ix < userCommands.size(); ix++) {
    snprintf((char*)msg, 255, "%s ", userCommands[ix].name.c_str());
    logThis();
    if (c == userCommands[ix].name) {
      char code[256];
      strcpy(code, userCommands[ix].command.c_str());
      snprintf((char*)msg, 255, "tokenize %s ", userCommands[ix].command.c_str());
      logThis();
      int savedExecutionPointer = executionPointer;
      vector<string> myChunks = tokenize(code);
      evaluate(myChunks);
      executionPointer = savedExecutionPointer;
      return true;
    }
  }
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
  snprintf((char*)msg, 255, "isInteger/%d/%s", base, c.c_str());
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
    snprintf((char*)msg, 255, "%s is not an int.\n", c.c_str());
    logThis();
    return false;
  }
  try {
    *i0 = stoi(c, nullptr, base) * sign;
    return true;
  } catch (const invalid_argument &e) {
    snprintf((char*)msg, 255, "Invalid argument for '%s': %s\n", c.c_str(), e.what());
    logThis();
  } catch (const out_of_range &e) {
    snprintf((char*)msg, 255, "Out of range for '%s': %s\n", c.c_str(), e.what());
    logThis();
  }
  return false;
}

bool isFloat(string c, float *f0) {
  if (c.length() == 0) return false;
    snprintf((char*)msg, 255, "isFloat: %s?\n", c.c_str());
    logThis();
  if (GetINT("BASE") == 10) {
    try {
      *f0 = stof(c);
      return true;
    } catch (const invalid_argument &e) {
      snprintf((char*)msg, 255, "Invalid argument for '%s': %s\n", c.c_str(), e.what());
      logThis();
    } catch (const out_of_range &e) {
      snprintf((char*)msg, 255, "Out of range for '%s': %s\n", c.c_str(), e.what());
      logThis();
    }
  } else {
    snprintf((char*)msg, 255, "Only works for base 10!\n");
    logThis();
  }
  return false;
}

void evaluate(vector<string> chunks) {
  bool r;
  int i0;
  float f0;
  snprintf((char*)msg, 255, "Evaluating:\n");
  logThis();
#if defined(DEBUG)
  for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) cout << *it << " ";
  cout << endl;
  showStack();
#endif
  // for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) {
  executionPointer = 0;
  while (executionPointer < chunks.size()) {
    // executionPointer is global so that BEGIN – and later others – can change it.
    string c = chunks.at(executionPointer);
    snprintf((char*)msg, 255, "Evaluating '%s' executionPointer: %d \n", c.c_str(), executionPointer);
    logThis();
#if defined(DEBUG)
    for (int xx = 0; xx < chunks.size(); xx++) {
      cout << xx;
      if (xx == executionPointer) cout << "*";
      else cout << " ";
      cout << "\t| " << chunks.at(xx) << "\t|" << endl;
    }
#endif
    if (lookupVAR(c)) {
      snprintf((char*)msg, 255, "Put address of %s on stack. ", c.c_str());
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
        snprintf((char*)msg, 255, "No INT on the stack!\n");
        logThis();
        if (popFloatFromStack(&f0) == false) {
          snprintf((char*)msg, 255, "No FLOAT on the stack either!\n");
          logThis();
        } else {
          thisIsFloat = true;
        }
      } else thisIsInt = true;
      if (!thisIsFloat && !thisIsInt) return;
      if (c == "VAR" && thisIsInt) {
        snprintf((char*)msg, 255, "VAR name: %s initialized with %d\n", d.c_str(), i0);
        logThis();
        StoreINT(d, i0);
      } else if (c == "VAR" && thisIsFloat) {
        snprintf((char*)msg, 255, "VAR name: %s initialized with %f\n", d.c_str(), f0);
        logThis();
        StoreFLOAT(d, f0);
      } else if (c == "CONST" && thisIsInt) {
        snprintf((char*)msg, 255, "CONST name: %s initialized with %d\n", d.c_str(), i0);
        logThis();
        StoreCONSTINT(d, i0);
      } else if (c == "CONST" && thisIsFloat) {
        snprintf((char*)msg, 255, "CONST name: %s initialized with %f\n", d.c_str(), f0);
        logThis();
        StoreCONSTFLOAT(d, f0);
      }
    } else if (isPrinting && c.back() == '"') {
      // print that
      c.pop_back();
      cout << c << " ";
      isPrinting = false;
      executionPointer += 1;
    } else if (c == ":") {
      // creation of a word
      executionPointer += 1;
      bool done = false, error = true;
      string miniChunks, dictName;
      dictName = chunks.at(executionPointer++);
      snprintf((char*)msg, 255, "WORD name: %s: ", dictName.c_str());
      logThis();
      while (executionPointer < chunks.size() && !done) {
        c = chunks.at(executionPointer);
        snprintf((char*)msg, 255, "%s %d / %zu ", c.c_str(), executionPointer, chunks.size());
        logThis();
        if (c == ";") {
          done = true;
          error = false;
          executionPointer += 1;
          snprintf((char*)msg, 255, " got a ;! ");
          logThis();
        } else {
          miniChunks.append(c);
          miniChunks.append(" ");
          executionPointer += 1;
        }
      }
      if (error) {
        snprintf((char*)msg, 255, "Missing ; after : sequence! %s\n", miniChunks.c_str());
        logThis();
        return;
      }
      snprintf((char*)msg, 255, "Adding word `%s` with `%s`\n", dictName.c_str(), miniChunks.c_str());
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
        snprintf((char*)msg, 255, "%s lookupUC\n", c.c_str());
        logThis();
        executionPointer += 1;
      } else if (isInteger(c, &i0)) {
        putIntegerOnStack(i0);
        executionPointer += 1;
        snprintf((char*)msg, 255, "%s is an INT %d ", c.c_str(), i0);
        logThis();
      } else if (isFloat(c, &f0)) {
        putFloatOnStack(f0);
        executionPointer += 1;
        snprintf((char*)msg, 255, "%s is a FLOAT %f ", c.c_str(), f0);
        logThis();
      } else {
        snprintf((char*)msg, 255, "\nERROR! Unknown: %s at executionPointer %d\n", c.c_str(), executionPointer);
        logThis();
        return;
      }
    }
  }
}

vector<string> tokenize(char *code) {
  unsigned int ln = strlen(code), ix = 0;
  vector<string> chunks;
  char buffer[256] = { 0 };
  unsigned int buffIndex = 0;
  bool insideString = false;
  while (ix < ln) {
    char c = code[ix++];
    if (c < '!' && !insideString) {
      // skip if not yet in a string
      // else add chunk
      if (buffIndex > 0) {
        buffer[buffIndex] = 0;
        chunks.push_back(buffer);
        if (chunks.at(chunks.size() - 1) == ".\"" && !insideString) {
          insideString = true;
          snprintf((char*)msg, 255, "inside string\n");
          logThis();
          cout << "" << endl;
        }
        snprintf((char*)msg, 255, " * Adding `%s`\n", buffer);
        logThis();
        memset(buffer, 0, 256);
        buffIndex = 0;
      }
    } else if (c == '\\' && insideString) {
      char esc = code[ix++];
      if (esc == 'n') esc = '\n';
      else if (esc == 'r') esc = '\r';
      else if (esc == '0') esc = '\0';
      else if (esc == 't') esc = '\t';
      else if (esc == 'x') {
        char xxx[3] = {0};
        xxx[0] = code[ix++];
        xxx[1] = code[ix++];
        esc = stoi(string(xxx), nullptr, 16);
      }
      buffer[buffIndex++] = esc;
    } else if (c == '"' && insideString /* && code[ix + 1] < '!'*/) {
      snprintf((char*)msg, 255, "Ending \"\n");
      logThis();
      insideString = false;
      buffer[buffIndex++] = c;
      buffer[buffIndex] = 0;
      string ss(buffer);
      //ss.append("\"");
      ix += 1;
      snprintf((char*)msg, 255, "ss: %s\n", ss.c_str());
      logThis();
      chunks.push_back(ss);
      memset(buffer, 0, 256);
      buffIndex = 0;
    } else {
      snprintf((char*)msg, 255, "%c", c);
      logThis();
      buffer[buffIndex++] = c;
    }
  }
  if (buffIndex > 0) {
    buffer[buffIndex + 1] = 0;
    snprintf((char*)msg, 255, " • Adding `%s`\n", buffer);
    logThis();
    chunks.push_back(buffer);
  }
  return chunks;
}

int main(int argc, char **argv) {
  char code[256] = { 0 };
  initForth();
  if(argc == 3) {
    if (strcmp(argv[1], "-f") == 0) {
      ifstream inputFile(argv[2]);
      if (!inputFile.is_open()) {
        cerr << "Unable to open file!" << endl;
        return 0;
      }
      string line;
      getline(inputFile, line);
      strcpy(code, line.c_str());
    } else {
      cerr << argv[1] << "!= -f" << endl;
      return 0;
    }
  } else if(argc == 2) {
    strcpy(code, argv[1]);
  } else {
    strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
  }
  //   strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
  //   cout << code << endl;
  //   vector<string> chunks = tokenize(code);
  //   evaluate(chunks);

  cout << "Running code:" << endl << "\t" << code << endl;
  vector<string> chunks = tokenize(code);
  evaluate(chunks);

  cout << endl << endl;
  return 0;
}
