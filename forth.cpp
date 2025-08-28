#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
// vector<string> userStrings;

bool showStack();
bool handleCR();
bool handleSWAP();
bool handleROT();
bool handleEqual();
bool handleLower();
bool handleHigher();
bool handlePlus();
bool handleMinus();
bool handleMult();
bool handleDiv();
bool handlePRINT();
bool handleUPRINT();
bool handleDUP();
bool handleOVER();
bool putIntegerOnStack(int);
bool popIntegerFromStack(int *);
bool putFloatOnStack(float);
bool popFloatFromStack(float *);
bool lookup(string);
bool lookupUC(string);
bool putStringOnStack(string);
void initForth();
bool handleStore();
bool handleRetrieve();
bool handleBASE();
bool handleBASE2();
bool handleBASE10();
bool handleBASE16();
bool handleUNTIL();
bool handleBEGIN();
vector<string> tokenize(char *);
void evaluate(vector<string>);

unsigned char dataStack[1024] = { 0 };
unsigned int dataStackPointer = 0;
unsigned int intCounter = 0;
unsigned int floatCounter = 0;
unsigned int stringCounter = 0;
int executionPointer = -1;
vector<int> jumpStack;
vector<int> jumpStackType;
vector<string> userStrings;
vector<int> userIntegers;
vector<float> userFloats;
unsigned char myRAM[64 * 1024] = { 0 };
enum varAddresses {
  BASE_ADDRESS,
  FREE_ADDRESS,  // You can peek and poke from here
};

struct nativeCommand {
  bool (*ptr)(void);  // Function pointer
  string name;
};

nativeCommand nativeCommands[] = {
  { handlePlus, "+" },
  { handleMinus, "-" },
  { handleMult, "*" },
  { handleDiv, "/" },
  { handlePRINT, "." },
  { handleUPRINT, "U." },
  { handleDUP, "DUP" },
  { handleSWAP, "SWAP" },
  { handleROT, "ROT" },
  { handleOVER, "OVER" },
  { handleBASE, "BASE" },
  { handleBASE2, "BIN" },
  { handleBASE10, "DEC" },
  { handleBASE16, "HEX" },
  { handleStore, "!" },
  { handleRetrieve, "?" },
  { handleCR, "CR" },
  { showStack, ".S" },
  { handleEqual, "=" },
  { handleLower, "<" },
  { handleHigher, ">" },
  { handleBEGIN, "BEGIN" },
  { handleUNTIL, "UNTIL" },
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

bool checkTypes(int, unsigned char);
bool checkTypes(int levels, unsigned char n) {
  if (dataStackPointer < levels) return false;
  for (int ix = 0; ix < levels; ix++) {
    if (dataStack[dataStackPointer - 1 - ix] != n) return false;
  }
  return true;
}

bool handleBEGIN() {
  // BEGIN ... <condition> UNTIL
  cout << endl << "BEGIN at ";
  jumpStack.push_back(executionPointer + 1);
  jumpStackType.push_back(xBEGIN);
  cout << (executionPointer + 1) << endl;
  return true;
}

bool handleUNTIL() {
  cout << endl << "UNTIL at " << executionPointer << " looping back to ";
  int i0, type0;
  if (jumpStack.size() == 0) {
    cout << "handleUNTIL JumpStack overflow!" << endl;
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
    cout << "handleUNTIL JumpStackType overflow!" << endl;
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
    cout << "handleUNTIL Stack overflow!" << endl;
    return false;
  }
  if (i0 < 0 || i0 > 1) {
    cout << "handleUNTIL " << i0 << " is not a BOOLEAN!" << endl;
    return false;
  }
  if (i0 == 0) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
    cout << executionPointer << ". Condition: " << i0 << endl;
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
    cout << " Ending BEGIN" << endl;
  }
  return true;
}

