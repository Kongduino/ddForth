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
  {"BLACK", "0 0 0"},
  {"WHITE", "255 255 255"},
  {"RED", "255 0 0"},
  {"GREEN", "0 255 0"},
  {"BLUE", "0 0 255"},
};
int userCmdCount = 0;
