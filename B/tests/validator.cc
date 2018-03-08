#include "./constraints.hpp"
#include "./testlib.h"
#include <iostream>
#include <set>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

int main() {
  registerValidation();
  int N = inf.readInt(MIN_N, MAX_N);
  inf.readEoln();
  vector<int> a(N), b(N);
  rep(i, N) {
    a[i] = inf.readInt(MIN_a, MAX_a);
    if (i < N - 1) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  rep(i, N) {
    b[i] = inf.readInt(MIN_b, MAX_b);
    if (i < N - 1) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  inf.readEof();

  set<int> s(a.begin(), a.end());
  if (s.size() != N) {
    cerr << "a_i must be unique" << endl;
    return 1;
  }

  rep(i, N) {
    if (!s.count(b[i])) {
      cerr << "Set S must contain b_" << i + 1 << "(=" << b[i] << ")" << endl;
      return 1;
    }
  }
}