bool showStack() {
  int count = 0;
  if (dataStackPointer == 0) {
    cout << "Stack empty! ";
    return true;
  }
  cout << endl;  // << "showStack " << dataStackPointer;
  int x = dataStackPointer - 1;
  int myInts = intCounter - 1;
  int myFloats = floatCounter - 1;
  int myStrings = stringCounter - 1;
  // cout << "\tmyInts\t" << (myInts + 1);
  // cout << "\tmyFloats\t" << (myFloats + 1);
  // cout << "\tmyStrings\t" << (myStrings + 1) << endl;
  cout << "+-----------------------+" << endl;
  while (x > -1) {
    int type0 = dataStack[x];
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

void initForth() {
  // cout << "init ";
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  userCmdCount = userCommands.size();
  myRAM[BASE_ADDRESS] = 10;
  string name("0=");
  string code("0 =");
  cout << "Adding word " << name << " with `" << code << "`" << endl;
  userCommand x = { name, code };
  userCommands.push_back(x);
}

bool handleCR() {
  cout << endl;
  return true;
}

bool handleStore() {
  // cout << "handleStore: intCounter " << intCounter << " dataStackPointer " << dataStackPointer << " ";
  if (!checkTypes(2, xINTEGER)) {
    cout << "handleStore Not enough integers!" << endl;
    return false;
  }
  int ad, x;
  if (popIntegerFromStack(&x) == false) {
    cout << "handleStore1 Stack overflow!" << endl;
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
    cout << "handleStore2 Stack overflow!" << endl;
    return false;
  }
  // cout << "storing " << x << " into RAM[" << ad << "] ";
  myRAM[ad] = (unsigned char)x;
  return true;
}

bool handleRetrieve() {
  // cout << "handleRetrieve: dataStackPointer " << dataStackPointer << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  if (!checkTypes(1, xINTEGER)) {
    cout << "handleRetrieve Not enough integers!" << endl;
    return false;
  }
  int ad;
  if (popIntegerFromStack(&ad) == false) {
    cout << "handleRetrieve1 Stack overflow!" << endl;
    return false;
  }
  // cout << "handleRetrieve end ";
  return putIntegerOnStack(myRAM[ad]);
}

bool handleBASE() {
  // cout << "handleBASE ";
  return putIntegerOnStack(BASE_ADDRESS);
}

bool handleBASE2() {
  // cout << "handleBASE2 ";
  myRAM[BASE_ADDRESS] = 2;
  return true;
}

bool handleBASE10() {
  // cout << "handleBASE10 ";
  myRAM[BASE_ADDRESS] = 10;
  return true;
}

bool handleBASE16() {
  // cout << "handleBASE16 ";
  myRAM[BASE_ADDRESS] = 16;
  return true;
}

bool printOtherBases(int number, int base) {
  if (base > 16) {
    myRAM[BASE_ADDRESS] = 16;
    base = 16;
  }
  unsigned int uNumber = number;
  char buffer[32] = { 0 };
  unsigned char ix = 0;
  while (number >= base) {
    int q = uNumber % base;
    uNumber = uNumber / base;
    buffer[ix++] = numerics[q];
  }
  buffer[ix] = numerics[uNumber];
  for (unsigned char n = 0; n < (ix >> 1); n++) {
    unsigned char b = buffer[n];
    buffer[n] = buffer[ix - n];
    buffer[ix - n] = b;
  }
  printf("%s ", buffer);
  return true;
}

bool handlePRINT() {
  // cout << "handlePRINT: dataStackPointer " << dataStackPointer << " ";
  if (dataStackPointer == 0) {
    cout << "handlePRINT Stack overflow!" << endl;
    return false;
  }
  unsigned char x = dataStack[dataStackPointer - 1];
  switch (x) {
    case xINTEGER:
      {
        int i0;
        if (popIntegerFromStack(&i0) == false) {
          cout << "handlePRINT1 Stack overflow!" << endl;
          return false;
        }
        int base = myRAM[BASE_ADDRESS];
        if (base == 10) cout << i0 << " ";
        else printOtherBases(i0, base);
        break;
      }
    case xFLOAT:
      {
        float f0;
        if (popFloatFromStack(&f0) == false) {
          cout << "handlePRINT2 Stack overflow!" << endl;
          return false;
        }
        printf("%f ", f0);
        break;
      }
  }
  return true;
}

bool handleUPRINT() {
  // cout << "handlePRINT: dataStackPointer " << dataStackPointer << " ";
  if (dataStackPointer == 0) {
    cout << "handlePRINT Stack overflow!" << endl;
    return false;
  }
  if (myRAM[BASE_ADDRESS] != 10) {
    cout << "handleUPRINT only works in base 10!" << endl;
    return false;
  }
  unsigned char x = dataStack[dataStackPointer - 1];
  switch (x) {
    case xINTEGER:
      {
        unsigned int i0;
        if (popIntegerFromStack((int *)&i0) == false) {
          cout << "handleUPRINT1 Stack overflow!" << endl;
          return false;
        }
        cout << i0 << " ";
        break;
      }
    case xFLOAT:
      {
        cout << "handleUPRINT only works with integers!" << endl;
        return false;
      }
  }
  return true;
}

bool handleOVER() {
  // cout << "handleOVER: dataStackPointer " << dataStackPointer << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  unsigned char type0 = dataStack[dataStackPointer - 1];
  unsigned char type1 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleOVER Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleOVER1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleOVER2 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i1);
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        cout << "handleOVER3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        cout << "handleOVER4 Stack overflow!" << endl;
        return false;
      }
      // cout << "2 FLOATs ";
      putFloatOnStack(f1);
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  } else {
    // one int one float
    cout << "OVER requires 2 ints or 2 floats!" << endl;
    return false;
  }
  return false;
}

