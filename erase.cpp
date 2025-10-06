// erasing from vector
#include <iostream>
#include <vector>

int main () {
  std::vector<int> myvector;
  // set some values (from 1 to 20)
  for (int i = 0; i <= 20; i++)
    myvector.push_back(i);
  myvector.erase(myvector.begin() + 3, myvector.begin() + 7);
  std::cout << "myvector contains:";
  for (unsigned i = 0; i < myvector.size(); ++i)
    std::cout << ' ' << myvector[i];
  std::cout << '\n';
  return 0;
}
