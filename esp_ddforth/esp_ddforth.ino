#include "ddforth.hpp"

using namespace std;

void StoreCONSTFLOAT(string name, float value) {
  std::map<string, int>::iterator it;
  it = fconstAddresses.find(name);
  if (it == fconstAddresses.end()) {
    myFCONSTs.push_back(value);
    fconstAddresses[name] = myFCONSTs.size() - 1 + 384;
  } else {
  }
}

void StoreCONSTINT(string name, int value) {
  std::map<string, int>::iterator it;
  it = constAddresses.find(name);
  if (it == constAddresses.end()) {
    myCONSTs.push_back(value);
    constAddresses[name] = myCONSTs.size() - 1 + 256;
  } else {
  }
}

void StoreFLOAT(string name, float value) {
  std::map<string, int>::iterator it;
  it = fvarAddresses.find(name);
  if (it != fvarAddresses.end()) {
    myFVARs.at(it->second) = value;
  } else {
    myFVARs.push_back(value);
    fvarAddresses[name] = myFVARs.size() - 1 + 128;
  }
}

void StoreINT(string name, int value) {
  std::map<string, int>::iterator it;
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
  std::map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    return myVARs.at(it->second);
  } else {
    return -1;
  }
}

int GetINTaddress(string name) {
  std::map<string, int>::iterator it;
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

bool handleLOAD() {
  // if (dataStack.size() == 0) {
  //   return false;
  // }
  // int i0;
  // if (popIntegerFromStack(&i0) == false) {
  //   return false;
  // }
  // string code;
  // char fi[128];
  // sprintf(fi, "/BLOCK%d.fs", i0);
  // code = readFile(fi);
  // return handleEXEC();
  return true;
}

bool handleSAVE() {
  return true;
}

bool handleRput() {
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    return false;
  }
  putIntegerOnJumpStack(i0);
  return true;
}

bool handleRget() {
  if (jumpStack.size() == 0) {
    return false;
  }
  int i0;
  if (popIntegerFromJumpStack(&i0) == false) {
    return false;
  }
  putIntegerOnStack(i0);
  return true;
}

bool handleWORDS() {
  Serial.println("Handled in Code:\n----------------\n");
  for (vector<string>::iterator it = computedWords.begin(); it != computedWords.end(); ++it) {
    string s = *it;
    sprintf(msg, " • %-11s (Handled in code)\n", s.c_str());
    Serial.print(msg);
  }
  Serial.println("Native Commands:\n----------------");
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    //sprintf(msg, " • %-11s (Native command)\n", nativeCommands[ix].name.c_str()); Serial.print(msg);
    cout << nativeCommands[ix].name << " ";
  }
  Serial.println("User Commands:\n----------------");
  for (vector<userCommand>::iterator it = userCommands.begin(); it != userCommands.end(); ++it) {
    sprintf(msg, " • %-11s %s\n", it->name.c_str(), it->command.c_str());
    Serial.print(msg);
  }
  return true;
}

bool handleMOD() {
  return handle2Nums(math_MOD);
}

bool handleFact() {
  int factorial = 1;
  int n;
  if (popIntegerFromStack(&n) == false) {
    return false;
  }
  if (n < 0) {
    return false;
  }
  for (int i = 1; i <= n; ++i)
    factorial *= i;
  putIntegerOnStack(factorial);
  return true;
}

bool handleDO() {
  // Max min DO ... LOOP
  if (dataStack.size() < 2) {
    Serial.print("Stack empty! ");
    return true;
  }
  int max, min;
  if (popIntegerFromStack(&min) == false) {
    return false;
  }
  if (popIntegerFromStack(&max) == false) {
    return false;
  }
  loopStack.push_back(max);
  loopStack.push_back(min);
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xDO);
  return true;
}

