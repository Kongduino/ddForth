using namespace std;

extern bool debuggerOn;
extern bool stopHere;
extern bool isRestarting;
extern int restartExecutionPointer;
extern vector<string> restartChunks;
extern vector<int> restartIF;
extern vector<int> restartELSE;
extern vector<int> restartTHEN;
extern vector<int> restartIFsave;
extern vector<int> restartELSEsave;
extern vector<int> restartTHENsave;
bool handleRestart();

extern vector<int> indexIF;
extern vector<int> indexELSE;
extern vector<int> indexTHEN;
extern int ifLevels;
extern int thenStep, elseStep;
extern vector<int> jumpStackSave;
extern vector<int> jumpStackTypeSave;
extern vector<int> loopStackSave;


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

void saveForBreak(vector<string> chunks) {
  // cout << "saveForBreak: " << chunks.size() << " ops.\n";
  // save the chunks
  restartChunks.clear();
  for (vector<string>::iterator it = chunks.begin(); it != chunks.end(); ++it) {
    restartChunks.push_back(*it);
    // cout << *it << " ";
  }
  // cout << endl;
  // cout << "saveForBreak: " << restartChunks.size() << " ops.\n";
  restartIFsave.clear();
  restartELSEsave.clear();
  restartTHENsave.clear();
  jumpStackSave.clear();
  jumpStackTypeSave.clear();
  loopStackSave.clear();
  if (indexIF.size() > 0) {
    // cout << " . Saving indexIF\n";
    for (vector<int>::iterator it = indexIF.begin(); it != indexIF.end(); ++it)
      restartIFsave.push_back(*it);
  }
  if (indexELSE.size() > 0) {
    // cout << " . Saving indexELSE\n";
    for (vector<int>::iterator it = indexELSE.begin(); it != indexELSE.end(); ++it)
      restartELSEsave.push_back(*it);
  }
  if (indexTHEN.size() > 0) {
    // cout << " . Saving indexTHEN\n";
    for (vector<int>::iterator it = indexTHEN.begin(); it != indexTHEN.end(); ++it)
      restartTHENsave.push_back(*it);
  }
  if (jumpStack.size() > 0) {
    // cout << " . Saving jumpStack\n";
    int count = 0;
    for (vector<int>::iterator it = jumpStack.begin(); it != jumpStack.end(); ++it) {
      jumpStackSave.push_back(*it);
      // cout << "\t" << count++ << ": " << *it << endl;
    }
  }
  if (jumpStackType.size() > 0) {
    // cout << " . Saving jumpStackType\n";
    int count = 0;
    for (vector<int>::iterator it = jumpStackType.begin(); it != jumpStackType.end(); ++it) {
      jumpStackTypeSave.push_back(*it);
      // cout << "\t" << count++ << ": " << *it << endl;
    }
  }
  if (loopStack.size() > 0) {
    // cout << " . Saving loopStack\n";
    int count = 0;
    for (vector<int>::iterator it = loopStack.begin(); it != loopStack.end(); ++it) {
      loopStackSave.push_back(*it);
      // cout << "\t" << count++ << ": " << *it << endl;
    }
  }
  indexIF.clear();
  indexELSE.clear();
  indexTHEN.clear();
  jumpStack.clear();
  jumpStackType.clear();
  loopStack.clear();
  // cout << "restartChunks.size(): " << restartChunks.size() << endl;
}

void restoreFromBreak() {
  indexIF.clear();
  indexELSE.clear();
  indexTHEN.clear();
  // cout << " * IFs " << restartIFsave.size() << " / " << restartELSEsave.size() << " / " << restartTHENsave.size() << endl;
  if (restartIFsave.size() > 0) {
    // cout << " * restartIFsave\n";
    for (vector<int>::iterator it = restartIFsave.begin(); it != restartIFsave.end(); ++it)
      indexIF.push_back(*it);
  }
  if (restartELSEsave.size() > 0) {
    // cout << " * restartELSEsave\n";
    for (vector<int>::iterator it = restartELSEsave.begin(); it != restartELSEsave.end(); ++it)
      indexELSE.push_back(*it);
  }
  if (restartTHENsave.size() > 0) {
    // cout << " * restartTHENsave\n";
    for (vector<int>::iterator it = restartTHENsave.begin(); it != restartTHENsave.end(); ++it)
      indexTHEN.push_back(*it);
  }
  restartIFsave.clear();
  restartELSEsave.clear();
  restartTHENsave.clear();
  // IF THEN ELSE indexes have been restored.
  // Backups have been nuked.
  // cout << " * jumps " << jumpStackSave.size() << " / " << jumpStackTypeSave.size() << " / " << loopStackSave.size() << endl;
  jumpStack.clear();
  jumpStackType.clear();
  loopStack.clear();
  if (jumpStackSave.size() > 0) {
    // cout << "\tjumpStack " << jumpStackSave.size() << endl;
    for (vector<int>::iterator it = jumpStackSave.begin(); it != jumpStackSave.end(); ++it) {
      jumpStack.push_back(*it);
      // cout << "\t* " << *it << endl;
    }
  }
  if (jumpStackTypeSave.size() > 0) {
    // cout << "\tjumpStackType " << jumpStackTypeSave.size() << endl;
    for (vector<int>::iterator it = jumpStackTypeSave.begin(); it != jumpStackTypeSave.end(); ++it) {
      jumpStackType.push_back(*it);
      // cout << "\t* " << *it << endl;
    }
  }
  if (loopStackSave.size() > 0) {
    // cout << "\tloopStack " << loopStackSave.size() << endl;
    for (vector<int>::iterator it = loopStackSave.begin(); it != loopStackSave.end(); ++it) {
      loopStack.push_back(*it);
      // cout << "\t* " << *it << endl;
    }
  }
  jumpStackSave.clear();
  jumpStackTypeSave.clear();
  loopStackSave.clear();
  // DO..LOOP and BEGIN stacks have been restored.
  // Backups have been nuked.
}

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
  // if (!debuggerOn) return false;
  cout << "\nRESTART at cell " << restartExecutionPointer << " / " << restartChunks.size() << endl;
  restoreFromBreak();
  showJumpStack();
  isRestarting = true;
  evaluate(restartChunks);
  // restartChunks.clear();
  restartIFsave.clear();
  restartELSEsave.clear();
  restartTHENsave.clear();
  executionPointer = 65535;
  return true;
}





// end