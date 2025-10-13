using namespace std;

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
  handleClearTerminal();
  // In case the BP hasn't been excised from the chunks during tokenization
  cout << "\nBREAKPOINT!\n";
  showStack(70, 1);
  showVars(70, dataStack.size() + 5);
  gotoXY(1, 3);
  showJumpStack();
  handleARRAYLIST();
  stopHere = true;
  bpStop = true;
  return true;
}

bool handleRestart() {
  // if (!debuggerOn) return false;
  cout << "\nRESTART at cell " << restartExecutionPointer << " / " << restartChunks.size() << endl;
  restoreFromBreak();
  showJumpStack();
  isRestarting = true;
  evaluate(restartChunks);
  restartIFsave.clear();
  restartELSEsave.clear();
  restartTHENsave.clear();
  executionPointer = 65535;
  return true;
}

bool handleStep() {
  stopHere = false;
  requestStop = true;
  return handleRestart();
}

// end