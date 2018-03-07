#include "./testlib.h"
#include "./constraints.hpp"
#include<iostream>
#include <cassert>

int main() {

  registerValidation();

  int N = inf.readInt(MIN_N, MAX_N);

  inf.readSpace();

  inf.readInt(MIN_M, N);

  inf.readEoln();

  for(int i = 0; i < N ; i++){

    inf.readInt(MIN_a, MAX_a);

    if(i < N-1)
      inf.readSpace();
    else
      inf.readEoln();

  }

  inf.readEof();

}
