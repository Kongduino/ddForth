#include <cmath> // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "random.hpp"

using namespace std;

#define myVERSION 1098

bool getRandomBuffer();
void hexDump(unsigned char *, int);
unsigned char getRandomByte();
bool putRandomByteOnStack();
bool getRandomUInt();

#if defined(NEED_SDL)
#include "sdl_inc0.hpp"
#endif

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
bool handleSIN();
bool handleCOS();
bool handleTAN();
bool handleXOR();
bool handleNEGATE();
bool handleINVERT();
bool handleSETINT();

bool handleBEGIN();
bool handleCR();
bool handleDEPTH();
bool handleCLEAR();
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
bool handlePRINTSTRING();
bool handleSTACKSTRING();
bool handlePRINTSTACKSTRING();
bool handleAPPENDSTACKSTRING();
bool handlePREPENDSTACKSTRING();
bool handleRetrieve();
bool handleRget();
bool handleROT();
bool handleROLL();
bool handleRput();
bool handleSQR();
bool handleStore();
bool handleStorePlus();
bool handleSWAP();
bool handleUNTIL();
bool handleUPRINT();
bool handleWHILE();
bool handleWORDS();
bool handleLOAD();

bool handleLEFT();
bool handleRIGHT();
bool handleMID();
bool handleLEN();
bool handleSUBSTR();
bool handleLowercase();
bool handleUppercase();
bool handleMULTSTR();
bool handleSTRIPSTR();
bool handleLSTRIPSTR();
bool handleRSTRIPSTR();
bool handleINTSTR();
bool handleSTRINT();

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

int executionPointer = -1;
vector<int> jumpStack;
vector<int> jumpStackType;
vector<int> loopStack;
vector<int> dataStack;
vector<string> userStrings;
vector<float> userFloats;
vector<int> userIntegers;
vector<string> blocks;
unsigned char myRAM[64 * 1024] = { 0 };
bool isPrinting = false;
bool isStackingString = false;
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
  { handleINVERT, "INVERT" },
  { handleSQR, "SQR" },
  { handleSQRT, "SQRT" },
  { handleSIN, "SIN" },
  { handleCOS, "COS" },
  { handleTAN, "TAN" },
  { handleSETINT, "INT"},
  { handleEMIT, "EMIT" },
  { handleKEY, "KEY" },
  { handleLINE, "LINE" },
  { handlePRINT, "." },
  { handlePRINTSTRING, ".\"" },
  { handleSTACKSTRING, "s\"" },
  { handlePRINTSTACKSTRING, ".s" },
  { handlePREPENDSTACKSTRING, ">s" },
  { handleAPPENDSTACKSTRING, "s<" },
  { handleLEFT, "LEFTSTR" },
  { handleMID, "MIDSTR" },
  { handleRIGHT, "RIGHTSTR" },
  { handleLEN, "LENSTR" },
  { handleSUBSTR, "SUBSTR" },
  { handleLowercase, "LOWERSTR"},
  { handleUppercase, "UPPERSTR"},
  { handleMULTSTR, "MULTSTR"},
  { handleSTRIPSTR, "STRIPSTR" },
  { handleLSTRIPSTR, "LSTRIPSTR" },
  { handleRSTRIPSTR, "RSTRIPSTR" },
  { handleINTSTR, "INTSTR"},
  { handleSTRINT, "STRINT"},
  { handleUPRINT, "U." },
  { handleDUP, "DUP" },
  { handleDROP, "DROP" },
  { handleSWAP, "SWAP" },
  { handleDEPTH, "DEPTH" },
  { handleCLEAR, "CLEAR" },
  { handleROT, "ROT" },
  { handleROLL, "ROLL" },
  { handleOVER, "OVER" },
  { handleBASE, "BASE" },
  { handleBASE2, "BIN" },
  { handleBASE10, "DEC" },
  { handleBASE16, "HEX" },
  { handleStore, "!" },
  { handleStorePlus, "!+" },
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
  { putRandomByteOnStack, "RANDOM" },
  { putRandomUIntOnStack, "RANDOMI" },

#if defined(NEED_SDL)
#include "sdl_inc1.hpp"
#endif
};

int nativeCmdCount = 0;

char numerics[] = "0123456789abcdef";

#include "Files.hpp"
#include "Strings.hpp"
#include "Numbers.hpp"
#include "Stack.hpp"
#include "ExtraCommands.hpp"
#if defined(NEED_SDL)
#include "sdl_helper.hpp"
#endif

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
  getRandomBuffer();
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
//#if defined(DEBUG)
  xxxxxx = snprintf((char *)msg, 255, "%s Stack overflow!\n", who);
  cout << msg;
//#endif
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


