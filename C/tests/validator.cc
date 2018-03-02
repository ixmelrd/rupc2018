#include "./testlib.h"
#include "./constraints.hpp"
#include<iostream>
#include <cassert>

int main() {

  registerValidation();

  int n = inf.readInt(MIN_N, MAX_N);
  inf.readEoln();

  for(int i = 0; i < n ; i++){

    inf.readInt(MIN_A, MAX_A);

    if(i<n-1)
      inf.readSpace();
    else
      inf.readEoln();

  }

  inf.readEof();

}