bool handleDUP() {
  if (dataStackPointer == 0) {
    cout << "handleDUP Stack overflow!" << endl;
    return false;
  }
  unsigned char x = dataStack[dataStackPointer - 1];
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
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleEqual Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleEqual1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleEqual2 Stack overflow!" << endl;
        return false;
      }
      if (i0 > i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handleEqual3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handleEqual4 Stack overflow!" << endl;
        return false;
      }
      if (f0 > f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
    // one int one float
    // cout << "1 INT 1 FLOAT ";
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handleEqual5 Stack overflow!" << endl;
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      cout << "handleEqual6 Stack overflow!" << endl;
      return false;
    }
    if (i0 > i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handleLower() {
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleEqual Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleEqual1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleEqual2 Stack overflow!" << endl;
        return false;
      }
      if (i0 < i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handleEqual3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handleEqual4 Stack overflow!" << endl;
        return false;
      }
      if (f0 < f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
    // one int one float
    // cout << "1 INT 1 FLOAT ";
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handleEqual5 Stack overflow!" << endl;
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      cout << "handleEqual6 Stack overflow!" << endl;
      return false;
    }
    if (i0 < i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handleEqual() {
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleEqual Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleEqual1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleEqual2 Stack overflow!" << endl;
        return false;
      }
      if (i0 == i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handleEqual3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handleEqual4 Stack overflow!" << endl;
        return false;
      }
      if (f0 == f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
    // one int one float
    // cout << "1 INT 1 FLOAT ";
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handleEqual5 Stack overflow!" << endl;
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
      cout << "handleEqual6 Stack overflow!" << endl;
      return false;
    }
    if (i0 == i1) putIntegerOnStack(1);
    else putIntegerOnStack(0);
    return true;
  }
  return false;
}

bool handlePlus() {
  // cout << "handlePlus: dataStackPointer " << dataStackPointer << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handlePlus Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handlePlus1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handlePlus2 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0 + i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handlePlus3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handlePlus4 Stack overflow!" << endl;
        return false;
      }
      // cout << "2 FLOATs ";
      putFloatOnStack(f0 + f1);
      return true;
    }
  } else {
    // one int one float
    // cout << "1 INT 1 FLOAT ";
    int i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handlePlus5 Stack overflow!" << endl;
      return false;
    }
    if (popIntegerFromStack(&i1) == false) {
      cout << "handlePlus6 Stack overflow!" << endl;
      return false;
    }
    putFloatOnStack(f0 + i1);
    return true;
  }
  return false;
}

