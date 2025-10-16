#include <iostream>
#include <vector>

using namespace std;
int main () {
  std::vector<string> myvector;
  std::vector<string>::iterator it;
  myvector.push_back("zero");
  myvector.push_back("one");
  myvector.push_back("two");
  myvector.push_back("three");
  myvector.push_back("four");

  it = myvector.begin();
  std::vector<string> anothervector;
  anothervector.push_back("10");
  anothervector.push_back("11");
  anothervector.push_back("12");
  anothervector.push_back("13");
  myvector.erase(myvector.begin() + 3);
  myvector.insert(it + 3, anothervector.begin(), anothervector.end());

  std::cout << "myvector contains:";
  for (it=myvector.begin(); it<myvector.end(); it++)
    std::cout << ' ' << *it;
  std::cout << '\n';

  return 0;
}
