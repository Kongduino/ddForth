#include <cmath> // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

#define myVERSION 1089

bool handle2Nums(unsigned char);
bool handleABS();
bool handleAND();
bool handleBASE();
bool handleBASE2();
bool handleBASE10();
bool handleBASE16();
bool handleDifferent();
bool handleDiv();
bool handleEqual();
bool handleFact();
bool handleGreater();
bool handleGreaterEqual();
bool handleLower();
bool handleLowerEqual();
bool handleMAX();
bool handleMIN();
bool handleMinus();
bool handleMOD();
bool handleMult();
bool handleNOT();
bool handleOR();
bool handleSQRT();
bool handleXOR();
bool handleNEGATE();

bool handleBEGIN();
bool handleCR();
bool handleDEPTH();
bool handleDO();
bool handleDROP();
bool handleDUP();
bool handleEMIT();
bool handleEXEC();
bool handleI();
bool handleIprime();
bool handleJ();
bool handleKEY();
bool handleLINE();
bool handleLOOP();
bool handleOVER();
bool handlePlus();
bool handlePRINT();
bool handlePRINTSTACKSTRING();
bool handlePRINTSTRING();
bool handleRetrieve();
bool handleRget();
bool handleROT();
bool handleROLL();
bool handleRput();
bool handleSQR();
bool handleStore();
bool handleSWAP();
bool handleUNTIL();
bool handleUPRINT();
bool handleWHILE();
bool handleWORDS();
bool handleLOAD();
bool lookup(string);
bool lookupUC(string);
bool lookupVAR(string);
bool popFloatFromStack(float *);
bool popFromLoopStack(int *);
bool popIntegerFromJumpStack(int *);
bool popIntegerFromStack(int *);
bool popStringFromStack(string *);
bool putFloatOnStack(float);
bool putIntegerOnJumpStack(int);
bool putIntegerOnStack(int);
bool putStringOnStack(string);
bool showStack();
bool showVars();
void initForth();
void logJumpStackOverflow(char *);
void logLoopStackOverflow(char *);
void logUnknownBlock(char *);
vector<string> tokenize(char *, vector<string>);
void evaluate(vector<string>);
int GetINTaddress(string);

vector<string> tokenize(char *, vector<string>);
void evaluate(vector<string>);
void StoreINT(string, int);
void StoreFLOAT(string, float);
void StoreCONSTFLOAT(string, float);
bool checkTypes(int, unsigned char);
void logStack(char *);
void logInconsistent(char *who);
void logStackOverflow(char *who);
void logThis();

vector<int> dataStack;
int executionPointer = -1;
vector<int> jumpStack;
vector<int> jumpStackType;
vector<int> loopStack;
vector<string> userStrings;
vector<int> userIntegers;
vector<string> blocks;
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
char code[256] = { 0 };
int xxxxxx;
char msg[256];

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
  { handleABS, "ABS" },  
  { handleMIN, "MIN" },
  { handleMAX, "MAX" },
  { handleFact, "FACT" },
  { handleMOD, "MOD" },
  { handleAND, "AND" },
  { handleOR, "OR" },
  { handleXOR, "XOR" },
  { handleNOT, "NOT" },  
  { handleNEGATE, "NEGATE" },
  { handleSQR, "SQR" },
  { handleSQRT, "SQRT" },
  { handleEMIT, "EMIT" },
  { handleKEY, "KEY" },
  { handleLINE, "LINE" },
  { handlePRINT, "." },
  { handlePRINTSTRING, ".\"" },
  { handlePRINTSTACKSTRING, ".s" },
  { handleUPRINT, "U." },
  { handleDUP, "DUP" },
  { handleDROP, "DROP" },
  { handleSWAP, "SWAP" },
  { handleDEPTH, "DEPTH" },
  { handleROT, "ROT" },
  { handleROLL, "ROLL" },
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
  { handleRput, ">R" },
  { handleRget, "R>" },
  { handleEXEC, "EXEC" },
  { handleLOAD, "LOAD" },
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
  {"pi", "PI @"},
};
int userCmdCount = 0;

char numerics[] = "0123456789abcdef";

#include "Files.hpp"
#include "Numbers.hpp"

void initForth() {
  xxxxxx = snprintf((char *)msg, 255, "init ");
  logThis();
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  StoreINT("BASE", 10);
  StoreINT("VER.", myVERSION);
  StoreCONSTFLOAT("PI", 3.141592653);
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
    "%s: dataStack.size() %zu userIntegers.size() %zu ",
    who, dataStack.size(), userIntegers.size());
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

void logJumpStackOverflow(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Jump Stack overflow!\n", who);
  cout << msg;
#endif
}

void logLoopStackOverflow(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Loop Stack overflow!\n", who);
  cout << msg;
#endif
}

void logUnknownBlock(char *who) {
#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Unknown Block!\n", who);
  cout << msg;
#endif
}


