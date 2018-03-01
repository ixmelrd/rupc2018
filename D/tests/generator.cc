#include "./constraints.hpp"
#include "./testlib.h"
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define loop(i, a, n) for (int i = a; i < (n); i++)
#define rep(i, n) loop(i, 0, n)

void output(const int N, const int M, const vector<int> &a, const string &prefix, const int num = 0) {
  ostringstream os;
  os << prefix << '_' << setw(2) << setfill('0') << num << ".in";
  ofstream ofs(os.str());
  ofs << N << ' ' << M << '\n';
  rep(i, N) ofs << a[i] << " \n"[i == N - 1];
  ofs.close();
}

void case_50_small() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, 10);
    int M = rnd.next(MIN_M, N);
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, 20);
    output(N, M, a, "50_small", num);
  }
}

void case_51_large() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = rnd.next(MIN_M, N);
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "51_large", num);
  }
}

void case_52_Mmin() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = MIN_M;
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "52_Mmin", num);
  }
}

void case_52_Nmin() {
  rep(num, 10) {
    int N = MIN_N;
    int M = rnd.next(MIN_M, N);
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "52_Nmin", num);
  }
}

void case_53_Mmax() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = N;
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "53_Mmax", num);
  }
}

void case_53_Nmax() {
  rep(num, 10) {
    int N = MAX_N;
    int M = rnd.next(MIN_M, N);
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "53_Nmax", num);
  }
}

void case_53_Nmax_Mmax() {
  rep(num, 10) {
    int N = MAX_N;
    int M = N;
    vector<int> a(N);
    for (int &x : a) x = rnd.next(MIN_a, MAX_a);
    output(N, M, a, "53_Nmax_Mmax", num);
  }
}

void case_60_constant() {
  rep(num, 10) {
    int N = num == 0 ? 79 : rnd.next(MIN_N, MAX_N);
    int M = num == 0 ? 1 : rnd.next(MIN_M, N);
    vector<int> a(N, rnd.next(MIN_a, MAX_a));
    output(N, M, a, "60_constant", num);
  }
}

int main() {
  rnd.setSeed(time(nullptr) + getpid());
  case_50_small();
  case_51_large();
  case_52_Mmin();
  case_52_Nmin();
  case_53_Mmax();
  case_53_Nmax();
  case_53_Nmax_Mmax();
  case_60_constant();
}
