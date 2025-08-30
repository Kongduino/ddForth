#include <fstream> // For ifstream
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>

//#define DEBUG

using namespace std;
// vector<string> userStrings;

bool showStack();
bool handleCR();
bool handleDROP();
bool handleSWAP();
bool handleROT();
bool handleEqual();
bool handleDifferent();
bool handleLower();
bool handleHigher();
bool handle2Nums(unsigned char);
bool handlePlus();
bool handleMinus();
bool handleMult();
bool handleDiv();
bool handleFact();
bool handleEMIT();
bool handlePRINT();
bool handlePRINTSTRING();
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
bool handleWHILE();
bool handleUNTIL();
bool handleBEGIN();
vector<string> tokenize(char *);
void evaluate(vector<string>);
void StoreINT(int, int);
bool checkTypes(int, unsigned char);

vector<int> dataStack;
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
bool isPrinting = false;
enum varAddresses {
  BASE_ADDRESS,
  BASE_ADDRESS1,
  FREE_ADDRESS,  // You can peek and poke from here
};

enum mathTypes {
  math_PLUS,
  math_MINUS,
  math_MULT,
  math_DIV,
  math_EQUAL,
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
  { handleFact, "FACT" },
  { handleEMIT, "EMIT" },
  { handlePRINT, "." },
  { handlePRINTSTRING, ".\"" },
  { handleUPRINT, "U." },
  { handleDUP, "DUP" },
  { handleDROP, "DROP" },
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

void StoreINT(int addr, int value) {
  unsigned char x = value & 0xFF;
  myRAM[addr] = x;
  x = (value >> 8) & 0xFF;
  myRAM[addr + 1] = x;
}

int GetINT(int addr) {
  unsigned char x = myRAM[addr];
  unsigned char y = myRAM[addr + 1];
  int i0 = (y << 8) + x;
  return i0;
}

bool checkTypes(int levels, unsigned char n) {
  if (dataStack.size() < levels) return false;
  for (int ix = 0; ix < levels; ix++) {
    if (dataStack.at(dataStack.size() - 1 - ix) != n) return false;
  }
  return true;
}

void initForth() {
#if defined(DEBUG)
  cout << "init ";
#endif
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  userCmdCount = userCommands.size();
  StoreINT(BASE_ADDRESS, 10);
  string name("0=");
  string code("0 =");
#if defined(DEBUG)
  cout << "Adding word " << name << " with `" << code << "`" << endl;
#endif
  userCommand x = { name, code };
  userCommands.push_back(x);
}

bool handleFact() {
  int factorial = 1;
  int n;
  if (popIntegerFromStack(&n) == false) {
#if defined(DEBUG)
    cout << "handleFact Stack overflow!" << endl;
#endif
    return false;
  }
  if (n < 0) {
    std::cout << "Factorial is not defined for negative numbers." << std::endl;
    return false;
  }
  for (int i = 1; i <= n; ++i)
    factorial *= i;
  putIntegerOnStack(factorial);
  return true;
}

bool handleBEGIN() {
// BEGIN ... <condition> UNTIL
#if defined(DEBUG)
  cout << endl << "--> BEGIN at ";
#endif
  jumpStack.push_back(executionPointer);
  jumpStackType.push_back(xBEGIN);
#if defined(DEBUG)
  cout << (executionPointer) << endl;
#endif
  return true;
}

bool handleUNTIL() {
#if defined(DEBUG)
  cout << endl << "--> UNTIL at " << executionPointer << ". JumpStack size: " << jumpStack.size() << endl;
#endif
  int i0, type0;
  if (jumpStack.size() == 0) {
#if defined(DEBUG)
    cout << "handleUNTIL JumpStack overflow!" << endl;
#endif
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
#if defined(DEBUG)
    cout << "handleUNTIL JumpStackType overflow!" << endl;
#endif
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
    cout << "handleUNTIL Stack overflow!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  showStack();
#endif
  if (i0 < 0 || i0 > 1) {
#if defined(DEBUG)
    cout << "handleUNTIL " << i0 << " is not a BOOLEAN!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  cout << "Condition is " << ((i0 == 1) ? "true" : "false") << endl;
#endif
  if (i0 == 0) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
#if defined(DEBUG)
    cout << " looping back to " << executionPointer << ". Condition: " << i0 << endl;
#endif
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
#if defined(DEBUG)
    cout << " Ending BEGIN. Condition: " << i0 << endl;
#endif
  }
  return true;
}

bool handleWHILE() {
#if defined(DEBUG)
  cout << endl << "--> WHILE at " << executionPointer << ". JumpStack size: " << jumpStack.size() << endl;
#endif
  int i0, type0;
  if (jumpStack.size() == 0) {
#if defined(DEBUG)
    cout << "handleWHILE JumpStack overflow!" << endl;
#endif
    return false;
  }
  type0 = jumpStackType.at(jumpStackType.size() - 1);
  if (type0 != xBEGIN) {
#if defined(DEBUG)
    cout << "handleWHILE JumpStackType overflow!" << endl;
#endif
    return false;
  }
  if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
    cout << "handleWHILE Stack overflow!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  showStack();
#endif
  if (i0 < 0 || i0 > 1) {
#if defined(DEBUG)
    cout << "handleWHILE " << i0 << " is not a BOOLEAN!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  cout << "Condition is " << ((i0 == 1) ? "true" : "false") << endl;
#endif
  if (i0 == 1) {
    executionPointer = jumpStack.at(jumpStack.size() - 1);
#if defined(DEBUG)
    cout << " looping back to " << executionPointer << ". Condition: " << i0 << endl;
#endif
  } else {
    jumpStack.pop_back();
    jumpStackType.pop_back();
#if defined(DEBUG)
    cout << " Ending BEGIN. Condition: " << i0 << endl;
#endif
  }
  return true;
}

bool showStack() {
  int count = 0;
  if (dataStack.size() == 0) {
    cout << "Stack empty! ";
    return true;
  }
  cout << endl;  // << "showStack " << dataStack.size();
  int x = dataStack.size() - 1;
  int myInts = intCounter - 1;
  int myFloats = floatCounter - 1;
  int myStrings = stringCounter - 1;
#if defined(DEBUG)
  cout << "\tdataStack.size()\t" << (dataStack.size());
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

bool handleCR() {
  cout << endl;
  return true;
}

bool handleStore() {
#if defined(DEBUG)
  cout << "handleStore: intCounter " << intCounter << " dataStack.size() " << dataStack.size() << " ";
#endif
  if (!checkTypes(2, xINTEGER)) {
#if defined(DEBUG)
    cout << "handleStore Not enough integers!" << endl;
#endif
    return false;
  }
  int ad, x;
  if (popIntegerFromStack(&x) == false) {
#if defined(DEBUG)
    cout << "handleStore1 Stack overflow!" << endl;
#endif
    return false;
  }
  if (popIntegerFromStack(&ad) == false) {
#if defined(DEBUG)
    cout << "handleStore2 Stack overflow!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  cout << "storing " << x << " into RAM[" << ad << "] ";
#endif
  myRAM[ad] = (unsigned char)x;
  return true;
}

bool handleRetrieve() {
#if defined(DEBUG)
  cout << "handleRetrieve: dataStack.size() " << dataStack.size() << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
#endif
  if (!checkTypes(1, xINTEGER)) {
#if defined(DEBUG)
    cout << "handleRetrieve Not enough integers!" << endl;
#endif
    return false;
  }
  int ad;
  if (popIntegerFromStack(&ad) == false) {
#if defined(DEBUG)
    cout << "handleRetrieve1 Stack overflow!" << endl;
#endif
    return false;
  }
#if defined(DEBUG)
  cout << "handleRetrieve end ";
#endif
  return putIntegerOnStack(myRAM[ad]);
}

bool handleBASE() {
#if defined(DEBUG)
  cout << "handleBASE ";
#endif
  return putIntegerOnStack(BASE_ADDRESS);
}

bool handleBASE2() {
#if defined(DEBUG)
  cout << "handleBASE2 ";
#endif
  StoreINT(BASE_ADDRESS, 2);
  return true;
}

bool handleBASE10() {
#if defined(DEBUG)
  cout << "handleBASE10 ";
#endif
  StoreINT(BASE_ADDRESS, 10);
  return true;
}

bool handleBASE16() {
#if defined(DEBUG)
  cout << "handleBASE16 ";
#endif
  StoreINT(BASE_ADDRESS, 16);
  return true;
}

bool printOtherBases(int number, unsigned int base) {
  if (base > 16) {
    StoreINT(BASE_ADDRESS, 16);
    base = 16;
  }
  unsigned int uNumber = number;
#if defined(DEBUG)
  cout << " Printing " << uNumber << " in base " << base << endl;
#endif
  char buffer[32] = { 0 };
  unsigned char ix = 0;
  while (uNumber >= base) {
    int q = uNumber % base;
    uNumber = uNumber / base;
    buffer[ix++] = numerics[q];
  }
  buffer[ix] = numerics[uNumber];
#if defined(DEBUG)
  cout << numerics[uNumber] << endl;
#endif
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
#if defined(DEBUG)
    cout << "handleOVER1 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
  cout << "handlePRINT: dataStack.size() " << dataStack.size() << " ";
#endif
  if (dataStack.size() == 0) {
#if defined(DEBUG)
    cout << "handlePRINT Stack overflow!" << endl;
#endif
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        int i0;
        if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
          cout << "handlePRINT1 Stack overflow!" << endl;
#endif
          return false;
        }
        int base = GetINT(BASE_ADDRESS);
        if (base == 10) cout << i0 << " ";
        else printOtherBases(i0, base);
        break;
      }
    case xFLOAT:
      {
        float f0;
        if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
          cout << "handlePRINT2 Stack overflow!" << endl;
#endif
          return false;
        }
        printf("%f ", f0);
        break;
      }
  }
  return true;
}

bool handleUPRINT() {
  // cout << "handlePRINT: dataStack.size() " << dataStack.size() << " ";
  if (dataStack.size() == 0) {
#if defined(DEBUG)
    cout << "handlePRINT Stack overflow!" << endl;
#endif
    return false;
  }
  if (myRAM[BASE_ADDRESS] != 10) {
#if defined(DEBUG)
    cout << "handleUPRINT only works in base 10!" << endl;
#endif
    return false;
  }
  unsigned char x = dataStack.at(dataStack.size() - 1);
  switch (x) {
    case xINTEGER:
      {
        unsigned int i0;
        if (popIntegerFromStack((int *)&i0) == false) {
#if defined(DEBUG)
          cout << "handleUPRINT1 Stack overflow!" << endl;
#endif
          return false;
        }
        cout << i0 << " ";
        break;
      }
    case xFLOAT:
      {
#if defined(DEBUG)
        cout << "handleUPRINT only works with integers!" << endl;
#endif
        return false;
      }
  }
  return true;
}

bool handleOVER() {
  // cout << "handleOVER: dataStack.size() " << dataStack.size() << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
#if defined(DEBUG)
    cout << "handleOVER Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleOVER1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleOVER2 Stack overflow!" << endl;
#endif
        return false;
      }
      putIntegerOnStack(i1);
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleOVER3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleOVER4 Stack overflow!" << endl;
#endif
        return false;
      }
#if defined(DEBUG)
      cout << "2 FLOATs ";
#endif
      putFloatOnStack(f1);
      putFloatOnStack(f0);
      putFloatOnStack(f1);
      return true;
    }
  } else {
// one int one float
#if defined(DEBUG)
    cout << "OVER requires 2 ints or 2 floats!" << endl;
#endif
    return false;
  }
  return false;
}

