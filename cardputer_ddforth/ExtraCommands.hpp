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
  {"-rot", "rot rot"},
  {"true", "1 ="},
  {"false", "0 ="},
  {"nROT>", "0 DO DUP ROT> LOOP CLEAR"},
  {"n<ROT", "0 DO DUP <ROT LOOP CLEAR"},
  {"ssplit", "32 csplit"},
  {"SSPLIT", "32 CSPLIT"},
};
int userCmdCount = 0;
