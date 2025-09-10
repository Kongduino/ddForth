using namespace std;
extern vector<int> dataStack;
extern int executionPointer;
extern vector<int> jumpStack;
extern vector<int> jumpStackType;
extern vector<int> loopStack;
extern vector<string> userStrings;
extern vector<int> userIntegers;
extern vector<string> blocks;
extern vector<float> userFloats;
extern unsigned char myRAM[64 * 1024];
extern bool isPrinting;
extern map<string, int> varAddresses;
extern map<string, int> fvarAddresses;
extern map<string, int> constAddresses;
extern map<string, int> fconstAddresses;
extern vector<int> myVARs;
extern vector<float> myFVARs;
extern vector<int> myCONSTs;
extern vector<float> myFCONSTs;
extern vector<string> computedWords;
extern char code[256];
extern int xxxxxx;
extern char msg[256];

bool checkTypes(int levels, unsigned char n) {
  if (dataStack.size() < levels) return false;
  for (int ix = 0; ix < levels; ix++) {
    if (dataStack.at(dataStack.size() - 1 - ix) != n) return false;
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
  int myInts = userIntegers.size() - 1;
  int myFloats = userFloats.size() - 1;
  int myStrings = userStrings.size() - 1;
#if defined(DEBUG)
  cout << "\tdataStack.size()\t" << (x + 1);
  cout << "\tmyInts\t" << (myInts + 1);
  cout << "\tmyFloats\t" << (myFloats + 1);
  cout << "\tmyStrings\t" << (myStrings + 1) << endl;
#endif
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

bool handleOVER() {
  logStack((char *)"handleOVER");
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char *)"handleOVER");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char *)"handleOVER1");
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char *)"handleOVER2");
        return false;
      }
      putIntegerOnStack(i1);
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char *)"handleOVER3");
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char *)"handleOVER4");
        return false;
      }
      xxxxxx = snprintf((char *)msg, 255, "2 FLOATs ");
      logThis();
      putFloatOnStack(f1);
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  } else {
    // one int one float
    xxxxxx = snprintf((char *)msg, 255, "OVER requires 2 ints or 2 floats!\n");
    logThis();
    return false;
  }
  return false;
}

bool handleDROP() {
  if (dataStack.size() == 0) {
    logStackOverflow((char *)"handleDROP");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  switch (type0) {
    case xINTEGER:
      int i0;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char *)"handleDROP1");
        return false;
      }
      return true;
      break;
    case xFLOAT:
      float f0;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char *)"handleDROP2");
        return false;
      }
      return true;
      break;
  }
  return false;
}

bool handleDUP() {
  if (dataStack.size() == 0) {
    logStackOverflow((char *)"handleDUP");
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

bool handleCLEAR() {
  logStack((char *)"handleCLEAR");
  dataStack.clear();
  userStrings.clear();
  userFloats.clear();
  userIntegers.clear();
  return true;
}

bool handleDEPTH() {
  logStack((char *)"handleDEPTH");
  putIntegerOnStack(dataStack.size());
  return true;
}

bool handleROLL() {
  int ix, levels;
  if (popIntegerFromStack(&levels) == false) {
    logStackOverflow((char *)"handleROLL");
    return false;
  }
  unsigned char type0;
  for(ix = 0; ix < levels; ix++) {
    type0 = dataStack.at(dataStack.size() - ix - 1);
    if (type0 != xINTEGER && type0 != xFLOAT) {
      logInconsistent((char *)"handleROLL");
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
  logStack((char *)"handleROT");
  if (dataStack.size() < 2) {
    logStackOverflow((char *)"handleSWAP");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char *)"handleSWAP");
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (userIntegers.size() < 2) {
        logStackOverflow((char *)"handleSWAP1");
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char *)"handleSWAP2");
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char *)"handleSWAP3");
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      if (userFloats.size() < 2) {
        logStackOverflow((char *)"handleSWAP4");
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char *)"handleSWAP5");
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char *)"handleSWAP6");
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

bool popStringFromStack(string* s) {
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