bool checkDOLOOPconditions(char *who) {
  if (jumpStack.size() == 0) {
    return false;
  }
  if (loopStack.size() < 2) {
    return false;
  }
  int type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xDO) {
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
  if (popFromLoopStack(&min) == false) {
    return false;
  }
  if (popFromLoopStack(&max) == false) {
    return false;
  }
  min += 1;
  if (min < max) {
    loopStack.push_back(max);
    loopStack.push_back(min);
    executionPointer = jumpStack.at(jumpStack.size() - 1);
  } else {
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
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xBEGIN);
  return true;
}

bool isUNTIL = true;
bool handleUNTILWHILE() {
  int i0, type0;
  if (jumpStack.size() == 0) {
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
    return false;
  }
#if defined(DEBUG)
  showStack();
#endif
  if (i0 < 0 || i0 > 1) {
    return false;
  }
  if ((i0 == 0 && isUNTIL) || (i0 == 1 && !isUNTIL)) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
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
  // cout << "myVARs.size: " << myVARs.size() << " myFVARs.size: " << myFVARs.size()
  //      << " varAddresses.size: " << varAddresses.size()
  //      << " fvarAddresses.size: " << fvarAddresses.size() << endl;
  // cout << "myCONSTs.size: " << myCONSTs.size() << " myFCONSTs.size: " << myFCONSTs.size()
  //      << " constAddresses.size: " << constAddresses.size()
  //      << " fconstAddresses.size: " << fconstAddresses.size() << endl;
  if (myVARs.size() > 0) {
    Serial.println("+-----------------------------------------+");
    Serial.println("| Num     |  VAR Name   | Addr | Value    |");
    Serial.println("+-----------------------------------------+");
    std::map<string, int>::iterator it = varAddresses.begin();
    int ix = 0;
    while (it != varAddresses.end()) {
      string n = it->first;
      sprintf(
        msg,
        "| %3d/%-3zu | %-11s | %4d |%9d |\n",
        (ix++), myVARs.size(), n.c_str(), it->second, myVARs.at(it->second));
      it++;
    }
    Serial.print(msg);
    Serial.println("+-----------------------------------------+");
  }
  if (myFVARs.size() > 0) {
    Serial.println("+-----------------------------------------+");
    Serial.println("| Num     | FVAR Name   | Addr | Value    |");
    Serial.println("+-----------------------------------------+");
    std::map<string, int>::iterator it = fvarAddresses.begin();
    int ix = 0;
    while (it != fvarAddresses.end()) {
      string n = it->first;
      sprintf(
        msg,
        "| %3d/%-3zu | %-11s | %4d |%9f |\n",
        (ix++), myFVARs.size(), n.c_str(), it->second, myFVARs.at(it->second - 128));
      it++;
    }
    Serial.print(msg);
    Serial.println("+-----------------------------------------+");
  }
  if (myCONSTs.size() > 0) {
    Serial.println("+-----------------------------------------+");
    Serial.println("| Num     |  CONST Name | Addr | Value    |");
    Serial.println("+-----------------------------------------+");
    std::map<string, int>::iterator it = constAddresses.begin();
    int ix = 0;
    while (it != constAddresses.end()) {
      string n = it->first;
      sprintf(
        msg,
        "| %3d/%-3zu | %-11s | %4d |%9d |\n",
        (ix++), myCONSTs.size(), n.c_str(), it->second, myCONSTs.at(it->second - 256));
      it++;
    }
    Serial.print(msg);
    Serial.println("+-----------------------------------------+");
  }
  if (myFCONSTs.size() > 0) {
    Serial.println("+-----------------------------------------+");
    Serial.println("| Num     | FCONST Name | Addr | Value    |");
    Serial.println("+-----------------------------------------+");
    std::map<string, int>::iterator it = fconstAddresses.begin();
    int ix = 0;
    while (it != fconstAddresses.end()) {
      string n = it->first;
      sprintf(
        msg,
        "| %3d/%-3zu | %-11s | %4d |%9f |\n",
        (ix++), myFCONSTs.size(), n.c_str(), it->second, myFCONSTs.at(it->second - 384));
      it++;
    }
    Serial.print(msg);
    Serial.println("+-----------------------------------------+");
  }
  return true;
}

