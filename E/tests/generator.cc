#include "./constraints.hpp"
#include "./testlib.h"
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define loop(i, a, n) for (int i = a; i < (n); i++)
#define rep(i, n) loop(i, 0, n)

void output(const int N, const int M, const int s, const int t,
            const vector<int> &a, const vector<int> &b, const vector<int> &c,
            const string &prefix, const int num = 0) {
  ostringstream os;
  os << prefix << '_' << setw(2) << setfill('0') << num << ".in";
  ofstream ofs(os.str());
  ofs << N << ' ' << M << ' ' << s << ' ' << t << '\n';
  rep(i, N) ofs << a[i] << ' ' << b[i] << c[i] << '\n';
  ofs.close();
}

void gen_random(const int N, const int M, int &s, int &t, vector<int> &a, vector<int> &b, vector<int> &c) {
  a.resize(M);
  b.resize(M);
  c.resize(M);
  rep(i, M) {
    a[i] = rnd.next(MIN_a, N);
    b[i] = rnd.next(MIN_b, N);
    c[i] = rnd.next(MIN_c, N);
  }
  s = rnd.next(MIN_s, N);
  t = rnd.next(MIN_t, N - 1);
  if (s <= t) t++;
}

void case_50_small() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, 10);
    int M = rnd.next(MIN_M, 20);
    int s, t;
    vector<int> a, b, c;
    gen_random(N, M, s, t, a, b, c);
    output(N, M, s, t, a, b, c, "51_large", num);
  }
}

void case_51_large() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = rnd.next(MIN_M, MAX_M);
    int s, t;
    vector<int> a, b, c;
    gen_random(N, M, s, t, a, b, c);
    output(N, M, s, t, a, b, c, "51_large", num);
  }
}

void case_52_Mmin() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = MIN_M;
    int s, t;
    vector<int> a, b, c;
    gen_random(N, M, s, t, a, b, c);
    output(N, M, s, t, a, b, c, "51_large", num);
  }
}

void case_52_Nmin() {
  rep(num, 10) {
    int N = MIN_N;
    int M = rnd.next(MIN_M, MAX_M);
    int s, t;
    vector<int> a, b, c;
    gen_random(N, M, s, t, a, b, c);
    output(N, M, s, t, a, b, c, "51_large", num);
  }
}

int main() {
  rnd.setSeed(time(0) + getpid());
  case_50_small();
  case_51_large();
  case_52_Mmin();
  case_52_Nmin();
  // case_53_Mmax();
  // case_53_Nmax();
  // case_53_Nmax_Mmax();
}
