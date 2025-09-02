#include <fstream>  // For ifstream
#include <iostream>
#include <stdio.h>
#include <vector>
#include <string>
#include <map>
#include <cmath> // For std::sqrt

using namespace std;

#define myVERSION 1045

bool handleWORDS();
bool showStack();
bool showVars();
bool handleCR();
bool handleDEPTH();
bool handleDROP();
bool handleSWAP();
bool handleROT();
bool handleEqual();
bool handleDifferent();
bool handleLower();
bool handleGreater();
bool handleGreaterEqual();
bool handleLowerEqual();
bool handle2Nums(unsigned char);
bool handlePlus();
bool handleMinus();
bool handleMult();
bool handleDiv();
bool handleSQR();
bool handleSQRT();
bool handleFact();
bool handleEMIT();
bool handleKEY();
bool handlePRINT();
bool handlePRINTSTRING();
bool handleUPRINT();
bool handleDUP();
bool handleOVER();
bool popFromLoopStack(int *);
bool putIntegerOnStack(int);
bool popIntegerFromStack(int *);
bool putFloatOnStack(float);
bool popFloatFromStack(float *);
bool lookup(string);
bool lookupUC(string);
bool lookupVAR(string);
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
bool handleDO();
bool handleLOOP();
bool handleI();
bool handleIprime();
bool handleJ();

vector<string> tokenize(char *, vector<string>);
void evaluate(vector<string>);
void StoreINT(string, int);
void StoreFLOAT(string, float);
void StoreCONSTFLOAT(string, float);
bool checkTypes(int, unsigned char);
void logStack(char *);
void logInconsistent(char *who);
void logStackOverflow(char *who);

vector<int> dataStack;
unsigned int intCounter = 0;
unsigned int floatCounter = 0;
unsigned int stringCounter = 0;
int executionPointer = -1;
vector<int> jumpStack;
vector<int> jumpStackType;
vector<int> loopStack;
vector<string> userStrings;
vector<int> userIntegers;
vector<float> userFloats;
unsigned char myRAM[64 * 1024] = { 0 };
bool isPrinting = false;
map<string, int> varAddresses;
map<string, int> fvarAddresses;
map<string, int> constAddresses;
map<string, int> fconstAddresses;
vector<int> myVARs;
vector<float> myFVARs;
vector<int> myCONSTs;
vector<float> myFCONSTs;
vector<string> computedWords;
int xxxxxx;

enum mathTypes {
  math_PLUS,
  math_MINUS,
  math_MULT,
  math_DIV,
  math_EQUAL,
  math_GREATER,
  math_GREATEREQUAL,
  math_LOWER,
  math_LOWEREQUAL,
  math_DIFFERENT,
};
enum dataType {
  xINVALID,
  xINTEGER,
  xFLOAT,
  xSTRING,  // not used so far
};
enum JumpType {
  xBEGIN,
  xDO
};

struct nativeCommand {
  bool (*ptr)(void);  // Function pointer
  string name;
};

char msg[256];
void logThis() {
#if defined(DEBUG)
  cout << msg;
#endif
}

nativeCommand nativeCommands[] = {
  { handleWORDS, "WORDS" },
  { handlePlus, "+" },
  { handleMinus, "-" },
  { handleMult, "*" },
  { handleDiv, "/" },
  { handleFact, "FACT" },
  { handleSQR, "SQR" },
  { handleSQRT, "SQRT" },
  { handleEMIT, "EMIT" },
  { handleKEY, "KEY" },
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
  { handleLowerEqual, "<=" },
  { handleGreater, ">" },
  { handleGreaterEqual, ">=" },
  { handleDifferent, "<>" },
  { handleBEGIN, "BEGIN" },
  { handleUNTIL, "UNTIL" },
  { handleWHILE, "WHILE" },
  { handleDO, "DO" },
  { handleLOOP, "LOOP" },
  { handleI, "I" },
  { handleIprime, "I'" },
  { handleJ, "J" },
};
int nativeCmdCount = 0;

struct userCommand {
  string name;
  string command;
};
vector<userCommand> userCommands {
  {"0=", "0 ="},
  {"0>", "0 >"},
  {"0<", "0 <"},
  {"TRUE", "1 ="},
  {"FALSE", "0 ="},
  {"?", "@ ."},
  {"1+", "1 +"},
  {"1-", "1 -"},
  {"2+", "2 +"},
  {"2-", "2 -"},
  {"2*", "2 *"},
  {"2/", "2 /"},
};
int userCmdCount = 0;

char numerics[] = "0123456789abcdef";

void initForth() {
  xxxxxx = snprintf((char *)msg, 255, "init ");
  logThis();
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  StoreINT("BASE", 10);
  StoreINT("VER.", myVERSION);
  // words that are handled in code (evaluate)
  computedWords.push_back("VAR");
  computedWords.push_back("CONST");
  computedWords.push_back(": ... ;");
  userCmdCount = userCommands.size();
}

void logStack(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf(
    (char *)msg, 255,
    "%s: dataStack.size() %zu intCounter %d userIntegers.size() %zu ",
    who, dataStack.size(), intCounter, userIntegers.size());
  cout << msg;
#endif
}

void logInconsistent(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Data inconsistent!\n", who);
  cout << msg;
#endif
}

void logStackOverflow(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Stack overflow!\n", who);
  cout << msg;
#endif
}
