#include "./testlib.h"
#include "./constraints.hpp"
#include<iostream>
#include <cassert>
#include <set>

int main() {

  registerValidation();

  int n = inf.readInt(MIN_N, MAX_N);
  inf.readEoln();

  std::set<int> s;

  for(int i = 0; i < n ; i++){

	s.emplace(inf.readInt(MIN_A, MAX_A));

    if(i<n-1)
      inf.readSpace();
    else
      inf.readEoln();

  }

  assert(n == s.size());

  inf.readEof();

}
