#include <cmath>  // For std::sqrt
#include <fcntl.h>
#include <iostream>
#include <map>
#include <cstdio>
#include <cstring>
#include <string>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include <algorithm>  // std::transform
#include "random.hpp"

using namespace std;

#include "myversion.hpp"

bool getRandomBuffer();
void hexDump(unsigned char *, int);
unsigned char getRandomByte();
bool putRandomByteOnStack();
bool getRandomUInt();

#if defined(NEED_SDL)
#include "sdl_helpers/sdl_inc0.hpp"
#endif

bool handleHELP();

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
bool handleEqualQ();
bool handleGreaterQ();
bool handleLowerQ();
bool handleGreaterEqualQ();
bool handleLowerEqualQ();
bool handleDifferentQ();
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
bool handleASIN();
bool handleACOS();
bool handleATAN();
bool handleSINH();
bool handleCOSH();
bool handleTANH();
bool handleLOG();
bool handleLOG10();
bool handleROUND();
bool handleFLOOR();
bool handleCEIL();
bool handleEXP();
bool handleXOR();
bool handleNEGATE();
bool handleINVERT();
bool handleSETINT();

bool handleBEGIN();
bool handleCR();
bool handleDEPTH();
bool handleCLEAR();
bool handleDO();
bool handlePlusLoop();
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
bool handleFLOAD();
bool handleParens();
bool handleCELLS();
bool handleARRAYLIST();
bool handleCELLSTORE();
bool handleCELLRETRIEVE();
bool handleCELLLENGTH();
bool handleCELLAPPEND();
bool handleCELLPREPEND();
bool handleCELLLIST();
bool handleCELLLROT();
bool handleCELLRROT();
bool handleARRAYSUM();

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
bool handleCSPLIT();
bool handleSPLITDELIM();
bool handleVARRAY();

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
bool handleEXIT();

bool handleIF();
bool handleTHEN();
bool handleELSE();

vector<string> tokenize(char *, vector<string>);
void evaluate(vector<string>);
void StoreINT(string, int);
void StoreFLOAT(string, float);
void StoreSTRING(string, string);
void StoreCONSTFLOAT(string, float);
void StoreCONSTSTR(string, string);
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
std::map<string, int> varAddresses;
std::map<string, int> fvarAddresses;
std::map<string, int> strvarAddresses;
std::map<string, int> constAddresses;
std::map<string, int> fconstAddresses;
std::map<string, int> strconstAddresses;
std::map<string, vector<int>> myIntArrays;
std::map<string, vector<float>> myFloatArrays;
std::map<string, vector<string>> myStringArrays;
vector<int> myVARs;
vector<float> myFVARs;
vector<int> myCONSTs;
vector<float> myFCONSTs;
vector<string> mySTRVARs;
vector<string> mySTRCONSTs;
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
  string help;
};

void logThis() {
#if defined(DEBUG)
  cout << msg;
#endif
}

