#include <cmath> // For sin, cos, tan
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
  math_EQUALQ,
  math_GREATERQ,
  math_LOWERQ,
  math_GREATEREQUALQ,
  math_LOWEREQUALQ,
  math_DIFFERENTQ,
  math_MOD,
  math_MIN,
  math_MAX,
  math_AND,
  math_OR,
  math_XOR,
  math_NOT,
  math_NEGATE,
};

bool handle2Nums(unsigned char X) {
  unsigned char type1 = dataStack.at(dataStack.size() - 1);
  unsigned char type0 = dataStack.at(dataStack.size() - 2);
  if (type0 == xSTRING || type0 == xINVALID || type1 == xSTRING || type1 == xINVALID) {
    logInconsistent((char *)"handle2Nums");
    showStack();
    return false;
  }
  if (type0 == type1) {
    if (type0 == xINTEGER) {
      xxxxxx = snprintf((char *)msg, 255, "2 INTs ");
      logThis();
      int i0, i1;
      if (popIntegerFromStack(&i1) == false) {
        logStackOverflow((char *)"handle2Nums1");
        return false;
      }
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char *)"handle2Nums2");
        return false;
      }
      switch (X) {
        case math_PLUS:
          {
            putIntegerOnStack(i0 + i1);
            break;
          }
        case math_MINUS:
          {
            putIntegerOnStack(i0 - i1);
            break;
          }
        case math_MULT:
          {
            putIntegerOnStack(i0 * i1);
            break;
          }
        case math_DIV:
          {
            putIntegerOnStack(i0 / i1);
            break;
          }
        case math_GREATER:
          {
            putIntegerOnStack((i0 > i1));
            break;
          }
        case math_GREATEREQUAL:
          {
            putIntegerOnStack((i0 > i1) || (i0 == i1));
            break;
          }
        case math_LOWER:
          {
            putIntegerOnStack((i0 < i1));
            break;
          }
        case math_LOWEREQUAL:
          {
            putIntegerOnStack((i0 < i1) || (i0 == i1));
            break;
          }
        case math_DIFFERENT:
          {
            putIntegerOnStack((i0 != i1));
            break;
          }
        case math_EQUAL:
          {
            putIntegerOnStack((i0 == i1));
            break;
          }
        case math_EQUALQ:
          {
            putIntegerOnStack(i0);
            putIntegerOnStack((i0 == i1));
            break;
          }
        case math_LOWERQ:
          {
            putIntegerOnStack(i0);
            putIntegerOnStack((i0 < i1));
            break;
          }
        case math_GREATERQ:
          {
            putIntegerOnStack(i0);
            putIntegerOnStack((i0 > i1));
            break;
          }
        case math_MOD:
          {
            putIntegerOnStack((i0 % i1));
            break;
          }
        case math_AND:
          {
            putIntegerOnStack((i0 & i1));
            break;
          }
        case math_OR:
          {
            putIntegerOnStack((i0 | i1));
            break;
          }
        case math_XOR:
          {
            putIntegerOnStack((i0 ^ i1));
            break;
          }
        case math_MIN:
          {
            if (i0 < i1) putIntegerOnStack(i0);
            else putIntegerOnStack(i1);
            break;
          }
        case math_MAX:
          {
            if (i0 > i1) putIntegerOnStack(i0);
            else putIntegerOnStack(i1);
            break;
          }
      }
      return true;
    } else {
      float f0, f1;
      if (popFloatFromStack(&f1) == false) {
        logStackOverflow((char *)"handle2Nums3");
        return false;
      }
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char *)"handle2Nums4");
        return false;
      }
      xxxxxx = snprintf((char *)msg, 255, "2 FLOATs ");
      logThis();
      switch (X) {
        case math_PLUS:
          {
            putFloatOnStack(f0 + f1);
            break;
          }
        case math_MINUS:
          {
            putFloatOnStack(f0 - f1);
            break;
          }
        case math_MULT:
          {
            putFloatOnStack(f0 * f1);
            break;
          }
        case math_DIV:
          putFloatOnStack(f0 / f1);
          break;
        case math_GREATER:
          {
            putIntegerOnStack((f0 > f1));
            break;
          }
        case math_GREATEREQUAL:
          {
            putIntegerOnStack((f0 > f1) || (f0 == f1));
            break;
          }
        case math_LOWER:
          {
            putIntegerOnStack((f0 < f1));
            break;
          }
        case math_LOWEREQUAL:
          {
            putIntegerOnStack((f0 < f1) || (f0 == f1));
            break;
          }
        case math_DIFFERENT:
          {
            putIntegerOnStack((f0 != f1));
            break;
          }
        case math_EQUAL:
          {
            putIntegerOnStack((f0 == f1));
            break;
          }
        case math_EQUALQ:
          {
            putFloatOnStack(f0);
            putIntegerOnStack((f0 == f1));
            break;
          }
        case math_GREATERQ:
          {
            putFloatOnStack(f0);
            putIntegerOnStack((f0 > f1));
            break;
          }
        case math_GREATEREQUALQ:
          {
            putFloatOnStack(f0);
            putIntegerOnStack((f0 >= f1));
            break;
          }
        case math_LOWERQ:
          {
            putFloatOnStack(f0);
            putIntegerOnStack((f0 < f1));
            break;
          }
        case math_LOWEREQUALQ:
          {
            putFloatOnStack(f0);
            putIntegerOnStack((f0 <= f1));
            break;
          }
        case math_MOD:
          {
            int i0 = (f0 / f1);
            i0 *= f1;
            float f2 = f0 - i0;
            putFloatOnStack(f2);
          }
          break;
        case math_MIN:
          {
            if (f0 < f1) putFloatOnStack(f0);
            else putFloatOnStack(f1);
            break;
          }
        case math_MAX:
          {
            if (f0 > f1) putFloatOnStack(f0);
            else putFloatOnStack(f1);
            break;
          }
      }
      return true;
    }
  } else {
    // one int one float
    xxxxxx = snprintf((char *)msg, 255, "1 INT, 1 FLOAT ");
    logThis();
    bool intFirst = false;
    if (type0 == xINTEGER) intFirst = true;
    // we need to know which comes first for / and -
    int i1;
    float f0, f1;
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handle2Nums5");
      return false;
    }
    if (popIntegerFromStack(&i1) == false) {
      logStackOverflow((char *)"handle2Nums6");
      return false;
    }
    f1 = i1;  // The int is converted to a float
    switch (X) {
      case math_PLUS:
        {
          putFloatOnStack(f0 + f1);
          break;
        }
      case math_MINUS:
        {
          if (intFirst) putFloatOnStack(f1 - f0);
          else putFloatOnStack(f0 - f1);
          break;
        }
      case math_MULT:
        {
          putFloatOnStack(f0 * f1);
          break;
        }
      case math_DIV:
        {
          if (intFirst) putFloatOnStack(f1 / f0);
          else putFloatOnStack(f0 / f1);
          break;
        }
      case math_GREATER:
        {
          if (intFirst) putIntegerOnStack(f1 > f0);
          else putIntegerOnStack(f0 > f1);
          break;
        }
      case math_GREATEREQUAL:
        {
          if (intFirst) putIntegerOnStack((f1 > f0) || (f1 == f0));
          else putIntegerOnStack((f0 > f1) || (f0 == f1));
          break;
        }
      case math_LOWER:
        {
          if (intFirst) putIntegerOnStack(f1 < f0);
          else putIntegerOnStack(f0 < f1);
          break;
        }
      case math_LOWEREQUAL:
        {
          if (intFirst) putIntegerOnStack((f1 < f0) || (f1 == f0));
          else putIntegerOnStack((f0 < f1) || (f0 == f1));
          break;
        }
      case math_DIFFERENT:
        {
          putIntegerOnStack((f0 != f1));
          break;
        }
      case math_EQUAL:
        {
          putIntegerOnStack((f0 == f1));
          break;
        }
      case math_MOD:
        {
          int i0 = f0;
          if (intFirst) putIntegerOnStack(i1 % i0);
          else putIntegerOnStack(i0 % i1);
          break;
        }
      case math_MIN:
        {
          if (f0 < f1) putFloatOnStack(f0);
          else putFloatOnStack(f1);
          break;
        }
      case math_MAX:
        {
          if (f0 > f1) putFloatOnStack(f0);
          else putFloatOnStack(f1);
          break;
        }
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

bool handleMIN() {
  return handle2Nums(math_MIN);
}

bool handleMAX() {
  return handle2Nums(math_MAX);
}

bool handleABS() {
  if (dataStack.size() == 0) {
    logStackOverflow((char *)"handleDROP");
    return false;
  }
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  switch (type0) {
    case xINTEGER:
      int i0;
      if (popIntegerFromStack(&i0) == false) {
        logStackOverflow((char *)"handleABS1");
        return false;
      }
      putIntegerOnStack(abs(i0));
      return true;
      break;
    case xFLOAT:
      float f0;
      if (popFloatFromStack(&f0) == false) {
        logStackOverflow((char *)"handleDROP2");
        return false;
      }
      putFloatOnStack(abs(f0));
      return true;
      break;
  }
  return false;
}

bool handleGreater() {
  return handle2Nums(math_GREATER);
}

bool handleGreaterEqual() {
  return handle2Nums(math_GREATEREQUAL);
}
bool handleLower() {
  return handle2Nums(math_LOWER);
}

bool handleLowerEqual() {
  return handle2Nums(math_LOWEREQUAL);
}

bool handleEqual() {
  return handle2Nums(math_EQUAL);
}

bool handleDifferent() {
  return handle2Nums(math_EQUAL);
}

bool handleEqualQ() {
  return handle2Nums(math_EQUALQ);
}

bool handleGreaterQ() {
  return handle2Nums(math_GREATERQ);
}

bool handleLowerQ() {
  return handle2Nums(math_LOWERQ);
}

bool handleGreaterEqualQ() {
  return handle2Nums(math_GREATEREQUALQ);
}

bool handleLowerEqualQ() {
  return handle2Nums(math_LOWEREQUALQ);
}

bool handleDifferentQ() {
  return handle2Nums(math_DIFFERENTQ);
}

bool handleEXP() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleEXP");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleEXP");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleEXP");
      return false;
    }
  }
  putFloatOnStack(std::exp(f0));
  return true;
}

