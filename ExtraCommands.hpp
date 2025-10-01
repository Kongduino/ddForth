#include <vector>

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
  {"++", "+ +"},
  {"NIP", "SWAP DROP"},
  {"TUCK", "SWAP OVER"},
  {"-ROT", "ROT ROT"},
  {"nip", "swap drop"},
  {"tuck", "swap over"},
  {"?DUP", "DUP 0= IF THEN DUP ELSE"},
  {"2DUP", "0 PICK 1 PICK"},
  {"2DROP", "DROP DROP"},
  {"2SWAP", "4 roll 4 roll"},
  {"2OVER", "depth 4 - pick depth 4 - pick"},
  {"-rot", "rot rot"},
  {"true", "1 ="},
  {"false", "0 ="},
  {"nROT>", "0 DO DUP ROT> LOOP CLEAR"},
  {"n<ROT", "0 DO DUP <ROT LOOP CLEAR"},
  {"ssplit", "32 csplit"},
  {"SSPLIT", "32 CSPLIT"},

#if defined(NEED_SDL)
#include "sdl_helpers/sdl_inc3.hpp"
#endif

};
int userCmdCount = 0;
