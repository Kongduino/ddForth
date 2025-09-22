// Add #include "initForth2.hpp"
// As the last line of initForth()
// #include "display.hpp"
// in ddforth.hpp
// #include "displayHandles.hpp"
// after #include "lowercase.hpp"

#include "ddforth.hpp"
bool insideString;

using namespace std;

/*
myVARs + 0
myFVARs + 128
myCONSTs +256
myFCONSTs + 384
mySTRVARs + 512
mySTRCONSTs + 640
*/

void StoreCONSTFLOAT(string name, float value) {
  std::map<string, int>::iterator it;
  int ad;
  it = fconstAddresses.find(name);
  if (it == fconstAddresses.end()) {
    myFCONSTs.push_back(value);
    ad = myFCONSTs.size() - 1 + 384;
    fconstAddresses[name] = ad;
    xxxxxx = snprintf((char *)msg, 255, "FCONST name: %s initialized with %f\n", name.c_str(), value);
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "FCONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreCONSTINT(string name, int value) {
  std::map<string, int>::iterator it;
  it = constAddresses.find(name);
  if (it == constAddresses.end()) {
    myCONSTs.push_back(value);
    constAddresses[name] = myCONSTs.size() - 1 + 256;
    xxxxxx = snprintf((char *)msg, 255, "INT CONST name: %s initialized with %d\n", name.c_str(), value);
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "CONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreCONSTSTR(string name, string value) {
  std::map<string, int>::iterator it;
  it = strconstAddresses.find(name);
  if (it == strconstAddresses.end()) {
    mySTRCONSTs.push_back(value);
    strconstAddresses[name] = mySTRCONSTs.size() - 1 + 640;
    xxxxxx = snprintf((char *)msg, 255, "STR CONST name: %s initialized with %s\n", name.c_str(), value.c_str());
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "STRCONST %s already exists!\n", name.c_str());
    logThis();
  }
}

void StoreSTRING(string name, string value) {
  std::map<string, int>::iterator it;
  it = strvarAddresses.find(name);
  if (it != strvarAddresses.end()) {
    xxxxxx = snprintf(
      (char *)msg, 255,
      "Updating STR VAR name: %s at position %d to %s\n",
      name.c_str(), (it->second - 512), value.c_str());
    logThis();
    mySTRVARs.at(it->second - 512) = value;
    xxxxxx = snprintf((char *)msg, 255, "STR VAR name: %s updated to %s\n", name.c_str(), value.c_str());
    logThis();
  } else {
    mySTRVARs.push_back(value);
    strvarAddresses[name] = mySTRVARs.size() - 1 + 512;
    xxxxxx = snprintf((char *)msg, 255, "STR VAR name: %s initialized with %s\n", name.c_str(), value.c_str());
    logThis();
  }
}

void StoreFLOAT(string name, float value) {
  std::map<string, int>::iterator it;
  it = fvarAddresses.find(name);
  if (it != fvarAddresses.end()) {
    xxxxxx = snprintf((char *)msg, 255, "FVAR name: %s updated to %f\n", name.c_str(), value);
    logThis();
    myFVARs.at(it->second - 128) = value;
  } else {
    myFVARs.push_back(value);
    fvarAddresses[name] = myFVARs.size() - 1 + 128;
    xxxxxx = snprintf((char *)msg, 255, "FVAR name: %s initialized with %f\n", name.c_str(), value);
    logThis();
  }
}

void StoreINT(string name, int value) {
  std::map<string, int>::iterator it;
  it = varAddresses.find(name);
  if (it != varAddresses.end()) {
    myVARs.at(it->second) = value;
    xxxxxx = snprintf((char *)msg, 255, "INT VAR name: %s updated to %d\n", name.c_str(), value);
    logThis();
  } else {
    xxxxxx = snprintf((char *)msg, 255, "INT VAR name: %s initialized with %d\n", name.c_str(), value);
    logThis();
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

bool handleVARRAY() {
  // [data] num "name" VARRAY
  // s" Riri Fifi Loulou" SSPLIT s" PLAYERS" VARRAY
  // 1 2 3 4 4 s" dataNum" VARRAY
  // etc
  // it must be a new array
  string name;
  if (popStringFromStack(&name) == false) {
    logStackOverflow((char *)"handleVARRAY/0");
    return false;
  }
  int number;
  if (popIntegerFromStack(&number) == false) {
    logStackOverflow((char *)"handleVARRAY/1");
    return false;
  }
  int type0 = dataStack.at(dataStack.size() - 1);
  int type1, ix;
  for (ix = 1; ix < number; ix++) {
    type1 = dataStack.at(dataStack.size() - ix - 1);
    if (type0 != type1) {
      xxxxxx = snprintf((char *)msg, 255, "handleVARRAY/2/%d", ix);
      logInconsistent(msg);
      return false;
    }
  }
  // now let's check that the array doesn't exist...
  switch (type0) {
    case xINTEGER:
      {
        // cout << " INTEGER VARRAY ";
        std::map<string, vector<int>>::iterator it;
        it = myIntArrays.find(name);
        if (it != myIntArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/INT exists!\n", name.c_str());
          logThis();
          return false;
        }
        if (userIntegers.size() < number) {
          logStackOverflow((char *)"handleVARRAY/INT");
          return false;
        }
        vector<int> tmp;
        int i0;
        for (ix = 0; ix < number; ix++) {
          if (popIntegerFromStack(&i0) == false) {
            xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/INT pop fail!\n", name.c_str());
            logThis();
            return false;
          }
          tmp.push_back(i0);
        }
        myIntArrays[name] = tmp;
        return true;
        break;
      }
    case xFLOAT:
      {
        // cout << " FLOAT VARRAY ";
        std::map<string, vector<float>>::iterator itF;
        itF = myFloatArrays.find(name);
        if (itF != myFloatArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/Float exists!\n", name.c_str());
          logThis();
          return false;
        }
        vector<float> tmpF;
        float f0;
        for (ix = 0; ix < number; ix++) {
          if (popFloatFromStack(&f0) == false) {
            xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/FLOAT pop fail!\n", name.c_str());
            logThis();
            return false;
          }
          tmpF.push_back(f0);
        }
        myFloatArrays[name] = tmpF;
        return true;
        break;
      }
    case xSTRING:
      {
        // cout << " STRING VARRAY ";
        std::map<string, vector<string>>::iterator itS;
        itS = myStringArrays.find(name);
        if (itS != myStringArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/String exists!\n", name.c_str());
          logThis();
          return false;
        }
        vector<string> tmpS;
        string s0;
        for (ix = 0; ix < number; ix++) {
          if (popStringFromStack(&s0) == false) {
            xxxxxx = snprintf((char *)msg, 255, "handleVARRAY %s/STR pop fail!\n", name.c_str());
            logThis();
            return false;
          }
          tmpS.push_back(s0);
        }
        myStringArrays[name] = tmpS;
        return true;
        break;
      }
  }
  return false;
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
  cout << "Handled in Code:" << endl
       << "----------------" << endl;
  for (vector<string>::iterator it = computedWords.begin(); it != computedWords.end(); ++it) {
    string s = *it;
    printf(" • %-11s (Handled in code)\n", s.c_str());
  }
  cout << endl
       << "Native Commands:" << endl
       << "----------------" << endl;
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    // printf(" • %-11s (Native command)\n", nativeCommands[ix].name.c_str());
    cout << nativeCommands[ix].name << " ";
  }
  cout << endl
       << endl
       << "User Commands:" << endl
       << "--------------" << endl;
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
    return false;
  }
  int max, min;
  if (popIntegerFromStack(&min) == false) {
    logStackOverflow((char *)"handleDO");
    return false;
  }
  if (popIntegerFromStack(&max) == false) {
    logStackOverflow((char *)"handleDO");
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

bool handlePlusLoop() {
  // val +LOOP ---> I = I + val
  if (loopStack.size() == 0) {
    cout << "Loop Stack empty! ";
    return false;
  }
  int value;
  if (popIntegerFromStack(&value) == false) {
    logStackOverflow((char *)"handlePlusLoop");
    return false;
  }
  loopStack.at(loopStack.size() - 1) += (value - 1);
  // -1 because handleLOOP() is going to add 1
  return handleLOOP();
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
#if defined(DEBUG)
  cout << endl
       << "myVARs.size: " << myVARs.size() << " myFVARs.size: " << myFVARs.size()
       << " varAddresses.size: " << varAddresses.size()
       << " fvarAddresses.size: " << fvarAddresses.size() << endl;
  cout << "myCONSTs.size: " << myCONSTs.size() << " myFCONSTs.size: " << myFCONSTs.size()
       << " constAddresses.size: " << constAddresses.size()
       << " fconstAddresses.size: " << fconstAddresses.size();
#endif
  if (myVARs.size() > 0) {
    cout << endl
         << "+-----------------------------------------+" << endl;
    cout << "| Num     |  VAR Name   | Addr | Value    |";
    cout << endl
         << "+-----------------------------------------+" << endl;
    std::map<string, int>::iterator it = varAddresses.begin();
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
    cout << endl
         << "+-----------------------------------------+" << endl;
    std::map<string, int>::iterator it = fvarAddresses.begin();
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
    cout << endl
         << "+-----------------------------------------+" << endl;
    std::map<string, int>::iterator it = constAddresses.begin();
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
    cout << endl
         << "+-----------------------------------------+" << endl;
    std::map<string, int>::iterator it = fconstAddresses.begin();
    int ix = 0;
    while (it != fconstAddresses.end()) {
      string n = it->first;
      printf(
        "| %3d/%-3zu | %-11s | %4d |%9f |\n",
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
  xxxxxx = snprintf((char *)msg, 255, "handleRetrieve var %d ", ad);
  logThis();
  /*
myVARs + 0
myFVARs + 128
myCONSTs + 256
myFCONSTs + 384
mySTRVARs + 512
mySTRCONSTs + 640
*/
  if (ad < 128) return putIntegerOnStack(myVARs.at(ad));
  else if (ad < 256) return putFloatOnStack(myFVARs.at(ad - 128));
  else if (ad < 384) putIntegerOnStack(myCONSTs.at(ad - 256));
  else if (ad < 512) return putFloatOnStack(myFCONSTs.at(ad - 384));
  else if (ad < 640) return putStringOnStack(mySTRVARs.at(ad - 512));
  else return putStringOnStack(mySTRCONSTs.at(ad - 640));
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
  getline(cin, s);  // Reads the entire line
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
  it = strvarAddresses.find(name);
  if (it != strvarAddresses.end()) {
    // found it
    putIntegerOnStack(it->second);
    return true;
  }
  it = strconstAddresses.find(name);
  if (it != strconstAddresses.end()) {
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
  if (popStringFromStack(&s) == false) {
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

bool isInsideIF = false;
bool isTrueIF = false;
bool skipElse = false;
bool handleIF() {
  int i0;
  if (popIntegerFromStack((int *)&i0) == false) {
    logStackOverflow((char *)"handleIF");
    return false;
  }
  isInsideIF = true;
  if (i0 == 0) {
    isTrueIF = false;
    skipElse = false;
  } else {
    isTrueIF = true;
    skipElse = false;
  }
  return true;
}

bool handleTHEN() {
  skipElse = true;
  return true;
}

bool handleELSE() {
  isInsideIF = false;
  isTrueIF = false;
  skipElse = false;
  return true;
}

bool isExiting = false;
bool handleEXIT() {
  isExiting = true;
  return true;
}

bool isInsideParens = false;
bool handleParens() {
  isInsideParens = true;
  return true;
}

bool handleCELLLENGTH() {
  string name;  // array name
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLENGTH: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLENGTH %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    putIntegerOnStack(tmp.size());
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLENGTH %s/float does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    putIntegerOnStack(tmpF.size());
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLENGTH %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  putIntegerOnStack(tmpS.size());
  return true;
}

bool handleCELLS() {
  int number;   // number of cells
  string name;  // array name
  // originalValue number name ARRAY
  if (dataStack.size() < 3) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLS: not enough data on the stack!\n");
    logThis();
    return false;
  }
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLS: No NAME on the stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&number) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLS: No NUMBER on the stack!\n");
    logThis();
    return false;
  }
  switch (dataStack.at(dataStack.size() - 1)) {
    case (xINTEGER):
      {
        std::map<string, vector<int>>::iterator it;
        it = myIntArrays.find(name);
        if (it != myIntArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS %s already exists!\n", name.c_str());
          logThis();
          return false;
        }
        int intValue;
        if (popIntegerFromStack(&intValue) == false) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS: No INT ORIGINALVALUE on the stack!\n");
          logThis();
          return false;
        }
        // We create a vector with number x originalValue
        vector<int> tmp(number, intValue);
        myIntArrays[name] = tmp;
        return true;
        break;
      }
    case (xFLOAT):
      {
        std::map<string, vector<float>>::iterator it;
        it = myFloatArrays.find(name);
        if (it != myFloatArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS %s already exists!\n", name.c_str());
          logThis();
          return false;
        }
        float floatValue;
        if (popFloatFromStack(&floatValue) == false) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS: No FLOAT ORIGINALVALUE on the stack!\n");
          logThis();
          return false;
        }
        // We create a vector with number x originalValue
        vector<float> tmp(number, floatValue);
        myFloatArrays[name] = tmp;
        return true;
        break;
      }
    case (xSTRING):
      {
        std::map<string, vector<string>>::iterator it;
        it = myStringArrays.find(name);
        if (it != myStringArrays.end()) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS %s already exists!\n", name.c_str());
          logThis();
          return false;
        }
        string stringValue;
        if (popStringFromStack(&stringValue) == false) {
          xxxxxx = snprintf((char *)msg, 255, "handleCELLS: No STRING ORIGINALVALUE on the stack!\n");
          logThis();
          return false;
        }
        // We create a vector with number x originalValue
        vector<string> tmp(number, stringValue);
        myStringArrays[name] = tmp;
        return true;
        break;
      }
  }
  return false;
}

bool handleARRAYLIST() {
  cout << "Integer arrays: ";
  if (myIntArrays.size() == 0) {
    cout << 0 << endl;
  } else {
    cout << myIntArrays.size() << endl;
    std::map<string, vector<int>>::iterator it;
    for (
      std::map<string, vector<int>>::iterator it = myIntArrays.begin();
      it != myIntArrays.end();
      ++it)
      std::cout << "* " << it->first << endl;
  }
  cout << "Float arrays: ";
  if (myFloatArrays.size() == 0) {
    cout << 0 << endl;
  } else {
    cout << myFloatArrays.size() << endl;
    std::map<string, vector<int>>::iterator itF;
    for (
      std::map<string, vector<float>>::iterator itF = myFloatArrays.begin();
      itF != myFloatArrays.end();
      ++itF)
      std::cout << "* " << itF->first << endl;
  }
  cout << "String arrays: ";
  if (myStringArrays.size() == 0) {
    cout << 0 << endl;
  } else {
    cout << myStringArrays.size() << endl;
    std::map<string, vector<string>>::iterator it;
    for (
      std::map<string, vector<string>>::iterator itS = myStringArrays.begin();
      itS != myStringArrays.end();
      ++itS)
      std::cout << "* " << itS->first << endl;
  }
  return true;
}

bool handleARRAYSUM() {
  string name;  // array name
  int ix;
  float f0;
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleARRAYSUM: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleARRAYSUM %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    ix = 0;
    for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
      ix += *it;
    }
    putIntegerOnStack(ix);
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleARRAYSUM %s/float does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    f0 = 0.0;
    for (std::vector<float>::iterator itF = tmpF.begin(); itF != tmpF.end(); ++itF) {
      f0 += *itF;
    }
    putFloatOnStack(ix);
    return true;
  }
  return false;
}

bool handleCELLLIST() {
  string name;  // array name
  int ix;
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLIST: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLIST %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    ix = 0;
    for (std::vector<int>::iterator it = tmp.begin(); it != tmp.end(); ++it) {
      xxxxxx = snprintf((char *)msg, 255, "Cell #%d: %d\n", ix++, *it);
      cout << msg;
    }
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLIST %s/float does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    ix = 0;
    for (std::vector<float>::iterator itF = tmpF.begin(); itF != tmpF.end(); ++itF) {
      xxxxxx = snprintf((char *)msg, 255, "Cell #%d: %f\n", ix++, *itF);
      cout << msg;
    }
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLIST %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  ix = 0;
  for (std::vector<string>::iterator itS = tmpS.begin(); itS != tmpS.end(); ++itS) {
    //xxxxxx = snprintf((char *)msg, 255, "Cell #%d: %s\n", ix++, *itS->c_str());
    cout << "Cell #" << ix++ << ": " << *itS << endl;
  }
  return true;
}

bool handleCELLSTORE() {
  int number;   // cell number
  string name;  // array name
  // value number name >IX
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE: No NAME on the stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&number) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE: No INDEX on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    if (number >= tmp.size() || number < 0) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %d/%zu INT out of range!\n", number, tmp.size());
      logThis();
    }
    int intValue;
    if (popIntegerFromStack(&intValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE: No INT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmp.at(number) = intValue;
    myIntArrays[name] = tmp;
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %s/FLOAT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    if (number >= tmpF.size() || number < 0) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %d/FLOAT out of range!\n", number);
      logThis();
    }
    float floatValue;
    if (popFloatFromStack(&floatValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE: No FLOAT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmpF.at(number) = floatValue;
    myFloatArrays[name] = tmpF;
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  if (number >= tmpS.size() || number < 0) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE %d/STRING out of range!\n", number);
    logThis();
  }
  string strValue;
  if (popStringFromStack(&strValue) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLSTORE: No STR ORIGINALVALUE on the stack!\n");
    logThis();
    return false;
  }
  tmpS.at(number) = strValue;
  myStringArrays[name] = tmpS;
  return true;
}

bool handleCELLRETRIEVE() {
  int number;   // cell number
  string name;  // array name
  // number name ARRAY
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE: No NAME on the stack!\n");
    logThis();
    return false;
  }
  if (popIntegerFromStack(&number) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE: No INDEX on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    if (number >= tmp.size() || number < 0) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE %d/%zu INT out of range!\n", number, tmp.size());
      logThis();
      return false;
    }
    putIntegerOnStack(tmp.at(number));
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE %s/FLOAT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    if (number >= tmpF.size() || number < 0) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE %d/FLOAT out of range!\n", number);
      logThis();
      return false;
    }
    putFloatOnStack(tmpF.at(number));
    return true;
  }

  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRETRIEVE %s/STRING does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  if (number >= tmpS.size() || number < 0) {
    xxxxxx = snprintf(
      (char *)msg, 255,
      "handleCELLRETRIEVE %d/STRING/%zu out of range!\n",
      number, tmpS.size());
    logThis();
    return false;
  }
  putStringOnStack(tmpS.at(number));
  return true;
}

