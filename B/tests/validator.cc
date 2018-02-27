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
  set<int> as;
  rep(i, N) {
    as.insert(inf.readInt(MIN_a, MAX_a));
    if (i < N - 1) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  rep(i, N) {
    inf.readInt(MIN_b, MAX_b);
    if (i < N - 1) {
      inf.readSpace();
    } else {
      inf.readEoln();
    }
  }
  inf.readEof();

  if (as.size() != N) {
    cout << "Expected a_i is unique; Got duplication;" << endl;
    return 1;
  }
}