bool handleCEIL() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleCEIL");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleCEIL");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleCEIL");
      return false;
    }
  }
  putFloatOnStack(std::ceil(f0));
  return true;
}

bool handleFLOOR() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleFLOOR");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleFLOOR");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleFLOOR");
      return false;
    }
  }
  putFloatOnStack(std::floor(f0));
  return true;
}

bool handleROUND() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleROUND");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleROUND");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleROUND");
      return false;
    }
  }
  putFloatOnStack(std::round(f0));
  return true;
}

bool handleLOG() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleLOG");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleLOG");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleLOG");
      return false;
    }
  }
  putFloatOnStack(std::log(f0));
  return true;
}

bool handleLOG10() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleLOG10");
    return false;
  }
  float f0;
  if (type0 == xINTEGER) {
    int i0;
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleLOG10");
      return false;
    }
    f0 = i0;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleLOG10");
      return false;
    }
  }
  putFloatOnStack(std::log(f0));
  return true;
}

bool handleSQR() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleSQR");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSQR");
      return false;
    }
    putFloatOnStack(i0 * i0);
    return true;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleSQR");
      return false;
    }
    putFloatOnStack(f0 * f0);
    return true;
  }
  return false;
}

bool handleSQRT() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleSQR");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSQR");
      return false;
    }
    putFloatOnStack(sqrt(i0));
    return true;
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleSQR");
      return false;
    }
    putFloatOnStack(sqrt(f0));
    return true;
  }
  return false;
}

