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
    a[i] = inf.readInt(MIN_a, N);
    if (i < N - 1) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  rep(i, N) {
    inf.readInt(MIN_b, N);
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
}
