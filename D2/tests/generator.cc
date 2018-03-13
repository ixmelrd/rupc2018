#include "./constraints.hpp"
#include "./testlib.h"
#include <deque>
#include <iomanip>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

#define loop(i, a, n) for (int i = a; i < (n); i++)
#define rep(i, n) loop(i, 0, n)

void output(const int N, const int M, const int s, const int t,
            const vector<int> &a, const vector<int> &b, const vector<int> &c, const vector<int> &d,
            const string &prefix, const int num = 0) {
  ostringstream os;
  os << prefix << '_' << setw(2) << setfill('0') << num << ".in";
  ofstream ofs(os.str());
  ofs << N << ' ' << M << ' ' << s << ' ' << t << '\n';
  rep(i, M) ofs << a[i] << ' ' << b[i] << ' ' << c[i] << ' ' << d[i] << '\n';
  ofs.close();
}

void gen_random(const int N, const int M, int &s, int &t, vector<int> &a, vector<int> &b, vector<int> &c) {
  a.reserve(M);
  b.reserve(M);
  c.reserve(M);
  s = rnd.next(MIN_s, N);
  t = rnd.next(MIN_t, N - 1);
  if (s <= t) t++;
  {
    deque<int> vertices;
    for (int v = 1; v <= N; v++) {
      if (v == s || v == t) continue;
      vertices.emplace_back(v);
    }
    shuffle(vertices.begin(), vertices.end());
    int hops = rnd.next(1, min(N - 1, M));
    vertices.resize(hops - 1);
    vertices.emplace_front(s);
    vertices.emplace_back(t);
    loop(i, 1, hops + 1) {
      array<int, 3> r;
      r[0] = vertices[i - 1];
      r[1] = vertices[i];
      r[2] = rnd.next(MIN_abc, N);
      sort(r.begin(), r.end());
      a.emplace_back(r[0]);
      b.emplace_back(r[1]);
      c.emplace_back(r[2]);
    }
  }
  while (a.size() < M) {
    array<int, 3> r;
    rep(j, 3) r[j] = rnd.next(MIN_abc, N);
    sort(r.begin(), r.end());
    a.emplace_back(r[0]);
    b.emplace_back(r[1]);
    c.emplace_back(r[2]);
  }
}

void case_50_small() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, 10);
    int M = rnd.next(MIN_M, 11);
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    d.resize(M);
    for (int &x : d) x = rnd.next(MIN_d, 10);
    output(N, M, s, t, a, b, c, d, "50_small", num);
  }
}

void case_51_large() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = rnd.next(MIN_M, MAX_M);
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "51_large", num);
  }
}

void case_52_Mmin() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = MIN_M;
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "52_Mmin", num);
  }
}

void case_52_Nmin() {
  rep(num, 10) {
    int N = MIN_N;
    int M = rnd.next(MIN_M, MAX_M);
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "52_Nmin", num);
  }
}

void case_52_Nmin_Mmin() {
  rep(num, 10) {
    int N = MIN_N;
    int M = MIN_M;
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "52_Nmin_Mmin", num);
  }
}

void case_53_Mmax() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = MAX_M;
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "53_Mmax", num);
  }
}

void case_53_Nmax() {
  rep(num, 10) {
    int N = MAX_N;
    int M = rnd.next(MIN_M, MAX_M);
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "53_Nmax", num);
  }
}

void case_53_Nmax_Mmax() {
  rep(num, 10) {
    int N = MAX_N;
    int M = MAX_M;
    int s, t;
    vector<int> a, b, c, d(M);
    gen_random(N, M, s, t, a, b, c);
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "53_Nmax_Mmax", num);
  }
}

