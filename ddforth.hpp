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
#include <algorithm> // std::transform
#include "random.hpp"
#include <iterator> // Required for std::distance

using namespace std;

#include "myversion.hpp"

bool getRandomBuffer();
void hexDump(unsigned char *, int);
bool handleHexDump();
unsigned char getRandomByte();
bool putRandomByteOnStack();
bool getRandomUInt();

#if defined(NEED_SDL)
#include "sdl_helpers/sdl_inc0.hpp"
#endif

bool handleHELP();
bool handleHELPSTRING();

bool handleSuppArgs();
bool handle2Nums(unsigned char);
bool handleABS();
bool handleAND();
bool handleBASE();
bool handleBASE2();
bool handleBASE10();
bool handleBASE16();
bool handleDifferent();
bool handleDiv();
bool handleWITHIN();
bool handleEqual();
bool handleStringEqual();
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
bool handleASC2CHR();
bool handleEXEC();
bool handleI();
bool handleIprime();
bool handleJ();
bool handleKEY();
bool handleQuietKEY();
bool handleLINE();
bool handleLOOP();
bool handleOVER();
bool handleSPICK();
bool handleSSTORE();
bool handlePICK();
bool handlePLACE();
bool handleSJOIN();
bool handleSlicer();
bool handleHEX2NUM();

bool handlePlus();
bool handlePRINT();
bool handlePRINTSTRING();
bool handleSTACKSTRING();
bool handlePRINTSTACKSTRING();
bool handleAPPENDSTACKSTRING();
bool handlePREPENDSTACKSTRING();
bool handleRetrieve();
bool handleRget();
// bool handleROT();
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
bool handleFLOAD();
bool handleFSAVE();

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
bool handleFLOATSTR();
bool handleSTRINT();
bool handleSTRFLOAT();
bool handleCSPLIT();
bool handleSPLITDELIM();
bool handleStringReverse();
bool handleDINSERT();
bool handleStringReplace();
bool handleSFILL();
bool handleCFILL();

bool handleVARRAY();
bool handleSortVARRAY();
bool handleSortReverseVARRAY();
bool handleFindVARRAY();

bool lookup(string);
bool lookupUC(string);
bool lookupVAR(string);
bool forgetVAR();
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
bool handleGotoXY();
bool handleClearTerminal();

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

bool read_byte(char&);
string readUntil(char);
bool handleFIONREAD();
bool handleOpenPort();
bool handleReadLinePort();
bool handleReadHEXLinePort();
bool handleReadRawPort();
bool handleReadRawHexPort();
bool handleReadUntilPort();
bool handleReadHEXUntilPort();
bool handleReadDiscardPort();
bool handleClosePort();
bool handleFlushPort();
bool handleReadCharPort();
bool handleWritePort();