bool showStack() {
  int count = 0;
  if (dataStack.size() == 0) {
    Serial.print("Stack empty! ");
    return true;
  }
  Serial.print("\n");  // << "showStack " << dataStack.size();
  int x = dataStack.size() - 1;
  int myInts = userIntegers.size() - 1;
  int myFloats = userFloats.size() - 1;
  int myStrings = userStrings.size() - 1;
  cout << "\tdataStack.size()\t" << (dataStack.size());
  cout << "\tmyInts\t" << (myInts + 1);
  cout << "\tmyFloats\t" << (myFloats + 1);
  cout << "\tmyStrings\t" << (myStrings + 1) << endl;
  Serial.println("+-----------------------+");
  while (x > -1) {
    int type0 = dataStack.at(x);
    cout << "| " << (count++) << "\t| ";
    switch (type0) {
      case xINTEGER:
        cout << "INT.\t| " << userIntegers.at(myInts--) << "\t|" << endl;
        break;
      case xFLOAT:
        cout << "FLOAT\t| ";
        sprintf(msg, "%.3f\t|\n", userFloats.at(myFloats--));
        Serial.print(msg);
        break;
      case xSTRING:
        cout << "STR.\t| " << userStrings.at(myStrings--) << "\t|" << endl;
        break;
    }
    x -= 1;
  }
  Serial.println("+-----------------------+");
  return true;
}

bool handleCR() {
  Serial.print("\n");
  return true;
}

bool handleStore() {
  if (dataStack.size() < 2) {
    return false;
  }
  // We are not necessarily storing an int
  // check the type of the address vs type in the stack
  // ie 0-127, 256-383 = int, else float
  int ad, x;
  float fx;
  if (dataStack.at(dataStack.size() - 1) == xINTEGER) {
    if (popIntegerFromStack(&x) == false) {
      return false;
    }
  } else if (dataStack.at(dataStack.size() - 1) == xFLOAT) {
    if (popFloatFromStack(&fx) == false) {
      return false;
    }
  } else {
    return true;
  }
  if (dataStack.at(dataStack.size() - 1) != xINTEGER) {
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
    return false;
  }
  if (ad < 128) {
    myVARs.at(ad) = x;
  } else if (ad < 256) {
    myFVARs.at(ad - 128) = fx;
  } else if (ad < 384) {
    myCONSTs.at(ad - 256) = x;
  } else {
    myFCONSTs.at(ad - 384) = fx;
  }
  return true;
}

bool handleRetrieve() {
  if (!checkTypes(1, xINTEGER)) {
    return false;
  }
  int ad;
  if (popIntegerFromStack(&ad) == false) {
    return false;
  }
  if (ad < 128) return putIntegerOnStack(myVARs.at(ad));
  else if (ad < 256) return putFloatOnStack(myFVARs.at(ad - 128));
  else if (ad < 384) putIntegerOnStack(myCONSTs.at(ad - 256));
  else return putFloatOnStack(myFCONSTs.at(ad - 384));
  return true;
}

bool handleBASE() {
  return putIntegerOnStack(GetINTaddress("BASE"));
}

bool handleBASE2() {
  StoreINT("BASE", 2);
  return true;
}

bool handleBASE10() {
  StoreINT("BASE", 10);
  return true;
}

bool handleBASE16() {
  StoreINT("BASE", 16);
  return true;
}

bool printOtherBases(int number, unsigned int base) {
  if (base > 16) {
    StoreINT("BASE", 16);
    base = 16;
  }
  unsigned int uNumber = number;
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
  sprintf(msg, "%s ", buffer);
  Serial.print(msg);
  return true;
}