nativeCommand nativeCommands[] = {
  { handleWORDS, "WORDS", "( -- Displays vocabulary )" },
  { handleHELP, "HELP", "( -- Displays this help )" },
  { handlePlus, "+", "( a b -- x ) Puts a+b on top of the stack" },
  { handleMinus, "-", "( a b -- x ) Puts a-b on top of the stack" },
  { handleMult, "*", "( a b -- x ) Puts a*b on top of the stack" },
  { handleDiv, "/", "( a b -- x ) Puts a/b on top of the stack" },
  { handleABS, "ABS", "( a -- x ) Puts absolute value of A on top of the stack" },
  { handleMIN, "MIN", "( a b -- x ) Puts min(a,b) on top of the stack" },
  { handleMAX, "MAX", "( a b -- x ) Puts max(a,b) on top of the stack" },
  { handleFact, "FACT", "( a -- x ) Puts a! on top of the stack" },
  { handleMOD, "MOD", "( a b -- x ) Puts a%b on top of the stack" },
  { handleAND, "AND", "( a b -- x ) Puts a&b on top of the stack" },
  { handleOR, "OR", "( a b -- x ) Puts a|b on top of the stack" },
  { handleXOR, "XOR", "( a b -- x ) Puts a^b on top of the stack" },
  { handleNOT, "NOT", "( a -- x ) Puts (1 - (a&1)) on top of the stack" },
  { handleNEGATE, "NEGATE", "( a -- x ) Puts ((~a) + 1) on top of the stack" },
  { handleINVERT, "INVERT", "( a -- x ) Puts ~a on top of the stack" },
  { handleSQR, "SQR", "( a -- x ) Puts (a*a) on top of the stack" },
  { handleSQRT, "SQRT", "( a -- x ) Puts √a on top of the stack" },
  { handleSIN, "SIN", "( a -- x ) Puts sin(a) on top of the stack" },
  { handleCOS, "COS", "( a -- x ) Puts cos(a) on top of the stack" },
  { handleTAN, "TAN", "( a -- x ) Puts tan(a) on top of the stack" },
  { handleASIN, "ASIN", "( a -- x ) Puts asin(a) on top of the stack" },
  { handleACOS, "ACOS", "( a -- x ) Puts acos(a) on top of the stack" },
  { handleATAN, "ATAN", "( a -- x ) Puts atan(a) on top of the stack" },
  { handleSINH, "SINH", "( a -- x ) Puts sinch(a) on top of the stack" },
  { handleCOSH, "COSH", "( a -- x ) Puts cosch(a) on top of the stack" },
  { handleTANH, "TANH", "( a -- x ) Puts tanch(a) on top of the stack" },
  { handleLOG, "LOG", "( a -- x ) Puts log(a) on top of the stack" },
  { handleLOG10, "LOG10", "( a -- x ) Puts log10(a) on top of the stack" },
  { handleROUND, "ROUND", "( a -- x ) Puts round(a) on top of the stack" },
  { handleFLOOR, "FLOOR", "( a -- x ) Puts floor(a) on top of the stack" },
  { handleCEIL, "CEIL", "( a -- x ) Puts ceil(a) on top of the stack" },
  { handleEXP, "EXP", "( a -- x ) Computes e raised to power a" },
  { handleSETINT, "INT", "( a -- x ) Converts a to an integer" },
  { handleEMIT, "EMIT", "( a -- ) printf(\"%c\", a);" },
  { handleKEY, "KEY", "( -- x) Waits for a key and puts it on the stack" },
  { handleLINE, "LINE", "( -- x ) Waits for a line, and puts it on the stack" },
  { handlePRINT, ".", "( -- ) Prints a numerical value" },
  { handlePRINTSTRING, ".\"", "( -- ) Print a string following that command. .\" print this.\"" },
  { handleSTACKSTRING, "s\"", "( -- ) Puts a string following that command on the stack. s\" stack this.\"" },
  { handlePRINTSTACKSTRING, ".s", "--" },
  { handlePREPENDSTACKSTRING, "+STR", "--" },
  { handleAPPENDSTACKSTRING, "STR+", "--" },
  { handleLEFT, "LEFTSTR", "--" },
  { handleMID, "MIDSTR", "--" },
  { handleRIGHT, "RIGHTSTR", "--" },
  { handleLEN, "LENSTR", "--" },
  { handleSUBSTR, "SUBSTR", "--" },
  { handleLowercase, "LOWERSTR", "--" },
  { handleUppercase, "UPPERSTR", "--" },
  { handleMULTSTR, "MULTSTR", "--" },
  { handleSTRIPSTR, "STRIPSTR", "--" },
  { handleLSTRIPSTR, "LSTRIPSTR", "--" },
  { handleRSTRIPSTR, "RSTRIPSTR", "--" },
  { handleINTSTR, "INTSTR", "--" },
  { handleSTRINT, "STRINT", "--" },
  { handleCSPLIT, "CSPLIT", "--" },
  { handleSPLITDELIM, "SPLITD", "--" },
  { handleVARRAY, "VARRAY", "--" },

  { handleUPRINT, "U.", "--" },
  { handleDUP, "DUP", "--" },
  { handleDROP, "DROP", "--" },
  { handleSWAP, "SWAP", "--" },
  { handleDEPTH, "DEPTH", "--" },
  { handleCLEAR, "CLEAR", "--" },
  { handleROT, "ROT", "--" },
  { handleROLL, "ROLL", "--" },
  { handleOVER, "OVER", "--" },
  { handleBASE, "BASE", "--" },
  { handleBASE2, "BIN", "--" },
  { handleBASE10, "DEC", "--" },
  { handleBASE16, "HEX", "--" },
  { handleStore, "!", "--" },
  { handleStorePlus, "!+", "--" },
  { handleRetrieve, "@", "--" },
  { handleCR, "CR", "--" },
  { showStack, ".S" },
  { showVars, ".V" },
  { handleEqual, "=", "--" },
  { handleLower, "<", "--" },
  { handleLowerEqual, "<=", "--" },
  { handleGreater, ">", "--" },
  { handleGreaterEqual, ">=", "--" },
  { handleDifferent, "<>", "--" },
  { handleEqualQ, "=?", "--" },
  { handleGreaterQ, ">?", "--" },
  { handleLowerQ, "<?", "--" },
  { handleLowerEqualQ, "<=?", "--" },
  { handleGreaterEqualQ, ">=?", "--" },
  { handleDifferentQ, "<>?", "--" },
  { handleBEGIN, "BEGIN", "--" },
  { handleUNTIL, "UNTIL", "--" },
  { handleWHILE, "WHILE", "--" },
  { handleDO, "DO", "--" },
  { handlePlusLoop, "+LOOP", "--" },
  { handleLOOP, "LOOP", "--" },
  { handleI, "I", "--" },
  { handleIprime, "I'", "--" },
  { handleJ, "J", "--" },
  { handleRput, ">R", "--" },
  { handleRget, "R>", "--" },
  { handleEXEC, "EXEC", "--" },
  { handleLOAD, "LOAD", "--" },
  { handleFLOAD, "FLOAD", "--" },
  { putRandomByteOnStack, "RANDOM" },
  { putRandomUIntOnStack, "RANDOMI" },
  { handleIF, "IF", "--" },
  { handleTHEN, "THEN", "--" },
  { handleELSE, "ELSE", "--" },
  { handleEXIT, "EXIT", "--" },
  { handleParens, "(", "--" },
  { handleCELLS, "ARRAY", "--" },
  { handleARRAYLIST, "ARRAYS", "--" },
  { handleCELLSTORE, ">IX", "--" },
  { handleCELLRETRIEVE, "IX>", "--" },
  { handleCELLLENGTH, "LEN>", "--" },
  { handleCELLAPPEND, "IX+", "--" },
  { handleCELLPREPEND, "+IX", "--" },
  { handleCELLLROT, "<ROT", "--" },
  { handleCELLRROT, "ROT>", "--" },
  { handleCELLLIST, "ALIST", "--" },
  { handleARRAYSUM, "ASUM", "--" },

#include "lowercase.hpp"

#if defined(NEED_SDL)
#include "sdl_helpers/sdl_inc1.hpp"
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
#include "sdl_helpers/sdl_helper.hpp"
#endif

void initForth() {
  xxxxxx = snprintf((char *)msg, 255, "init ");
  logThis();
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  StoreINT("BASE", 10);
  StoreINT("VER.", myVERSION);
  StoreCONSTFLOAT("PI", 3.141592653f);
  StoreCONSTFLOAT("E", 2.718281828459045f);
  // words that are handled in code (evaluate)
  computedWords.push_back("VAR");
  computedWords.push_back("CONST");
  computedWords.push_back(": ... ;");
  computedWords.push_back("IF...THEN...ELSE");
  computedWords.push_back("( THIS IS A COMMENT. )");
  userCmdCount = userCommands.size();
  getRandomBuffer();
  int v0, v1, v2;
  float f0;
  v0 = (myVERSION / 1000);
  v1 = ((myVERSION - (v0 * 1000))) / 100;
  v2 = (myVERSION / 100) * 100;
  f0 = (myVERSION - v2);
  v2 = f0;
  printf("ddForth v%d.%d.%d\n", v0, v1, v2);
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

bool handleWORDS() {
  cout << "Handled in Code:" << endl << "----------------" << endl;
  for (vector<string>::iterator it = computedWords.begin(); it != computedWords.end(); ++it) {
    string s = *it;
    printf(" • %-11s (Handled in code)\n", s.c_str());
  }
  cout << endl << "Native Commands:" << endl << "----------------" << endl;
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    // printf(" • %-11s (Native command)\n", nativeCommands[ix].name.c_str());
    cout << nativeCommands[ix].name << " ";
  }
  cout << endl << endl << "User Commands:" << endl << "--------------" << endl;
  for (vector<userCommand>::iterator it = userCommands.begin(); it != userCommands.end(); ++it) {
    printf(" • %-11s %s\n", it->name.c_str(), it->command.c_str());
  }
  return true;
}

bool handleHELP() {
  for (int ix = 0; ix < nativeCmdCount; ix++) {
    // printf(" • %-11s (Native command)\n", nativeCommands[ix].name.c_str());
    cout << nativeCommands[ix].name << endl;
    cout << "\t* " << nativeCommands[ix].help << endl;
  }
  return true;
}