bool handleCELLPREPEND() {
  string name;  // array name
  // number name ARRAY
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    int intValue;
    if (popIntegerFromStack(&intValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND: No INT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmp.insert(tmp.begin(), intValue);
    myIntArrays[name] = tmp;
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND %s/FLOAT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    float floatValue;
    if (popFloatFromStack(&floatValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND: No FLOAT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmpF.insert(tmpF.begin(), floatValue);
    myFloatArrays[name] = tmpF;
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  string strValue;
  if (popStringFromStack(&strValue) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLPREPEND: No STR ORIGINALVALUE on the stack!\n");
    logThis();
    return false;
  }
  tmpS.insert(tmpS.begin(), strValue);
  myStringArrays[name] = tmpS;
  return true;
}

bool handleCELLAPPEND() {
  string name;  // array name
  // number name ARRAY
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    int intValue;
    if (popIntegerFromStack(&intValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND: No INT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmp.push_back(intValue);
    myIntArrays[name] = tmp;
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND %s/FLOAT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    float floatValue;
    if (popFloatFromStack(&floatValue) == false) {
      xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND: No FLOAT ORIGINALVALUE on the stack!\n");
      logThis();
      return false;
    }
    tmpF.push_back(floatValue);
    myFloatArrays[name] = tmpF;
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  string strValue;
  if (popStringFromStack(&strValue) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLAPPEND: No STR ORIGINALVALUE on the stack!\n");
    logThis();
    return false;
  }
  tmpS.push_back(strValue);
  myStringArrays[name] = tmpS;
  return true;
}

bool handleCELLLROT() {
  string name;  // array name
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLROT: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLROT %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    int i0 = tmp.at(0);
    tmp.push_back(i0);
    tmp.erase(tmp.begin());
    myIntArrays[name] = tmp;
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLROT %s/float does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    float f0 = tmpF.at(tmpF.size() - 1);
    tmpF.push_back(f0);
    tmpF.erase(tmpF.begin());
    myFloatArrays[name] = tmpF;
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLLROT %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  string s0 = tmpS.at(tmpS.size() - 1);
  tmpS.push_back(s0);
  tmpS.erase(tmpS.begin());
  myStringArrays[name] = tmpS;
  return true;
}

bool handleCELLRROT() {
  string name;  // array name
  if (popStringFromStack(&name) == false) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRROT: No NAME on the stack!\n");
    logThis();
    return false;
  }
  std::map<string, vector<int>>::iterator it;
  it = myIntArrays.find(name);
  if (it == myIntArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRROT %s/INT does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<int> tmp = it->second;
    int i0 = tmp.at(tmp.size() - 1);
    tmp.insert(tmp.begin(), i0);
    tmp.pop_back();
    myIntArrays[name] = tmp;
    return true;
  }
  std::map<string, vector<float>>::iterator itF;
  itF = myFloatArrays.find(name);
  if (itF == myFloatArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRROT %s/float does not exist!\n", name.c_str());
    logThis();
  } else {
    vector<float> tmpF = itF->second;
    float f0 = tmpF.at(tmpF.size() - 1);
    tmpF.insert(tmpF.begin(), f0);
    tmpF.pop_back();
    myFloatArrays[name] = tmpF;
    return true;
  }
  std::map<string, vector<string>>::iterator itS;
  itS = myStringArrays.find(name);
  if (itS == myStringArrays.end()) {
    xxxxxx = snprintf((char *)msg, 255, "handleCELLRROT %s/String does not exist!\n", name.c_str());
    logThis();
    return false;
  }
  vector<string> tmpS = itS->second;
  string s0 = tmpS.at(tmpS.size() - 1);
  tmpS.insert(tmpS.begin(), s0);
  tmpS.pop_back();
  myStringArrays[name] = tmpS;
  return true;
}

void cleanup() {
  handleCLEAR();
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
    string cl = c;
    std::transform(cl.begin(), cl.end(), cl.begin(), ::tolower);
    // lowercase version
    xxxxxx = snprintf((char *)msg, 255, "\nEvaluating '%s' executionPointer: %d \n", c.c_str(), executionPointer);
    logThis();
#if defined(DEBUG)
    cout << "+-------+---------------------------------------------------+" << endl;
    for (int xx = 0; xx < chunks.size(); xx++) {
      printf("|%c%-5d | %-50s|\n", ((xx == executionPointer) ? '*' : ' '), xx, chunks.at(xx).c_str());
    }
    cout << "+-------+---------------------------------------------------+" << endl;
#endif
    if (isExiting) {
      isExiting = false;
      executionPointer = chunks.size();
    } else if (isInsideIF && !isTrueIF) {
      // Skip to after then
      while (chunks.at(executionPointer) != "THEN") {
        executionPointer += 1;
      }
      executionPointer += 1;
      isInsideIF = false;
    } else if (isInsideIF && isTrueIF && skipElse) {
      while (chunks.at(executionPointer) != "ELSE") {
        executionPointer += 1;
      }
      isInsideIF = false;
    } else if (isInsideParens) {
      executionPointer += 1;
      isInsideParens = false;
      while (chunks.at(executionPointer) != ")")
        executionPointer += 1;
      executionPointer += 1;
    } else if (cl == "var" || cl == "const") {
      // creation of a variable
      executionPointer += 1;
      string d = chunks.at(executionPointer++);
      int i0, x = dataStack.at(dataStack.size() - 1);
      float f0;
      string s0;
      bool thisIsInt = (x) == xINTEGER;
      bool thisIsFloat = (x) == xFLOAT;
      bool thisIsString = (x) == xSTRING;
      // we need something
      if (!thisIsFloat && !thisIsInt && !thisIsString) {
        xxxxxx = snprintf((char *)msg, 255, "No INT / FLOAT / STRING on the stack!\n");
        logThis();
        cleanup();
        return;
      }
      switch (x) {
        case xINTEGER:
          {
            if (popIntegerFromStack(&i0) == false) {
              xxxxxx = snprintf((char *)msg, 255, "No INT on the stack!\n");
              logThis();
              cleanup();
              return;
            }
            break;
          }
        case xFLOAT:
          {
            if (popFloatFromStack(&f0) == false) {
              xxxxxx = snprintf((char *)msg, 255, "No FLOAT on the stack!\n");
              logThis();
              cleanup();
              return;
            }
            break;
          }
        case xSTRING:
          {
            if (popStringFromStack(&s0) == false) {
              xxxxxx = snprintf((char *)msg, 255, "No STR on the stack!\n");
              logThis();
              cleanup();
              return;
            }
            break;
          }
      }
      if (cl == "var" && thisIsInt) {
        StoreINT(d, i0);
      } else if (cl == "var" && thisIsFloat) {
        StoreFLOAT(d, f0);
      } else if (cl == "const" && thisIsInt) {
        StoreCONSTINT(d, i0);
      } else if (cl == "const" && thisIsFloat) {
        StoreCONSTFLOAT(d, f0);
      } else if (cl == "var" && thisIsString) {
        StoreSTRING(d, s0);
      } else if (cl == "const" && thisIsString) {
        StoreCONSTSTR(d, s0);
      }
    } else if (lookupVAR(c)) {
      xxxxxx = snprintf((char *)msg, 255, "Put address of %s on stack. ", c.c_str());
      logThis();
      executionPointer += 1;
    } else if (insideString && c.back() == '"') {
      c.pop_back();
      insideString = false;
      if (isStackingString) {
        isStackingString = false;
        putStringOnStack(c);
      } else {
        cout << c;
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
          cleanup();
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
        cout << msg;
        return;
      }
    }
  }
}

vector<string> tokenize(char *cc, vector<string> chunks) {
  // adds to the string vector chunks.
  // enables multi-line code
  unsigned int ln = strlen(cc), ix = 0;
  cc[ln++] = 10;
  cc[ln] = 0;
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
    buffer[buffIndex] = 0;
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

void setup() {
  Serial.begin(115200);
  initForth();
  vector<string> chunks;
  // strcpy(code,
  // "255 0 0 setcolor cls 240 0 do I 0 i 128 + DUP drawline I 1 + >R loop display 10 delay"
  // );
  M5Cardputer.update();
  bool BtnG0 = M5Cardputer.BtnA.wasPressed();
  if (BtnG0) {
    Serial.println("Button A Pressed");
  }

  int fc = listAllFiles();
  if (fc == 0 || BtnG0) {
    SPIFFS.remove("/t0.fs");
    File file = SPIFFS.open("/t0.fs", FILE_WRITE);
    file.print("255 0 0 setcolor cls 240 0 do I 0 239 I 0.66 * INT drawline I 2 +loop display 10 delay");
    file.close();
    int fc = listAllFiles();
  }
  vector<string> thisBlock = loadFile("/t1.fs");
  cout << "loadFile " << thisBlock.size() << endl;
  for (vector<string>::iterator it = thisBlock.begin(); it != thisBlock.end(); ++it) {
    strcpy(code, it->c_str());
    cout << "Tokenizing " << *it << endl;
    chunks = tokenize(code, chunks);
  }

  evaluate(chunks);
  memset(code, 0, 256);
  chunks.clear();

  commonPrint("OK ");
  kbdSprite.createSprite(240, 104);
  kbdSprite.setTextFont(&fonts::FreeMono12pt7b);
  kbdSprite.setTextSize(1.0);
  kbdSprite.drawString(msg, 4, 4);
}

void loop() {
  char kbdData[256];
  uint8_t kbdIdx;
  uint8_t fh = kbdSprite.fontHeight();
  uint16_t py = 4;
  kbdIdx = 0;
  memset(kbdData, 0, 256);
  uint32_t t0, t1;
  uint8_t px = 0;
  char carret[2] = { ' ', '_' };
  t0 = millis();
  while (true) {
    M5Cardputer.update();
    if (M5Cardputer.Keyboard.isChange()) {
      if (M5Cardputer.Keyboard.isPressed()) {
        Keyboard_Class::KeysState status = M5Cardputer.Keyboard.keysState();
        if (status.del) {
          if (kbdIdx > 0) kbdIdx--;
          kbdData[kbdIdx] = 0;
        }
        if (status.enter) {
          vector<string> chunks;
          kbdData[kbdIdx] = 0;
          strcpy(code, kbdData);
          chunks = tokenize(code, chunks);
          display.clear();
          display.setTextDatum(top_left);
          display.setCursor(0, 0);
          // display.drawString("", 4, 4);
          sprintf(msg, "OK %s\n", kbdData);
          commonPrint(msg);
          evaluate(chunks);
          memset(code, 0, 256);
          chunks.clear();
          kbdIdx = 0;
          return;
        } else {
          for (auto i : status.word) {
            if (i > 31) kbdData[kbdIdx++] = i;
          }
        }
        Serial.println(msg);
        kbdSprite.fillRect(0, 0, 240, 128, TFT_BLACK);
        px = 255 - px;
        memset(msg, 0, 256);
        sprintf(msg, "OK %s%c", kbdData, carret[px & 1]);
        uint8_t tw = strlen(msg);
        if (tw < 16) {
          kbdSprite.drawString(msg, 4, 4);
        } else {
          uint8_t n = 0;
          char c;
          py = 4;
          while (n < kbdIdx + 3) {
            uint8_t nx = n + 15;
            c = msg[nx];
            msg[nx] = 0;
            kbdSprite.drawString(msg + n, 4, py);
            msg[nx] = c;
            py += fh;
            n += 15;
          }
        }
        // kbdSprite.drawString("OK ", 4, 204);
        kbdSprite.pushSprite(0, 24);
      }
    } else delay(100);
  }
}
