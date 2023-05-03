#include <iostream>

using namespace std;

int Catalan(int n) {
  // returns the n'th Catalan number
  // Source (Theory): https://oeis.org/A000108
  if (n == 0)
    return 1;
  return Catalan(n - 1) * (2 * n - 1) * (2 * n) / n / (n + 1);
}

int main() {
  int n;
  cin >> n;
  cout << Catalan(n) << endl;
  return 0;
}