bool handleEMIT() {
  int i0;
  char c;
  if (popIntegerFromStack(&i0) == false) {
    return false;
  }
  c = i0;
  sprintf(msg, "%c", c);
  Serial.print(msg);
  return true;
}

bool handleKEY() {
  char ch;
  while (!Serial.available())
    ;
  ch = Serial.read();
  putIntegerOnStack(ch);
  while (!Serial.available())
    ch = Serial.read();
  return true;
}

bool handleLINE() {
  string s;
  // cin.ignore(numeric_limits<streamsize>::max(), '\n');
  getline(cin, s);  // Reads the entire line
  return putStringOnStack(s);
}

bool handlePRINTSTRING() {
  isPrinting = true;
  return true;
}

bool handlePRINTSTACKSTRING() {
  string s;
  if (popStringFromStack(&s) == false) {
    return false;
  }
  sprintf(msg, "%s ", s.c_str());
  Serial.print(msg);
  return true;
}

bool handlePRINT() {
  if (dataStack.size() == 0) {
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        int i0;
        if (popIntegerFromStack(&i0) == false) {
          return false;
        }
        int base = GetINT("BASE");
        if (base == 10) {
          sprintf(msg, "%d ", i0);
          Serial.print(msg);
        } else printOtherBases(i0, base);
        break;
      }
    case xFLOAT:
      {
        float f0;
        if (popFloatFromStack(&f0) == false) {
          return false;
        }
        sprintf(msg, "%f ", f0);
        Serial.print(msg);
        break;
      }
  }
  return true;
}

bool handleUPRINT() {
  if (dataStack.size() == 0) {
    return false;
  }
  if (GetINT("BASE") != 10) {
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        unsigned int i0;
        if (popIntegerFromStack((int *)&i0) == false) {
          return false;
        }
        sprintf(msg, "%d ", i0);
        Serial.print(msg);
        break;
      }
    case xFLOAT:
      {
        return false;
      }
  }
  return true;
}

bool handleOVER() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        return false;
      }
      putIntegerOnStack(i1);
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        return false;
      }
      putFloatOnStack(f1);
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  } else {
    // one int one float
    return false;
  }
  return false;
}

