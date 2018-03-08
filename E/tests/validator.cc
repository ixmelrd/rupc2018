#include "./constraints.hpp"
#include "./testlib.h"
#include <iostream>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

int main() {
  registerValidation();
  string s = inf.readString();
  inf.readEof();

  int digitsOfN = static_cast<int>(s.size());
  if (digitsOfN < MIN_digits_of_N || MAX_digits_of_N < digitsOfN) {
    cerr << "Digits of N must be in [" << MIN_digits_of_N << ", " << MAX_digits_of_N << "]" << endl;
    return 1;
  }

  if (s[0] < '1' || '9' < s[0]) {
    cerr << "Most significant digit must be in [1, 9]" << endl;
    return 1;
  }

  loop(i, 1, digitsOfN) {
    if (s[i] < '0' || '9' < s[i]) {
      cerr << "Non most significant digit must be in [0, 9]" << endl;
      return 1;
    }
  }
}