bool handleSleep();
bool handleDelay();

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
int firstUserINT = 2;
int firstUserFLOAT = 2;
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
  xSTRING, // not used so far
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
  { handleWORDS, "WORDS", "( --  Displays vocabulary." },
  { handleHELP, "HELP", "( -- ) Displays this help." },
  { handleSuppArgs, "SUPP_ARGS", "( -- a b c d... n) Puts the supplementary arguments, if any, on the stack and the count on top." },
  { handleHexDump, "HEXDUMP", "( s -- Displays as string in hexadecimal as a table. )" },
  { handleHELPSTRING, "HELP\"", "( -- ) Print help for the word following, formatted as a string." },
  { handlePlus, "+", "( a b -- x ) Puts a+b on top of the stack." },
  { handleMinus, "-", "( a b -- x ) Puts a-b on top of the stack." },
  { handleMult, "*", "( a b -- x ) Puts a*b on top of the stack." },
  { handleDiv, "/", "( a b -- x ) Puts a/b on top of the stack." },
  { handleABS, "ABS", "( a -- x ) Puts absolute value of A on top of the stack." },
  { handleMIN, "MIN", "( a b -- x ) Puts min(a,b) on top of the stack." },
  { handleMAX, "MAX", "( a b -- x ) Puts max(a,b) on top of the stack." },
  { handleFact, "FACT", "( a -- x ) Puts a! on top of the stack." },
  { handleMOD, "MOD", "( a b -- x ) Puts a%b on top of the stack." },
  { handleAND, "AND", "( a b -- x ) Puts a&b on top of the stack." },
  { handleOR, "OR", "( a b -- x ) Puts a|b on top of the stack." },
  { handleXOR, "XOR", "( a b -- x ) Puts a^b on top of the stack." },
  { handleNOT, "NOT", "( a -- x ) Puts (1 - (a&1)) on top of the stack." },
  { handleNEGATE, "NEGATE", "( a -- x ) Puts ((~a) + 1) on top of the stack." },
  { handleINVERT, "INVERT", "( a -- x ) Puts ~a on top of the stack." },
  { handleSQR, "SQR", "( a -- x ) Puts (a*a) on top of the stack." },
  { handleSQRT, "SQRT", "( a -- x ) Puts √a on top of the stack." },
  { handleSIN, "SIN", "( a -- x ) Puts sin(a) on top of the stack." },
  { handleCOS, "COS", "( a -- x ) Puts cos(a) on top of the stack." },
  { handleTAN, "TAN", "( a -- x ) Puts tan(a) on top of the stack." },
  { handleASIN, "ASIN", "( a -- x ) Puts asin(a) on top of the stack." },
  { handleACOS, "ACOS", "( a -- x ) Puts acos(a) on top of the stack." },
  { handleATAN, "ATAN", "( a -- x ) Puts atan(a) on top of the stack." },
  { handleSINH, "SINH", "( a -- x ) Puts sinch(a) on top of the stack." },
  { handleCOSH, "COSH", "( a -- x ) Puts cosch(a) on top of the stack." },
  { handleTANH, "TANH", "( a -- x ) Puts tanch(a) on top of the stack." },
  { handleLOG, "LOG", "( a -- x ) Puts log(a) on top of the stack." },
  { handleLOG10, "LOG10", "( a -- x ) Puts log10(a) on top of the stack." },
  { handleROUND, "ROUND", "( a -- x ) Puts round(a) on top of the stack." },
  { handleFLOOR, "FLOOR", "( a -- x ) Puts floor(a) on top of the stack." },
  { handleCEIL, "CEIL", "( a -- x ) Puts ceil(a) on top of the stack." },
  { handleEXP, "EXP", "( a -- x ) Computes e raised to power a" },
  { handleSETINT, "INT", "( a -- x ) Converts a to an integer" },
  { handleEMIT, "EMIT", "( a -- ) printf(\"%c\", a);" },
  { handleASC2CHR, "CHR", "( a -- s ) Converts an ASCII code to a string and puts it on the stack." },
  { handleKEY, "KEY", "( -- x) Waits for a key, prints it on screen, and puts it on the stack." },
  { handleQuietKEY, "QKEY", "( -- x) Waits for a key and puts it on the stack." },
  { handleLINE, "LINE", "( -- x ) Waits for a line, and puts it on the stack." },
  { handleUPRINT, "U.", "( a -- ) Prints a numerical value as a UINT" },
  { handlePRINTSTRING, ".\"", "( -- ) Print a string following that command. .\" print this.\"" },
  { handleSTACKSTRING, "S\"", "( -- ) Puts a string following that command on the stack. s\" stack this.\"" },
  { handleSTACKSTRING, "C\"", "( -- ) Puts a string following that command on the stack. Forth 2012" },
  { handlePRINT, ".", "( a -- ) Prints a numerical value" },
  { handlePRINTSTACKSTRING, "CS", "( a -- ) Print the string on top of the stack." },
  { handlePREPENDSTACKSTRING, "+STR", "( a b -- ba ) Prepends string b to string a. AA BB +STR ===> BBAA" },
  { handleAPPENDSTACKSTRING, "STR+", "( a b -- ab ) Appends string b to string a. AA BB STR+ ===> AABB" },
  { handleLEFT, "LEFTSTR", "( a -- a x ) Puts the leftmost char of string a on top of the stack." },
  { handleMID, "MIDSTR", "( a b -- a x ) Puts the bth char of string a on top of the stack." },
  { handleRIGHT, "RIGHTSTR", "( a -- a x ) Puts the rightmost char of the string on top of the stack." },
  { handleLEN, "LENSTR", "( a -- a x ) Puts length of string a on top of the stack." },
  { handleSUBSTR, "SUBSTR", "( s a b -- s x ) Puts substring(a, b) of string s on top of the stack." },
  { handleLowercase, "LOWERSTR", "( A -- a ) replaces string A with its lowercase version" },
  { handleUppercase, "UPPERSTR", "( a -- A ) replaces string a with its uppercase version" },
  { handleMULTSTR, "MULTSTR", "( s a -- x ) Puts a string that's a times string s on the stack. s\" A\" 6 MULTSTR ==> AAAAAA" },
  { handleSTRIPSTR, "STRIPSTR", "( a -- x ) Removes whitespaces on both sides of string a" },
  { handleLSTRIPSTR, "LSTRIPSTR", "( a -- x ) Removes whitespaces on the left side of string a" },
  { handleRSTRIPSTR, "RSTRIPSTR", "( a -- x ) Removes whitespaces on the right side of string a" },
  { handleINTSTR, "INTSTR", "( a -- x ) Converts int to str." },
  { handleFLOATSTR, "FLOATSTR", "( a -- x ) Converts float to str." },
  { handleSTRINT, "STRINT", "( a -- x ) Converts str to int." },
  { handleSTRFLOAT, "STRFLOAT", "( a -- x ) Converts str to float." },
  { handleCSPLIT, "CSPLIT", "( s t -- a b c d...) Splits string s by delimiter t (one ASCII char) and puts the result on the stack." },
  { handleSPLITDELIM, "SPLITD", "( s t -- a b c d...) Splits string s by delimiter t (a string) and puts the result on the stack." },
  { handleStringReverse, "SREVERSE", "( s0 s1 s2 s3 s4... n -- sx... s4 s3 s2 s1 n ) Reverses a stack of strings prefixed by count." },
  { handleDINSERT, "DINSERT", "( s1 s0 n -- s ) Inserts s0 into s1 every n chars." },
  { handleStringReplace, "STRREPLACE", "( s0 s1 s2 -- s ) Replaces instances of s1 by s2 in s0." },
  { handleSFILL, "SFILL", "( s v -- s ) Fills string s with string v." },
  { handleCFILL, "CFILL", "( s c -- s ) Fills string s with char c." },

  { handleVARRAY, "VARRAY", "( a b c d... num name -- ) Creates an array with data a, b, c, d etc, making sure there are num data pieces." },
  { handleSortVARRAY, "SORTV", "( name -- ) Sorts varray name." },
  { handleSortReverseVARRAY, "RSORTV", "( name -- ) Sorts varray name in reverse." },
  { handleFindVARRAY, "FINDV", "( value name -- ) Looks for value in varray name." },

  { forgetVAR, "FORGET", "( name -- ) Erases var/const named 'name' if it exists." },

  { handleDUP, "DUP", "( a -- a a ) Duplicates value on top of the stack." },
  { handleDROP, "DROP", "( a -- ) Drops value on top of the stack." },
  { handleSWAP, "SWAP", "( a b -- b a ) Swaps the 2 values on top of the stack." },
  { handleDEPTH, "DEPTH", "( a b c d... -- a b c d... x ) Puts the length of the stack on top of the stack." },
  { handleCLEAR, "CLEAR", "( a b c d... -- ) Removes everything from the stack." },
  // { handleROT, "ROT", "(a b c -- c a b) Rotates the 3 values on top of the stack." },
  { handleROLL, "ROLL", "( a b c d... u -- x y z t... ) Rotates u items. SWAP = 1 ROLL. ROT = 2 ROLL" },
  { handleSPICK, "STRPICK", "( s0 s s2 s3... n x -- s0 s s2 s3... n sx ) Copies string x among the n strings on top of the stack." },
  { handleSSTORE, "STRSTORE", "( s0 s s2 s3... n S x -- s0 s s2 s3... n ) Takes string S and stores it at index x." },
  { handleSJOIN, "STRJOIN", "( s0 s s2 s3... n S -- s ) Joins strings on stack with S." },
  { handlePICK, "PICK", "( a b c d e f... n -- x ) Copies element n as x on top of the stack." },
  { handlePLACE, "PLACE", "( a b c d e f... n -- x n ) Puts x into row n." },
  { handleSlicer, "SLICER", "( s a b c d e f... n -- s0 s1 s2... sn ) Slices a string s into n elements of variable size." },
  { handleHEX2NUM, "HEX2NUM", "( s -- n ) Converts a hex string to a number." },

  { handleBASE, "BASE", "( a -- ) Sets the base" },
  { handleBASE2, "BIN", "( -- ) Sets the base to binary" },
  { handleBASE10, "DEC", "( -- ) Sets the base to decimal" },
  { handleBASE16, "HEX", "( -- ) Sets the base to hexadecimal" },
  { handleStore, "!", "( ad a -- ) Stores a into variable at address ad. myvar 10 !" },
  { handleStorePlus, "!+", "( ad -- ) Increments variable at address ad. myvar +!" },
  { handleRetrieve, "@", "( ad -- ) Puts contents of variable at address ad on top of the stack. myvar @" },
  { handleCR, "CR", "( -- ) Prints a Carriage Return" },
  { showStack, ".S", "( -- ) Displays the stack." },
  { showVars, ".V", "( -- ) Shows existing vars by type" },
  { handleWITHIN, "WITHIN", "( n0 n1 n2 -- [01] ) Puts the result of (n0 >= n1 && n0 <= n2) on top of the stack." },
  { handleEqual, "=", "( a b -- [01] ) Puts the result of (a == b) on top of the stack." },
  { handleStringEqual, "S=", "( a b -- [01] ) Puts the result of (a == b) on top of the stack for strings." },
  { handleLower, "<", "( a b -- [01] ) Puts the result of (a < b) on top of the stack." },
  { handleLowerEqual, "<=", "( a b -- [01] ) Puts the result of (a <= b) on top of the stack." },
  { handleGreater, ">", "( a b -- [01] ) Puts the result of (a > b) on top of the stack." },
  { handleGreaterEqual, ">=", "( a b -- [01] ) Puts the result of (a >= b) on top of the stack." },
  { handleDifferent, "<>", "( a b -- [01] ) Puts the result of (a != b) on top of the stack." },
  { handleEqualQ, "=?", "( a b -- a [01] ) Same as = but preserves a." },
  { handleGreaterQ, ">?", "( a b -- a [01] ) Same as > but preserves a." },
  { handleLowerQ, "<?", "( a b -- a [01] ) Same as < but preserves a." },
  { handleLowerEqualQ, "<=?", "( a b -- a [01] ) Same as <= but preserves a." },
  { handleGreaterEqualQ, ">=?", "( a b -- a [01] ) Same as >= but preserves a." },
  { handleDifferentQ, "<>?", "( a b -- a [01] ) Same as <> but preserves a." },
  { handleBEGIN, "BEGIN", "( -- ) Start of BEGIN...WHILE/UNTIL" },
  { handleUNTIL, "UNTIL", "(cond -- ) tests condition and loops, or not" },
  { handleWHILE, "WHILE", "(cond -- ) tests condition and loops, or not" },
  { handleDO, "DO", "( -- ) Start of DO...LOOP" },
  { handleLOOP, "LOOP", "( -- ) Increments loop index by 1 and loops or not." },
  { handlePlusLoop, "+LOOP", "( a -- ) Increments loop index by a instead of 1 and loops or not." },
  { handleI, "I", "( -- I ) Puts current loop index on top of the stack." },
  { handleIprime, "I'", "( -- I' ) Puts loop maximum on top of the stack." },
  { handleJ, "J", "( -- I ) Puts outer loop index on top of the stack (imbricated loops)." },
  { handleRput, ">R", "( a -- ) Puts a on the return stack." },
  { handleRget, "R>", "( -- a ) Puts top of the return stack onto the stack." },
  { handleEXEC, "EXEC", "( s -- ?) Executes string on the stack. Can be used in conjunction with LINE." },
  { handleFLOAD, "FLOAD", "( s -- ?) Loads file named 'name' and executes it." },
  { handleFSAVE, "FSAVE", "( cd fn -- ?) Saves string cd to file 'fn'." },

  { handleOpenPort, "UOPEN", "( 9600 s\" /dev/tty.usb...\" -- n ) Open ports at designated baud rate. Puts TRUE/FALSE on top of the stack." },
  { handleReadLinePort, "UREADL", "( -- s ) Reads a line from port." },
  { handleReadHEXLinePort, "UREADHEXL", "( -- s ) Reads a line from port." },
  { handleReadRawPort, "UREADRAW", "( n -- s ) Reads x bytes from port and puts them as a string on the stack." },
  { handleReadRawHexPort, "UREADHEX", "( n -- s ) Reads x bytes from port and puts them as a HEX string on the stack." },
  { handleFlushPort, "UFLUSH", "( -- s ) Flushes the port." },
  { handleFIONREAD, "UINQ", "( -- n ) Puts on the stack how many bytes are available on the port." },
  { handleReadDiscardPort, "UDISCARDUNTIL", "( s -- ) Reads and discards from port until s." },
  { handleReadHEXUntilPort, "UREADHEXUNTIL", "( s -- ) Reads from port until s." },
  { handleReadUntilPort, "UREADUNTIL", "( s -- ) Reads from port until s." },
  { handleReadCharPort, "UREADC", "( -- c ) Reads one byte from serial port." },
  { handleClosePort, "UCLOSE", "( -- ) Closes the port." },
  { handleWritePort, "UWRITE", "( s -- ) Writes string s to the port." },

  { putRandomByteOnStack, "RANDOM", "( -- a ) Puts a random byte on top of the stack." },
  { putRandomUIntOnStack, "RANDOMI", "( -- a ) Puts a random INT on top of the stack." },
  { handleIF, "IF", "( cond -- ) Beginning of IF THEN ELSE" },
  { handleTHEN, "THEN", "( words -- ? ) words between IF and THEN are executed if true." },
  { handleELSE, "ELSE", "( words -- ? ) words between THEN and ELSE are executed if false." },
  { handleEXIT, "EXIT", "( -- ) Exits ddForth" },
  { handleCELLS, "ARRAY", "( a b name -- ) Creates array name with b rows containing a." },
  { handleARRAYLIST, "ARRAYS", "( -- ) Lists existing arrays by type." },
  { handleCELLSTORE, ">IX", "( a b name -- ) Stores a into row b of array name." },
  { handleCELLRETRIEVE, "IX>", "( a name -- b ) Puts contents of row a of array name on top of the stack." },
  { handleCELLLENGTH, "LEN>", "( name -- a ) Puts length of array name on top of the stack." },
  { handleCELLAPPEND, "IX+", "( a name -- ) Appends a to array name." },
  { handleCELLPREPEND, "+IX", "( a name -- ) Prepends a to array name." },
  { handleCELLLROT, "<ROT", "( name -- ) Rotates up array name." },
  { handleCELLRROT, "ROT>", "( name -- ) Rotates down array name." },
  { handleCELLLIST, "ALIST", "( -- ) List of arrays." },
  { handleARRAYSUM, "ASUM", "( name -- a ) Puts the sum of all elements of array name on top of the stack." },

  { handleGotoXY, "POSXY", "( x y -- ) Positions cursor (terminal/UNIX-like) to x:y." },
  { handleClearTerminal, "CLEAN", "( -- ) Clears the screen (terminal/UNIX-like) and sets cursor to 1:1." },
  { handleSleep, "SLEEP", "( n -- ) Sleeps for n seconds." },
  { handleDelay, "DELAY", "( n -- ) Sleeps for n microseconds." },
