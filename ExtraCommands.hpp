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

};
int userCmdCount = 0;