bool handleDROP() {
  if (dataStack.size() == 0) {
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  switch (type0) {
    case xINTEGER:
      int i0;
      if (popIntegerFromStack(&i0) == false) {
        return false;
      }
      return true;
      break;
    case xFLOAT:
      float f0;
      if (popFloatFromStack(&f0) == false) {
        return false;
      }
      return true;
      break;
  }
  return false;
}

bool handleDUP() {
  if (dataStack.size() == 0) {
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

bool handleGreater() {
  return handle2Nums(math_GREATER);
}

bool handleGreaterEqual() {
  return handle2Nums(math_GREATEREQUAL);
}
bool handleLower() {
  return handle2Nums(math_LOWER);
}

bool handleLowerEqual() {
  return handle2Nums(math_LOWEREQUAL);
}

bool handleEqual() {
  return handle2Nums(math_EQUAL);
}

bool handleDifferent() {
  return handle2Nums(math_EQUAL);
}

bool handle2Nums(unsigned char X) {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    showStack();
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        return false;
      }
      switch (X) {
        case math_PLUS:
          {
            putIntegerOnStack(i0 + i1);
            break;
          }
        case math_MINUS:
          {
            putIntegerOnStack(i0 - i1);
            break;
          }
        case math_MULT:
          {
            putIntegerOnStack(i0 * i1);
            break;
          }
        case math_DIV:
          {
            putIntegerOnStack(i0 / i1);
            break;
          }
        case math_GREATER:
          {
            putIntegerOnStack((i0 > i1));
            break;
          }
        case math_GREATEREQUAL:
          {
            putIntegerOnStack((i0 > i1) || (i0 == i1));
            break;
          }
        case math_LOWER:
          {
            putIntegerOnStack((i0 < i1));
            break;
          }
        case math_LOWEREQUAL:
          {
            putIntegerOnStack((i0 < i1) || (i0 == i1));
            break;
          }
        case math_DIFFERENT:
          {
            putIntegerOnStack((i0 != i1));
            break;
          }
        case math_EQUAL:
          {
            putIntegerOnStack((i0 == i1));
            break;
          }
        case math_MOD:
          {
            putIntegerOnStack((i0 % i1));
            break;
          }
        case math_MIN:
          {
            if (i0 < i1) putIntegerOnStack(i0);
            else putIntegerOnStack(i1);
            break;
          }
        case math_MAX:
          {
            if (i0 > i1) putIntegerOnStack(i0);
            else putIntegerOnStack(i1);
            break;
          }
      }
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        return false;
      }
      switch (X) {
        case math_PLUS:
          {
            putFloatOnStack(f0 + f1);
            break;
          }
        case math_MINUS:
          {
            putFloatOnStack(f0 - f1);
            break;
          }
        case math_MULT:
          {
            putFloatOnStack(f0 * f1);
            break;
          }
        case math_DIV:
          putFloatOnStack(f0 / f1);
          break;
        case math_GREATER:
          {
            putIntegerOnStack((f0 > f1));
            break;
          }
        case math_GREATEREQUAL:
          {
            putIntegerOnStack((f0 > f1) || (f0 == f1));
            break;
          }
        case math_LOWER:
          {
            putIntegerOnStack((f0 < f1));
            break;
          }
        case math_LOWEREQUAL:
          {
            putIntegerOnStack((f0 < f1) || (f0 == f1));
            break;
          }
        case math_DIFFERENT:
          {
            putIntegerOnStack((f0 != f1));
            break;
          }
        case math_EQUAL:
          {
            putIntegerOnStack((f0 == f1));
            break;
          }
        case math_MOD:
          {
            int i0 = (f0 / f1);
            i0 *= f1;
            float f2 = f0 - i0;
            putFloatOnStack(f2);
          }
          break;
        case math_MIN:
          {
            if (f0 < f1) putFloatOnStack(f0);
            else putFloatOnStack(f1);
            break;
          }
        case math_MAX:
          {
            if (f0 > f1) putFloatOnStack(f0);
            else putFloatOnStack(f1);
            break;
          }
      }
      return true;
    }
  } else {
    // one int one float
    bool intFirst = false;
    if (type0 == xINTEGER) intFirst = true;
    // we need to know which comes first for / and -
    int i1;
    float f0, f1;
    if (popFloatFromStack(&f0) == false) {
      return false;
    }
    if (popIntegerFromStack(&i1) == false) {
      return false;
    }
    f1 = i1;  // The int is converted to a float
    switch (X) {
      case math_PLUS:
        {
          putFloatOnStack(f0 + f1);
          break;
        }
      case math_MINUS:
        {
          if (intFirst) putFloatOnStack(f1 - f0);
          else putFloatOnStack(f0 - f1);
          break;
        }
      case math_MULT:
        {
          putFloatOnStack(f0 * f1);
          break;
        }
      case math_DIV:
        {
          if (intFirst) putFloatOnStack(f1 / f0);
          else putFloatOnStack(f0 / f1);
          break;
        }
      case math_GREATER:
        {
          if (intFirst) putIntegerOnStack(f1 > f0);
          else putIntegerOnStack(f0 > f1);
          break;
        }
      case math_GREATEREQUAL:
        {
          if (intFirst) putIntegerOnStack((f1 > f0) || (f1 == f0));
          else putIntegerOnStack((f0 > f1) || (f0 == f1));
          break;
        }
      case math_LOWER:
        {
          if (intFirst) putIntegerOnStack(f1 < f0);
          else putIntegerOnStack(f0 < f1);
          break;
        }
      case math_LOWEREQUAL:
        {
          if (intFirst) putIntegerOnStack((f1 < f0) || (f1 == f0));
          else putIntegerOnStack((f0 < f1) || (f0 == f1));
          break;
        }
      case math_DIFFERENT:
        {
          putIntegerOnStack((f0 != f1));
          break;
        }
      case math_EQUAL:
        {
          putIntegerOnStack((f0 == f1));
          break;
        }
      case math_MOD:
        {
          int i0 = f0;
          if (intFirst) putIntegerOnStack(i1 % i0);
          else putIntegerOnStack(i0 % i1);
          break;
        }
      case math_MIN:
        {
          if (f0 < f1) putFloatOnStack(f0);
          else putFloatOnStack(f1);
          break;
        }
      case math_MAX:
        {
          if (f0 > f1) putFloatOnStack(f0);
          else putFloatOnStack(f1);
          break;
        }
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

bool handleMIN() {
  return handle2Nums(math_MIN);
}

bool handleMAX() {
  return handle2Nums(math_MAX);
}

bool handleABS() {
  if (dataStack.size() == 0) {
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  switch (type0) {
    case xINTEGER:
      int i0;
      if (popIntegerFromStack(&i0) == false) {
        return false;
      }
      putIntegerOnStack(abs(i0));
      return true;
      break;
    case xFLOAT:
      float f0;
      if (popFloatFromStack(&f0) == false) {
        return false;
      }
      putFloatOnStack(abs(f0));
      return true;
      break;
  }
  return false;
}

bool handleSQR() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      return false;
    }
    putFloatOnStack(i0 * i0);
    return true;
  } else {
    if (popFloatFromStack(&f0) == false) {
      return false;
    }
    putFloatOnStack(f0 * f0);
    return true;
  }
  return false;
}

