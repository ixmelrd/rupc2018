#include<stdio.h>
#include "./testlib.h"
#include "./constraints.hpp"
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <iomanip>
#include <iostream>
#include <vector>
#include <random>

using namespace std;

#define loop(i, a, n) for (int i = a; i < (n); i++)
#define rep(i, n) loop(i, 0, n)

void output(const int N, const vector<int> &A, const string &prefix, const int num = 0) {
	ostringstream os;
	os << prefix << '_' << setw(2) << setfill('0') << num << ".in";
	ofstream ofs(os.str());
	ofs << N << '\n';
	rep (i,A.size()) {
		if(i) ofs << ' ';
		ofs << A[i];
	}
	ofs << '\n';
	ofs.close();
}

vector<int> getArray(int N, int max_a){
	random_device seed_gen;
	mt19937 engine(seed_gen());

	vector<int> res(N,rnd.next(MIN_A, max_a));
	int l = 0, r = N - 1;
	while(r - l > 1){
		int size = rnd.next(1, (r - l + 1) / 2);

		vector<int> a(size);
		rep(j,size) a[j] = rnd.next(MIN_A, max_a);

		rep(j,size){
			res[l++] = a[j];
		}
		shuffle(a.begin(), a.end(), engine);
		rep(j,size){
			res[r--] = a[j];
		}
	}
	return res;
}

void case_50_ramdom_small() {
	rep(num, 10) {
		int N = rnd.next(MIN_N, 20);
		output(N, getArray(N, 20), "50_ramdom_small", num);
	}
}

void case_51_ramdom_large() {
	rep(num, 10) {
		int N = rnd.next(MIN_N, MAX_N);
		output(N, getArray(N, MAX_A), "50_ramdom_large", num);
	}
}

void case_52_minimum() {
	int N = 1;
	vector<int> A = {rnd.next(MIN_A, MAX_A)};
	output(N, A, "52_minimum", 0);
}

void case_53_maximum() {
	rep(num, 10) {
		int N = MAX_N;
		output(N, getArray(N, MAX_A), "52_maximum", num);
	}
}

void case_54_eaten() {
	rep(num, 5) {
		int N = rnd.next(MIN_N, MAX_N);
		vector<int> A = getArray(N, MAX_A);
		A[rnd.next(0, N - 1)] = rnd.next(MIN_A, MAX_A);
		output(N, A, "54_eaten", num);
	}
}

void case_60_challenge() {
	int N = MAX_N;
	vector<int> A(N, rnd.next(MIN_A, MAX_A));
	output(N, A, "60_challenge", 0);
}

void case_61_challenge() {
	rep(num, 5) {
		int N = MAX_N;
		output(N, getArray(N, 3), "61_challenge", num);
	}
}

int main(){
	rnd.setSeed(time(0)+getpid());

	case_50_ramdom_small();
	case_51_ramdom_large();
	case_52_minimum();
	case_53_maximum();
	case_54_eaten();		// getArrayで作った数列から、ある一箇所だけランダムに選んだ数値に置き換え
	
	case_60_challenge();	// 全部同じ数値
	case_61_challenge();	// {1,2,3}の数値しか出てこないケース
}