bool handleSIN() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleSIN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::sin(f0));
  return true;
}

bool handleCOS() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleCOS");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::cos(f0));
  return true;
}

bool handleTAN() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleTAN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleTAN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleTAN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::tan(f0));
  return true;
}

bool handleASIN() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleSIN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::asin(f0));
  return true;
}

bool handleACOS() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleCOS");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::acos(f0));
  return true;
}

bool handleATAN() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleATAN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleATAN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleATAN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::atan(f0));
  return true;
}

bool handleSINH() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleSIN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleSIN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::sin(f0));
  return true;
}

bool handleCOSH() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleCOS");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleCOS");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::cos(f0));
  return true;
}

bool handleTANH() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID) {
    logInconsistent((char *)"handleTAN");
    return false;
  }
  int i0;
  float f0;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleTAN");
      return false;
    }
    f0 = i0 * (3.141592653 / 180.0);
  } else {
    if (popFloatFromStack(&f0) == false) {
      logStackOverflow((char *)"handleTAN");
      return false;
    }
    f0 = f0 * (3.141592653 / 180.0);
  }
  putFloatOnStack(std::tan(f0));
  return true;
}

bool handleMOD() {
  return handle2Nums(math_MOD);
}

bool handleAND() {
  return handle2Nums(math_AND);
}