bool handleMinus() {
  if (dataStackPointer < 2) {
    cout << "handleMinus Stack overflow!" << endl;
    return false;
  }
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleMinus Data inconsistent!" << endl;
    return false;
  }
  dataStackPointer -= 2;
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (intCounter < 2) {
        cout << "handleMinus1 Stack overflow!" << endl;
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleMinus2 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleMinus3 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0 - i1);
      return true;
    } else {
      if (floatCounter < 2) {
        cout << "handleMinus4 Stack overflow!" << endl;
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handleMinus5 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handleMinus6 Stack overflow!" << endl;
        return false;
      }
      putFloatOnStack(f0 - f1);
      return true;
    }
  } else {
    // one int one float
    float f0;
    int i0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handlePlus5 Stack overflow!" << endl;
      return false;
    }
    if (popIntegerFromStack(&i0) == false) {
      cout << "handleMinus2 Stack overflow!" << endl;
      return false;
    }
    if (type0 == xINTEGER) putFloatOnStack(i0 - f0);
    else putFloatOnStack(f0 - i0);
    return true;
  }
  return false;
}

bool handleMult() {
  if (dataStackPointer < 2) {
    cout << "handleMult Stack overflow!" << endl;
    return false;
  }
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleMultData inconsistent!" << endl;
    return false;
  }
  dataStackPointer -= 2;
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handlePlus1 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handlePlus2 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0 * i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handlePlus3 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handlePlus4 Stack overflow!" << endl;
        return false;
      }
      // cout << "2 FLOATs ";
      putFloatOnStack(f0 * f1);
      return true;
    }
  } else {
    // one int one float
    float f0;
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      cout << "handlePlus2 Stack overflow!" << endl;
      return false;
    }
    if (popFloatFromStack(&f0) == false) {
      cout << "handlePlus4 Stack overflow!" << endl;
      return false;
    }
    putFloatOnStack(f0 * i0);
    return true;
  }
  return false;
}

bool handleDiv() {
  if (dataStackPointer < 2) {
    cout << "handleDiv Stack overflow!" << endl;
    return false;
  }
  unsigned char type1 = dataStack[dataStackPointer - 1];
  unsigned char type0 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleDiv Data inconsistent!" << endl;
    return false;
  }
  dataStackPointer -= 2;
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (intCounter < 2) {
        cout << "handleDiv1 Stack overflow!" << endl;
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleDiv2 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleDiv3 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0 - i1);
      return true;
    } else {
      if (floatCounter < 2) {
        cout << "handleDiv4 Stack overflow!" << endl;
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        cout << "handleDiv5 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        cout << "handleDiv6 Stack overflow!" << endl;
        return false;
      }
      putFloatOnStack(f0 - f1);
      return true;
    }
  } else {
    // one int one float
    float f0;
    int i0;
    if (popFloatFromStack(&f0) == false) {
      cout << "handlePlus5 Stack overflow!" << endl;
      return false;
    }
    if (popIntegerFromStack(&i0) == false) {
      cout << "handleDiv2 Stack overflow!" << endl;
      return false;
    }
    if (type0 == xINTEGER) putFloatOnStack(i0 / f0);
    else putFloatOnStack(f0 / i0);
    return true;
  }
  return false;
}