void case_60_complete_graph() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, static_cast<int>(sqrt(MAX_M * 2)));
    int M = N * (N - 1) / 2;
    int s = rnd.next(MIN_s, N);
    int t = rnd.next(MIN_t, N - 1);
    if (s <= t) t++;
    vector<int> a, b, c, d(M);
    a.reserve(M);
    b.reserve(M);
    a.reserve(M);
    for (int v = 1; v <= N - 1; v++) {
      for (int u = v + 1; u <= N; u++) {
        array<int, 3> r;
        r[0] = v;
        r[1] = u;
        r[2] = rnd.next(MIN_abc, N);
        sort(r.begin(), r.end());
        a.emplace_back(r[0]);
        b.emplace_back(r[1]);
        c.emplace_back(r[2]);
      }
    }
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "60_complete_graph", num);
  }
}

void case_60_path_graph() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = N - 1;
    int s = rnd.next(MIN_s, N);
    int t = rnd.next(MIN_t, N - 1);
    if (s <= t) t++;
    vector<int> a, b, c, d(M);
    a.reserve(M);
    b.reserve(M);
    a.reserve(M);
    for (int v = 1; v <= N - 1; v++) {
      array<int, 3> r;
      r[0] = v;
      r[1] = v + 1;
      r[2] = rnd.next(MIN_abc, N);
      sort(r.begin(), r.end());
      a.emplace_back(r[0]);
      b.emplace_back(r[1]);
      c.emplace_back(r[2]);
    }
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "60_path_graph", num);
  }
}

void case_60_star_graph() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = N - 1;
    int s = rnd.next(MIN_s, N);
    int t = rnd.next(MIN_t, N - 1);
    if (s <= t) t++;
    vector<int> a, b, c, d(M);
    a.reserve(M);
    b.reserve(M);
    a.reserve(M);
    int center = rnd.next(1, N);
    for (int v = 1; v <= N; v++) {
      if (v == center) continue;
      array<int, 3> r;
      r[0] = v;
      r[1] = center;
      r[2] = rnd.next(MIN_abc, N);
      sort(r.begin(), r.end());
      a.emplace_back(r[0]);
      b.emplace_back(r[1]);
      c.emplace_back(r[2]);
    }
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "60_star_graph", num);
  }
}

void case_60_tree_graph() {
  rep(num, 10) {
    int N = rnd.next(MIN_N, MAX_N);
    int M = N - 1;
    int s = rnd.next(MIN_s, N);
    int t = rnd.next(MIN_t, N - 1);
    if (s <= t) t++;
    vector<int> a, b, c, d(M);
    a.reserve(M);
    b.reserve(M);
    a.reserve(M);
    for (int v = 2; v <= N; v++) {
      array<int, 3> r;
      r[0] = v;
      r[1] = rnd.next(1, v - 1);
      r[2] = rnd.next(MIN_abc, N);
      sort(r.begin(), r.end());
      a.emplace_back(r[0]);
      b.emplace_back(r[1]);
      c.emplace_back(r[2]);
    }
    for (int &x : d) x = rnd.next(MIN_d, MAX_d);
    output(N, M, s, t, a, b, c, d, "60_tree_graph", num);
  }
}

void case_61_overflow() {
  rep(num, 10) {
    int N = rnd.next(MAX_N - 10, MAX_N);
    int M = N - 1;
    int s = 1, t = N;
    vector<int> a, b, c, d(M);
    a.reserve(M);
    b.reserve(M);
    a.reserve(M);
    for (int v = 1; v <= N - 1; v++) {
      a.emplace_back(v);
      b.emplace_back(v + 1);
      c.emplace_back(v + 1);
    }
    for (int &x : d) x = rnd.next(MAX_d - 10, MAX_d);
    output(N, M, s, t, a, b, c, d, "61_overflow", num);
  }
}

int main() {
  rnd.setSeed(time(nullptr) + getpid());
  case_50_small();
  case_51_large();
  case_52_Mmin();
  case_52_Nmin();
  case_52_Nmin_Mmin();
  case_53_Mmax();
  case_53_Nmax();
  case_53_Nmax_Mmax();
  case_60_complete_graph();
  case_60_path_graph();
  case_60_star_graph();
  case_60_tree_graph();
  case_61_overflow();
}
