using namespace std;

bool debuggerOn = false;
bool stopHere = false;
bool isRestarting = false;
int restartExecutionPointer = -1;
vector<string> restartChunks;
vector<int> restartIFsave;
vector<int> restartELSEsave;
vector<int> restartTHENsave;
bool handleRestart();



bool popFloatFromStack(float *);
bool popFromLoopStack(int *);
bool popIntegerFromJumpStack(int *);
bool popIntegerFromStack(int *);
bool popStringFromStack(string *);
bool putFloatOnStack(float);
bool putIntegerOnJumpStack(int);
bool putIntegerOnStack(int);
bool putStringOnStack(string);
void logStack(char *);
void logInconsistent(char *who);
void logStackOverflow(char *who);
bool showStack();
bool showVars();
void evaluate(vector<string>);
bool showJumpStack();

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
extern std::map<string, int> varAddresses;
extern std::map<string, int> fvarAddresses;
extern std::map<string, int> constAddresses;
extern std::map<string, int> fconstAddresses;
extern vector<int> myVARs;
extern vector<float> myFVARs;
extern vector<int> myCONSTs;
extern vector<float> myFCONSTs;
extern vector<string> computedWords;
extern char code[256];
extern int xxxxxx;
extern char msg[256];
extern vector<int> indexIF;
extern vector<int> indexELSE;
extern vector<int> indexTHEN;

bool handleDebugMode() {
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleDebugMode");
    return false;
  }
  debuggerOn = ((i0 & 1) == 1);
  if (debuggerOn)
    cout << " debugger ON ";
  else
    cout << " debugger OFF ";
  return true;
}

bool handleBP() {
  if (!debuggerOn) return true;
  cout << "\nBREAKPOINT!\n";
  showStack();
  showVars();
  showJumpStack();
  stopHere = true;
  return true;
}

bool handleRestart() {
  if (!debuggerOn) return false;
  cout << "\nRESTART at cell " << restartExecutionPointer << ": " << restartChunks.at(restartExecutionPointer) << endl;
  indexIF.clear();
  indexELSE.clear();
  indexTHEN.clear();
  for (vector<int>::iterator it = restartIFsave.begin() ; it != restartIFsave.end(); ++it)
    indexIF.push_back(*it);
  for (vector<int>::iterator it = restartELSEsave.begin() ; it != restartELSEsave.end(); ++it)
    indexELSE.push_back(*it);
  for (vector<int>::iterator it = restartTHENsave.begin() ; it != restartTHENsave.end(); ++it)
    indexTHEN.push_back(*it);
  // IF THEN ELSE indexes have been restored.
  isRestarting = true;
  evaluate(restartChunks);
  restartChunks.clear();
  restartIFsave.clear();
  restartELSEsave.clear();
  restartTHENsave.clear();
  executionPointer = 65535;
  return true;
}