// #include "lowercase.hpp"

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
#include "USB_UART.hpp"
#if defined(NEED_SDL)
#include "sdl_helpers/sdl_helper.hpp"
#endif

void initForth() {
  xxxxxx = snprintf((char *)msg, 255, "init ");
  logThis();
  nativeCmdCount = sizeof(nativeCommands) / sizeof(nativeCommand);
  StoreINT("BASE", 10);
  StoreINT("VER.", myVERSION);
  firstUserINT = myVARs.size();
  StoreCONSTFLOAT("PI", 3.141592653f);
  StoreCONSTFLOAT("E", 2.718281828459045f);
  firstUserFLOAT = myFVARs.size();
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
    printf(" • %-15s\t%s\n", nativeCommands[ix].name.c_str(), nativeCommands[ix].help.c_str());
  }
  for (vector<userCommand>::iterator it = userCommands.begin(); it != userCommands.end(); ++it) {
    printf(" • %-20s %s\n", it->name.c_str(), it->command.c_str());
  }
  return true;
}

bool handleGotoXY() {
  // ANSI escape code for cursor positioning: \033[<line>;<column>H
  int x, y;
  if (popIntegerFromStack(&y) == false) {
    logStackOverflow((char *)"handleGotoXY/0");
    return false;
  }
  if (popIntegerFromStack(&x) == false) {
    logStackOverflow((char *)"handleGotoXY/1");
    return false;
  }
  cout << "\033[" << y << ";" << x << "H";
  flush(cout); // Ensure the escape code is sent immediately
  return true;
}

bool handleClearTerminal() {
  cout << "\033[2J\033[1;1H";
  // Clears screen and moves cursor to top-left
  return true;
}

bool handleHexDump() {
  string mySTRING;
  if (popStringFromStack(&mySTRING) == false) {
    logStackOverflow((char *)"handleHexDump/0");
    return false;
  }
  hexDump((unsigned char *)mySTRING.c_str(), mySTRING.length());
  return true;
}

// end