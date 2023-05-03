#include <cstring>
#include <iostream>

using namespace std;

#define upper(x) char(toupper(x))

string to_upper(string str) {
  int sz = str.size();
  if (sz == 1)
    return str;
  return upper(str[0]) + to_upper(str.substr(1, sz - 1));
}

int main() {
  string line;
  while (getline(cin, line))
    cout << to_upper(line + '\n');
  return 0;
}