bool handleDROP() {
  if (dataStack.size() == 0) {
#if defined(DEBUG)
    cout << "handleDROP Stack overflow!" << endl;
#endif
    return false;
  }
  int i0;
  if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
    cout << "handleDROP1 Stack overflow!" << endl;
#endif
    return false;
  }
  return true;
}

bool handleDUP() {
  if (dataStack.size() == 0) {
#if defined(DEBUG)
    cout << "handleDUP Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
    cout << "handleHigher Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      // cout << "2 INTs ";
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleHigher1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleHigher2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (i0 > i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleHigher3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleHigher4 Stack overflow!" << endl;
#endif
        return false;
      }
      if (f0 > f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
#if defined(DEBUG)
    cout << "1 INT 1 FLOAT ";
#endif
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
      cout << "handleHigher5 Stack overflow!" << endl;
#endif
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
      cout << "handleHigher6 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
    cout << "handleLower Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
#if defined(DEBUG)
      cout << "2 INTs ";
#endif
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleLower1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleLower2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (i0 < i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleLower3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleLower4 Stack overflow!" << endl;
#endif
        return false;
      }
      if (f0 < f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
#if defined(DEBUG)
    cout << "1 INT 1 FLOAT ";
#endif
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
      cout << "handleLower5 Stack overflow!" << endl;
#endif
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
      cout << "handleLower6 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
    cout << "handleEqual Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
#if defined(DEBUG)
      cout << "2 INTs ";
#endif
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleEqual1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleEqual2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (i0 == i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleEqual3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleEqual4 Stack overflow!" << endl;
#endif
        return false;
      }
      if (f0 == f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
#if defined(DEBUG)
    cout << "1 INT 1 FLOAT ";
#endif
    int i0, i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
      cout << "handleEqual5 Stack overflow!" << endl;
#endif
      return false;
    }
    i1 = (int)f0;
    if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
      cout << "handleEqual6 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
    cout << "handleDifferent Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
#if defined(DEBUG)
      cout << "2 INTs ";
#endif
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleDifferent1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleDifferent2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (i0 != i1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleDifferent3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleDifferent4 Stack overflow!" << endl;
#endif
        return false;
      }
      if (f0 != f1) putIntegerOnStack(1);
      else putIntegerOnStack(0);
      return true;
    }
  } else {
// one int one float
#if defined(DEBUG)
    cout << "1 INT 1 FLOAT ";
#endif
    int i0;
    float f0, f1;
    if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
      cout << "handleDifferent5 Stack overflow!" << endl;
#endif
      return false;
    }
    if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
      cout << "handleDifferent6 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
    cout << "handle2Nums Data inconsistent! " << (int)type0 << endl;
#endif
    showStack();
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
#if defined(DEBUG)
      cout << "2 INTs ";
#endif
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handle2Nums1 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handle2Nums2 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
        cout << "handle2Nums3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handle2Nums4 Stack overflow!" << endl;
#endif
        return false;
      }
#if defined(DEBUG)
      cout << "2 FLOATs ";
#endif
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
#if defined(DEBUG)
    cout << "1 INT 1 FLOAT ";
#endif
    int i1;
    float f0;
    if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
      cout << "handle2Nums5 Stack overflow!" << endl;
#endif
      return false;
    }
    if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
      cout << "handle2Nums6 Stack overflow!" << endl;