bool handleROT() {
  // cout << "handleSWAP: dataStackPointer " << dataStackPointer << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  if (dataStackPointer < 3) {
    cout << "handleROT Stack overflow!" << endl;
    return false;
  }
  unsigned char type0 = dataStack[dataStackPointer - 1];
  unsigned char type1 = dataStack[dataStackPointer - 2];
  unsigned char type2 = dataStack[dataStackPointer - 3];
  if (
    type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID || type2 == xSTRING || type2 == xINVALID) {
    cout << "handleROT Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1 && type0 == type2) {
    if (type0 == xINTEGER) {
      if (intCounter < 3) {
        cout << "handleROT1 Stack overflow!" << endl;
        return false;
      }
      int i0, i1, i2;
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleROT2 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleROT3 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i2) == false) {
        cout << "handleROT4 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i2);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1, f2;
      if (popFloatFromStack(&f0) == false) {
        cout << "handleROT6 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        cout << "handleROT7 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f2) == false) {
        cout << "handleROT8 Stack overflow!" << endl;
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
  // cout << "handleSWAP: dataStackPointer " << dataStackPointer << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  if (dataStackPointer < 2) {
    cout << "handleSWAP Stack overflow!" << endl;
    return false;
  }
  unsigned char type0 = dataStack[dataStackPointer - 1];
  unsigned char type1 = dataStack[dataStackPointer - 2];
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    cout << "handleSWAP Data inconsistent!" << endl;
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (intCounter < 2) {
        cout << "handleSWAP1 Stack overflow!" << endl;
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
        cout << "handleSWAP2 Stack overflow!" << endl;
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
        cout << "handleSWAP3 Stack overflow!" << endl;
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      if (floatCounter < 2) {
        cout << "handleSWAP4 Stack overflow!" << endl;
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
        cout << "handleSWAP5 Stack overflow!" << endl;
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
        cout << "handleSWAP6 Stack overflow!" << endl;
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
  dataStack[dataStackPointer++] = type;
  stringCounter += 1;
  return true;
}

bool putIntegerOnStack(int n) {
  enum dataType type = xINTEGER;
  userIntegers.push_back(n);
  dataStack[dataStackPointer++] = type;
  intCounter += 1;
  return true;
}

bool popIntegerFromStack(int *value) {
  if (intCounter < 1) {
    return false;
  }
  enum dataType type = xINTEGER;
  *value = userIntegers.at(intCounter - 1);
  userIntegers.pop_back();
  intCounter -= 1;
  dataStackPointer -= 1;
  return true;
}

bool popFloatFromStack(float *value) {
  if (floatCounter < 1) {
    return false;
  }
  enum dataType type = xFLOAT;
  *value = userFloats.at(floatCounter - 1);
  userFloats.pop_back();
  floatCounter -= 1;
  dataStackPointer -= 1;
  return true;
}

bool putFloatOnStack(float n) {
  enum dataType type = xFLOAT;
  userFloats.push_back(n);
  dataStack[dataStackPointer++] = type;
  floatCounter += 1;
  return true;
}

bool lookupUC(string c) {
  cout << "lookupUC " << c << " ";
  for (int ix = 0; ix < userCommands.size(); ix++) {
    cout << userCommands[ix].name << " ";
    if (c == userCommands[ix].name) {
      char code[256];
      strcpy(code, userCommands[ix].command.c_str());
      // cout << "tokenize " << userCommands[ix].command << " ";
      vector<string> chunks = tokenize(code);
      evaluate(chunks);
      return true;
    }
  }
  return false;
}

bool lookup(string c, bool *r) {
  // cout << "Analyzing " << c << " ";
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
  int base = myRAM[BASE_ADDRESS];
  // cout << "isInteger/" << base << "/" << c << " ";
  string nums("0123456789ABCDEF");
  nums = nums.substr(0, base);
  if (base == 10 && c.at(0) == '-') {
    sign = -1;
    c.erase(0, 1);
  }
  string::const_iterator it = c.begin();
  while (it != c.end() && nums.find(*it) != string::npos) ++it;
  if (c.empty() || it != c.end()) {
    // cout << c << " is not an int." << endl;
    return false;
  }
  try {
    *i0 = stoi(c, nullptr, base) * sign;
    return true;
  } catch (const std::invalid_argument &e) {
    // cout << "Invalid argument for 'abc': " << e.what() << std::endl;
  } catch (const std::out_of_range &e) {
    // cout << "Out of range for 'abc': " << e.what() << std::endl;
  }
  return false;
}

bool isFloat(string c, float *f0) {
  if (c.length() == 0) return false;
  // cout << "isFloat: " << c << "? ";
  if (myRAM[BASE_ADDRESS] == 10) {
    try {
      *f0 = stof(c);
      return true;
    } catch (const std::invalid_argument &e) {
      // cout << "Invalid argument for `" << c << "`: " << e.what() << endl;
    } catch (const std::out_of_range &e) {
      // cout << "Out of range for " << c << ": " << e.what() << endl;
    }
  } else cout << "Only works for base 10!" << endl;
  return false;
}

void evaluate(vector<string> chunks) {
  bool r;
  int i0;
  float f0;
  cout << endl
       << "Evaluating:" << endl;
  for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) cout << *it << " ";
  cout << endl;
  // for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) {
  for (executionPointer = 0; executionPointer < chunks.size(); executionPointer++) {
    // executionPointer is global so that BEGIN – and later others – can change it.
    string c = chunks.at(executionPointer);
    // string c = *it;
    // cout << endl << "evaluating '" << c << "' len " << c.length() << " ";
    if (c == ":") {
      // creation of a word
      executionPointer += 1;
      bool done = false, error = true;
      string miniChunks, dictName;
      dictName = chunks.at(executionPointer++);
      cout << "WORD name: " << dictName << ": ";
      while (executionPointer < chunks.size() && !done) {
        c = chunks.at(executionPointer);
        cout << c << " " << executionPointer << "/" << chunks.size() << " ";
        if (c == ";") {
          done = true;
          error = false;
          cout << " got a ;! ";
        } else {
          miniChunks.append(c);
          miniChunks.append(" ");
          executionPointer += 1;
        }
      }
      if (error) {
        cout << "Missing ; after : sequence! " << miniChunks << endl;
        return;
      }
      cout << "Adding word " << dictName << " with `" << miniChunks << "`." << endl;
      userCommand x = { dictName, miniChunks };
      userCommands.push_back(x);
    } else {
      if (lookup(c, &r)) {
        if (r == false) {
          cout << c << " returned false. Aborting!" << endl;
          return;
        }
      } else if (lookupUC(c)) {
        cout << c << " lookupUC " << endl;
      } else if (isInteger(c, &i0)) {
        putIntegerOnStack(i0);
        // cout << c << " is an int " << i0 << endl;
      } else if (isFloat(c, &f0)) {
        putFloatOnStack(f0);
        // cout << c << " is an int " << i0 << endl;
      } else {
        cout << endl << "ERROR! Unknown: " << c << endl;
      }
    }
  }
}