bool handleSQRT() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      return false;
    }
    putFloatOnStack(sqrt(i0));
    return true;
  } else {
    if (popFloatFromStack(&f0) == false) {
      return false;
    }
    putFloatOnStack(sqrt(f0));
    return true;
  }
  return false;
}

bool handleDEPTH() {
  putIntegerOnStack(dataStack.size());
  return true;
}

bool handleROLL() {
  int ix, levels;
  if (popIntegerFromStack(&levels) == false) {
    return false;
  }
  unsigned char type0;
  for (ix = 0; ix < levels; ix++) {
    type0 = dataStack.at(dataStack.size() - ix - 1);
    if (type0 != xINTEGER && type0 != xFLOAT) {
      return false;
    }
  }
  if (type0 == xINTEGER) {
    ix = userIntegers.at(userIntegers.size() - 1);
    userIntegers.insert(userIntegers.end() - levels, ix);
    userIntegers.pop_back();
  } else if (type0 == xFLOAT) {
    ix = userFloats.at(userFloats.size() - 1);
    userFloats.insert(userFloats.end() - levels, ix);
    userFloats.pop_back();
  }
  return true;
}

bool handleROT() {
  putIntegerOnStack(3);
  return handleROLL();
}

bool handleSWAP() {
  if (dataStack.size() < 2) {
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (userIntegers.size() < 2) {
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      if (userFloats.size() < 2) {
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
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
  return true;
}

bool putIntegerOnJumpStack(int n) {
  enum dataType type = xINTEGER;
  jumpStack.push_back(n);
  return true;
}

bool putIntegerOnStack(int n) {
  enum dataType type = xINTEGER;
  userIntegers.push_back(n);
  dataStack.push_back(type);
  return true;
}

bool popFromLoopStack(int *value) {
  if (loopStack.size() == 0) {
    return false;
  }
  *value = loopStack.at(loopStack.size() - 1);
  loopStack.pop_back();
  return true;
}

bool popIntegerFromJumpStack(int *value) {
  *value = jumpStack.at(jumpStack.size() - 1);
  jumpStack.pop_back();
  return true;
}

bool popIntegerFromStack(int *value) {
  if (userIntegers.size() == 0) {
    return false;
  }
  *value = userIntegers.at(userIntegers.size() - 1);
  userIntegers.pop_back();
  dataStack.pop_back();
  return true;
}

bool popFloatFromStack(float *value) {
  if (userFloats.size() == 0) {
    return false;
  }
  *value = userFloats.at(userFloats.size() - 1);
  userFloats.pop_back();
  dataStack.pop_back();
  return true;
}

bool popStringFromStack(string *s) {
  if (userStrings.size() == 0) {
    return false;
  }
  *s = userStrings.at(userStrings.size() - 1);
  userStrings.pop_back();
  dataStack.pop_back();
  return true;
}

bool putFloatOnStack(float n) {
  enum dataType type = xFLOAT;
  userFloats.push_back(n);
  dataStack.push_back(type);
  return true;
}

bool lookupVAR(string name) {
  std::map<string, int>::iterator it;
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
  return false;
}

bool lookupUC(string name) {
  for (int ix = 0; ix < userCommands.size(); ix++) {
    if (name == userCommands[ix].name) {
      char code[256];
      strcpy(code, userCommands[ix].command.c_str());
      int savedExecutionPointer = executionPointer;
      vector<string> myChunks;
      myChunks = tokenize(code, myChunks);
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
  string nums("0123456789ABCDEF");
  nums = nums.substr(0, base);
  if (base == 10 && c.at(0) == '-') {
    sign = -1;
    c.erase(0, 1);
  }
  string::const_iterator it = c.begin();
  while (it != c.end() && nums.find(*it) != string::npos) ++it;
  if (c.empty() || it != c.end()) {
    return false;
  }
  try {
    *i0 = stoi(c, nullptr, base) * sign;
    return true;
  } catch (const invalid_argument &e) {
  } catch (const out_of_range &e) {
  }
  return false;
}

bool isFloat(string c, float *f0) {
  if (c.length() == 0) return false;
  if (GetINT("BASE") == 10) {
    try {
      *f0 = stof(c);
      return true;
    } catch (const invalid_argument &e) {
    } catch (const out_of_range &e) {
    }
  } else {
  }
  return false;
}

bool handleEXEC() {
  string s;
  if (popStringFromStack(&s) == false) {
    return false;
  }
  sprintf(msg, "%s\n", s.c_str());
  Serial.print(msg);
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
  executionPointer = 0;
  while (executionPointer < chunks.size()) {
    // executionPointer is global so that BEGIN – and later others – can change it.
    string c = chunks.at(executionPointer);
    if (lookupVAR(c)) {
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
        sprintf(msg, "%s name: `%s` is not valid!\n", ((c == "VARINT") ? "VAR" : "CONST"), c.c_str());
        Serial.print(msg);
        return;
      }
      bool thisIsInt = false;
      bool thisIsFloat = false;
      // we need a number
      if (popIntegerFromStack(&i0) == false) {
        if (popFloatFromStack(&f0) == false) {
        } else {
          thisIsFloat = true;
        }
      } else thisIsInt = true;
      if (!thisIsFloat && !thisIsInt) return;
      if (c == "VAR" && thisIsInt) {
        StoreINT(d, i0);
      } else if (c == "VAR" && thisIsFloat) {
        StoreFLOAT(d, f0);
      } else if (c == "CONST" && thisIsInt) {
        StoreCONSTINT(d, i0);
      } else if (c == "CONST" && thisIsFloat) {
        StoreCONSTFLOAT(d, f0);
      }
    } else if (isPrinting && c.back() == '"') {
      // print that
      c.pop_back();
      sprintf(msg, "%s ", c.c_str());
      Serial.print(msg);
      isPrinting = false;
      executionPointer += 1;
    } else if (c == ":") {
      // creation of a word
      executionPointer += 1;
      bool done = false, error = true;
      string miniChunks, dictName;
      dictName = chunks.at(executionPointer++);
      while (executionPointer < chunks.size() && !done) {
        c = chunks.at(executionPointer);
        if (c == ";") {
          done = true;
          error = false;
          executionPointer += 1;
        } else {
          miniChunks.append(c);
          miniChunks.append(" ");
          executionPointer += 1;
        }
      }
      if (error) {
        return;
      }
      userCommand x = { dictName, miniChunks };
      userCommands.push_back(x);
    } else {
      if (lookup(c, &r)) {
        if (r == false) {
          sprintf(msg, "%s returned false. Aborting!\n", c.c_str());
          Serial.print(msg);
          return;
        }
        executionPointer += 1;
      } else if (lookupUC(c)) {
        executionPointer += 1;
      } else if (isInteger(c, &i0)) {
        putIntegerOnStack(i0);
        executionPointer += 1;
      } else if (isFloat(c, &f0)) {
        putFloatOnStack(f0);
        executionPointer += 1;
      } else {
        return;
      }
    }
  }
}

vector<string> tokenize(char *code, vector<string> chunks) {
  // adds to the string vector chunks.
  // enables multi-line code
  unsigned int ln = strlen(code), ix = 0;
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
          // if (isPrinting && !insideString) {
          insideString = true;
          // cout << "" << endl;
        }
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
        char xxx[3] = { 0 };
        xxx[0] = code[ix++];
        xxx[1] = code[ix++];
        esc = stoi(string(xxx), nullptr, 16);
      }
      buffer[buffIndex++] = esc;
    } else if (c == '"' && insideString /* && code[ix + 1] < '!'*/) {
      insideString = false;
      buffer[buffIndex++] = c;
      buffer[buffIndex] = 0;
      string ss(buffer);
      //ss.append("\"");
      ix += 1;
      chunks.push_back(ss);
      memset(buffer, 0, 256);
      buffIndex = 0;
    } else {
      buffer[buffIndex++] = c;
    }
  }
  if (buffIndex > 0) {
    buffer[buffIndex + 1] = 0;
    chunks.push_back(buffer);
  }
  return chunks;
}

