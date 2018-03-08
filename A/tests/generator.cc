#include "./constraints.hpp"
#include "./testlib.h"
#include <iomanip>
#include <numeric>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define loop(i, a, n) for (int i = a; i < (n); i++)
#define rep(i, n) loop(i, 0, n)

void output(const int N, const vector<int> &a, const string &prefix, const int num = 0) {
  ostringstream os;
  os << prefix << '_' << setw(2) << setfill('0') << num << ".in";
  ofstream ofs(os.str());
  ofs << N << '\n';
  rep(i, N) ofs << a[i] << " \n"[i == N - 1];
  ofs.close();
}

void case_50_small() {
  vector<int> a(MAX_N);
  iota(a.begin(), a.end(), 1);
  rep(num, 10) {
    int N = rnd.next(MIN_N, 10);
    shuffle(a.begin(), a.end());
    output(N, a, "50_small", num);
  }
}

void case_51_large() {
  vector<int> a(MAX_N);
  iota(a.begin(), a.end(), 1);
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    shuffle(a.begin(), a.end());
    output(N, a, "51_large", num);
  }
}

void case_52_Nmin() {
  vector<int> a(MAX_N);
  iota(a.begin(), a.end(), 1);
  rep(num, 10) {
    int N = MIN_N;
    shuffle(a.begin(), a.end());
    output(N, a, "52_Nmin", num);
  }
}

void case_53_Nmax() {
  vector<int> a(MAX_N);
  iota(a.begin(), a.end(), 1);
  rep(num, 10) {
    int N = MAX_N;
    shuffle(a.begin(), a.end());
    output(N, a, "53_Nmax", num);
  }
}


int main() {
  rnd.setSeed(time(nullptr) + getpid());
  case_50_small();
  case_51_large();
  case_52_Nmin();
  case_53_Nmax();
}