vector<string> tokenize(char *code) {
  unsigned int ln = strlen(code), ix = 0;
  vector<string> chunks;
  char buffer[256] = { 0 };
  unsigned int buffIndex = 0;
  while (ix < ln) {
    char c = code[ix++];
    if (c < '!') {
      // skip if not yet in a string
      // else add chunk
      if (buffIndex > 0) {
        buffer[buffIndex] = 0;
        chunks.push_back(buffer);
        // printf(" * Adding `%s`\n", buffer);
        memset(buffer, 0, 256);
        buffIndex = 0;
      }
    } else {
      buffer[buffIndex++] = c;
    }
  }
  if (buffIndex > 0) {
    buffer[buffIndex + 1] = 0;
    printf(" • Adding `%s`\n", buffer);
    chunks.push_back(buffer);
  }
  return chunks;
}

int main() {
  initForth();
  char code[256] = { 0 };
//   strcpy(code, "1 2 3 4 5 .S DUP ROT + + / * + 13.22 .S + . CR");
//   vector<string> chunks = tokenize(code);
//   evaluate(chunks);
// 
//   strcpy(code, "BASE 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR");
//   chunks = tokenize(code);
//   evaluate(chunks);
// 
//   cout << "OVER" << endl;
//   strcpy(code, "1 2 .S OVER .S CR 1.2 2.1 .S OVER .S CR");
//   chunks = tokenize(code);
//   evaluate(chunks);
// 
//   cout << ": ++ + + ;" << endl;
//   strcpy(code, ": ++ + + ; 1 1 1 .S ++ . CR");
//   chunks = tokenize(code);
//   evaluate(chunks);

  cout << "10 .S BEGIN DUP . 1 - DUP 0= UNTIL" << endl;
  strcpy(code, "-10 .S BEGIN DUP . 1 .S + DUP 0 = UNTIL CR");
  vector<string> chunks = tokenize(code);
  evaluate(chunks);

  cout << endl << endl;
  return 0;
}
