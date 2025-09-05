#include <cmath>  // For std::sqrt
#include <fcntl.h>
#include <fstream>  // For ifstream
#include <iostream>
#include <map>
#include <cstdio>
#include <string>
//#include <termios.h>
#include <unistd.h>
#include <vector>
// #include "File.hpp"
// not working

#define FORMAT_SPIFFS_IF_FAILED true

using namespace std;

#define myVERSION 1084

bool handle2Nums(unsigned char);
bool handleABS();
bool handleBASE();
bool handleBASE2();
bool handleBASE10();
bool handleBASE16();
bool handleBEGIN();
bool handleCR();
bool handleDEPTH();
bool handleDifferent();
bool handleDiv();
bool handleDO();
bool handleDROP();
bool handleDUP();
bool handleEMIT();
bool handleEqual();
bool handleEXEC();
bool handleFact();
bool handleGreater();
bool handleGreaterEqual();
bool handleI();
bool handleIprime();
bool handleJ();
bool handleKEY();
bool handleLINE();
bool handleLOAD();
bool handleSAVE();
bool handleLOOP();
bool handleLower();
bool handleLowerEqual();
bool handleMinus();
bool handleMIN();
bool handleMAX();
bool handleMOD();
bool handleMult();
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
bool handleSQRT();
bool handleStore();
bool handleSWAP();
bool handleUNTIL();
bool handleUPRINT();
bool handleWHILE();
bool handleWORDS();
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
vector<string> tokenize(char *, vector<string>);
void evaluate(vector<string>);
void writeFile(const char *, const char *);
string readFile(const char *);

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
int executionPointer = -1;
vector<int> jumpStack;
vector<int> jumpStackType;
vector<int> loopStack;
vector<string> userStrings;
vector<int> userIntegers;
vector<float> userFloats;
unsigned char myRAM[64 * 1024] = { 0 };
bool isPrinting = false;
std::map<string, int> varAddresses;
std::map<string, int> fvarAddresses;
std::map<string, int> constAddresses;
std::map<string, int> fconstAddresses;
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
  math_MOD,
  math_MIN,
  math_MAX,
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
  Serial.print(msg);
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
  { handleSAVE, "SAVE" },
};

int nativeCmdCount = 0;

struct userCommand {
  string name;
  string command;
};
vector<userCommand> userCommands{
  { "0=", "0 =" },
  { "0>", "0 >" },
  { "0<", "0 <" },
  { "TRUE", "1 =" },
  { "FALSE", "0 =" },
  { "?", "@ ." },
  { "1+", "1 +" },
  { "1-", "1 -" },
  { "2+", "2 +" },
  { "2-", "2 -" },
  { "2*", "2 *" },
  { "2/", "2 /" },
  {"pi", "PI @"},
};
int userCmdCount = 0;

char numerics[] = "0123456789abcdef";

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