bool handleOR() {
  return handle2Nums(math_OR);
}

bool handleXOR() {
  return handle2Nums(math_XOR);
}

bool handleNOT() {
  int n;
  if (popIntegerFromStack(&n) == false) {
    logStackOverflow((char *)"handleNOT");
    return false;
  }
  putIntegerOnStack(1 - (n&1));
  return true;
}

bool handleNEGATE() {
  int n;
  int i0;
  if (popIntegerFromStack(&i0) == false) {
    logStackOverflow((char *)"handleNEGATE");
    return false;
  }
  n = i0;
  putIntegerOnStack((~n) + 1);
  return true;
}

bool handleINVERT() {
  unsigned char type0 = dataStack.at(dataStack.size() - 1);
  if (type0 == xSTRING || type0 == xINVALID || type0 == xFLOAT) {
    logInconsistent((char *)"handleINVERT");
    return false;
  }
  int i0;
  unsigned int i1;
  if (type0 == xINTEGER) {
    if (popIntegerFromStack(&i0) == false) {
      logStackOverflow((char *)"handleINVERT");
      return false;
    }
    i1 = i0;
    putIntegerOnStack(~i1);
    return true;
  }
  return false;
}
bool handleFact() {
  int factorial = 1;
  int n;
  if (popIntegerFromStack(&n) == false) {
    logStackOverflow((char *)"handleFact");
    return false;
  }
  if (n < 0) {
    xxxxxx = snprintf((char *)msg, 255, "Factorial is not defined for negative numbers.");
    logThis();
    return false;
  }
  for (int i = 1; i <= n; ++i)
    factorial *= i;
  putIntegerOnStack(factorial);
  return true;
}

bool handleBASE() {
  xxxxxx = snprintf((char *)msg, 255, "handleBASE ");
  logThis();
  return putIntegerOnStack(GetINTaddress("BASE"));
}

bool handleBASE2() {
  xxxxxx = snprintf((char *)msg, 255, "handleBASE2 ");
  logThis();
  StoreINT("BASE", 2);
  return true;
}

bool handleBASE10() {
  xxxxxx = snprintf((char *)msg, 255, "handleBASE10 ");
  logThis();
  StoreINT("BASE", 10);
  return true;
}

bool handleBASE16() {
  xxxxxx = snprintf((char *)msg, 255, "handleBASE16 ");
  logThis();
  StoreINT("BASE", 16);
  return true;
}