#endif
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

bool handleROT() {
#if defined(DEBUG)
  cout << "handleSWAP: dataStack.size() " << dataStack.size() << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
#endif
  if (dataStack.size() < 3) {
#if defined(DEBUG)
    cout << "handleROT Stack overflow!" << endl;
#endif
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  unsigned char type2 = dataStack.at(dataStack.size() - 3);
  if (
    type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID || type2 == xSTRING || type2 == xINVALID) {
#if defined(DEBUG)
    cout << "handleROT Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1 && type0 == type2) {
    if (type0 == xINTEGER) {
      if (intCounter < 3) {
#if defined(DEBUG)
        cout << "handleROT1 Stack overflow!" << endl;
#endif
        return false;
      }
      int i0, i1, i2;
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleROT2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleROT3 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i2) == false) {
#if defined(DEBUG)
        cout << "handleROT4 Stack overflow!" << endl;
#endif
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i2);
      putIntegerOnStack(i1);
      return true;
    } else {
      float f0, f1, f2;
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleROT6 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleROT7 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f2) == false) {
#if defined(DEBUG)
        cout << "handleROT8 Stack overflow!" << endl;
#endif
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
#if defined(DEBUG)
  cout << "handleSWAP: dataStack.size() " << dataStack.size() << " intCounter " << intCounter << " userIntegers.size() " << userIntegers.size() << " ";
#endif
  if (dataStack.size() < 2) {
#if defined(DEBUG)
    cout << "handleSWAP Stack overflow!" << endl;
#endif
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  unsigned char type1 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
#if defined(DEBUG)
    cout << "handleSWAP Data inconsistent!" << endl;
#endif
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      if (intCounter < 2) {
#if defined(DEBUG)
        cout << "handleSWAP1 Stack overflow!" << endl;
#endif
        return false;
      }
      int i0, i1;
      if (popIntegerFromStack(&i0) == false) {
#if defined(DEBUG)
        cout << "handleSWAP2 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popIntegerFromStack(&i1) == false) {
#if defined(DEBUG)
        cout << "handleSWAP3 Stack overflow!" << endl;
#endif
        return false;
      }
      putIntegerOnStack(i0);
      putIntegerOnStack(i1);
      return true;
    } else {
      if (floatCounter < 2) {
#if defined(DEBUG)
        cout << "handleSWAP4 Stack overflow!" << endl;
#endif
        return false;
      }
      float f0, f1;
      if (popFloatFromStack(&f0) == false) {
#if defined(DEBUG)
        cout << "handleSWAP5 Stack overflow!" << endl;
#endif
        return false;
      }
      if (popFloatFromStack(&f1) == false) {
#if defined(DEBUG)
        cout << "handleSWAP6 Stack overflow!" << endl;
#endif
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
  if (intCounter < 1) {
    return false;
  }
  enum dataType type = xINTEGER;
  *value = userIntegers.at(intCounter - 1);
  userIntegers.pop_back();
  dataStack.pop_back();
  intCounter -= 1;
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

bool lookupUC(string c) {
#if defined(DEBUG)
  cout << "lookupUC " << c << " ";
#endif
  for (int ix = 0; ix < userCommands.size(); ix++) {
#if defined(DEBUG)
    cout << userCommands[ix].name << " ";
#endif
    if (c == userCommands[ix].name) {
      char code[256];
      strcpy(code, userCommands[ix].command.c_str());
#if defined(DEBUG)
      cout << "tokenize " << userCommands[ix].command << " ";
#endif
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
  // #if defined(DEBUG)
  //   cout << "Analyzing " << c << " ";
  // #endif
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
  int base = GetINT(BASE_ADDRESS);
#if defined(DEBUG)
  cout << "isInteger/" << base << "/" << c << " ";
#endif
  string nums("0123456789ABCDEF");
  nums = nums.substr(0, base);
  if (base == 10 && c.at(0) == '-') {
    sign = -1;
    c.erase(0, 1);
  }
  string::const_iterator it = c.begin();
  while (it != c.end() && nums.find(*it) != string::npos) ++it;
  if (c.empty() || it != c.end()) {
#if defined(DEBUG)
    cout << c << " is not an int." << endl;
#endif
    return false;
  }
  try {
    *i0 = stoi(c, nullptr, base) * sign;
    return true;
  } catch (const std::invalid_argument &e) {
#if defined(DEBUG)
    cout << "Invalid argument for 'abc': " << e.what() << std::endl;
#endif
  } catch (const std::out_of_range &e) {
#if defined(DEBUG)
    cout << "Out of range for 'abc': " << e.what() << std::endl;
#endif
  }
  return false;
}

bool isFloat(string c, float *f0) {
  if (c.length() == 0) return false;
#if defined(DEBUG)
  cout << "isFloat: " << c << "? ";
#endif
  if (myRAM[BASE_ADDRESS] == 10) {
    try {
      *f0 = stof(c);
      return true;
    } catch (const std::invalid_argument &e) {
#if defined(DEBUG)
      cout << "Invalid argument for `" << c << "`: " << e.what() << endl;
#endif
    } catch (const std::out_of_range &e) {
#if defined(DEBUG)
      cout << "Out of range for " << c << ": " << e.what() << endl;
#endif
    }
  } else {
#if defined(DEBUG)
    cout << "Only works for base 10!" << endl;
#endif
  }
  return false;
}

void evaluate(vector<string> chunks) {
  bool r;
  int i0;
  float f0;
#if defined(DEBUG)
  cout << endl << "Evaluating:" << endl;
  for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) cout << *it << " ";
  cout << endl;
  showStack();
#endif
  // for (auto it = chunks.cbegin(); it != chunks.cend(); ++it) {
  executionPointer = 0;
  while (executionPointer < chunks.size()) {
    // executionPointer is global so that BEGIN – and later others – can change it.
    string c = chunks.at(executionPointer);
#if defined(DEBUG)
    cout << endl << "evaluating '" << c << "' executionPointer: " << executionPointer << endl;
    for (int xx = 0; xx < chunks.size(); xx++) {
      cout << xx;
      if (xx == executionPointer) cout << "*";
      else cout << " ";
      cout << "\t| " << chunks.at(xx) << "\t|" << endl;
    }
#endif
    if (isPrinting && c.back() == '"') {
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
#if defined(DEBUG)
      cout << "WORD name: " << dictName << ": ";
#endif
      while (executionPointer < chunks.size() && !done) {
        c = chunks.at(executionPointer);
#if defined(DEBUG)
        cout << c << " " << executionPointer << "/" << chunks.size() << " ";
#endif
        if (c == ";") {
          done = true;
          error = false;
#if defined(DEBUG)
          cout << " got a ;! ";
#endif
        } else {
          miniChunks.append(c);
          miniChunks.append(" ");
          executionPointer += 1;
        }
      }
      if (error) {
#if defined(DEBUG)
        cout << "Missing ; after : sequence! " << miniChunks << endl;
#endif
        return;
      }
#if defined(DEBUG)
      cout << "Adding word " << dictName << " with `" << miniChunks << "`." << endl;
#endif
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
#if defined(DEBUG)
        cout << c << " lookupUC " << endl;
#endif
        executionPointer += 1;
      } else if (isInteger(c, &i0)) {
        putIntegerOnStack(i0);
        executionPointer += 1;
#if defined(DEBUG)
        cout << c << " is an int " << i0 << endl;
#endif
      } else if (isFloat(c, &f0)) {
        putFloatOnStack(f0);
        executionPointer += 1;
#if defined(DEBUG)
        cout << c << " is an int " << i0 << endl;
#endif
      } else {
        cout << endl << "ERROR! Unknown: " << c << " at executionPointer " << executionPointer << endl;
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
#if defined(DEBUG)
          cout << "inside string" << endl;
#endif
        }
#if defined(DEBUG)
        printf(" * Adding `%s`\n", buffer);
#endif
        memset(buffer, 0, 256);
        buffIndex = 0;
      }
    } else if (c == '\\' && insideString) {
      buffer[buffIndex++] = code[ix++];
    } else if (c == '"' && insideString /* && code[ix + 1] < '!'*/) {
#if defined(DEBUG)
      cout << "Ending \"" << endl;
#endif
      insideString = false;
      buffer[buffIndex++] = c;
      buffer[buffIndex] = 0;
      string ss(buffer);
      //ss.append("\"");
      ix += 1;
#if defined(DEBUG)
      cout << "ss: " << ss << endl;
#endif
      chunks.push_back(ss);
      memset(buffer, 0, 256);
      buffIndex = 0;
    } else {
#if defined(DEBUG)
      cout << c;
#endif
      buffer[buffIndex++] = c;
    }
  }
  if (buffIndex > 0) {
    buffer[buffIndex + 1] = 0;
#if defined(DEBUG)
    printf(" • Adding `%s`\n", buffer);
#endif
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
        std::cerr << "Unable to open file!" << std::endl;
        return 0;
      }
      string line;
      getline(inputFile, line);
      strcpy(code, line.c_str());
    } else {
      std::cerr << argv[1] << "!= -f" << std::endl;
      return 0;
    }
  } else if(argc == 2) {
    strcpy(code, argv[1]);
  } else {
    strcpy(code, "-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR");
  }
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
