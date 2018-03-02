#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <queue>
using namespace std;

int main(){
	registerValidation();

    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
	int Q = inf.readInt(MIN_Q, MAX_Q);
    inf.readEoln();

    for(int i = 0; i < M; i++){
        int D = inf.readInt(MIN_D,MAX_D);
        inf.readSpace();
        int A = inf.readInt(MIN_A,N);
        inf.readSpace();
        int B = inf.readInt(MIN_B,N);
        inf.readEoln();

		assert(A < B);
    }

    for(int i = 0; i < Q; i++){
        int E = inf.readInt(MIN_E,MAX_E);
        inf.readSpace();
        int S = inf.readInt(MIN_S,N);
        inf.readSpace();
        int T = inf.readInt(MIN_T,N);
        inf.readEoln();
    }

	inf.readEof();
}