char code[256] = { 0 };
vector<string> chunks;

void setup() {
  Serial.begin(115200);
  delay(3000);
  initForth();
  strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
  sprintf(msg, "• Running code:\n\t%s\n", code);
  Serial.print(msg);
  Serial.println("\ttokenize.");
  chunks = tokenize(code, chunks);
  Serial.println("\tevaluate.");
  evaluate(chunks);
  chunks.resize(0);
  Serial.println("Done.");
  Serial.print("Enter code: ");
}

void loop() {
  if (Serial.available()) {
    // Serial.println("incoming from user on Serial.");
    char incoming[256];
    memset(incoming, 0, 256);
    uint8_t ix = 0;
    while (Serial.available()) {
      char c = Serial.read();
      delay(25);
      if (c == 13 || c == 10) {
        // cr / lf: we want to buffer lines and treat them one by one
        // when we're done receiving.
        if (ix > 0) {
          // only if we have a line to save:
          // if we receive CR + LF, the second byte would give us
          // an empty line.
          incoming[ix] = 0;
          string nextLine = string(incoming);
          userStrings.push_back(nextLine);
          ix = 0;
        }
      } else incoming[ix++] = c;
    }
  }
  if (userStrings.size() > 0) {
    vector<string> chunks;
    uint8_t ix, iy = userStrings.size();
    for (ix = 0; ix < iy; ix++) {
      sprintf(msg, "\t%s\n", userStrings[ix].c_str());
      Serial.print(msg);
      chunks = tokenize((char *)userStrings[ix].c_str(), chunks);
    }
    evaluate(chunks);
    userStrings.resize(0);
    Serial.print("\nEnter code: ");
  }
}
