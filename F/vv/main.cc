#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
#define all(v) (v).begin(), (v).end()
using namespace std;

template<typename T> class RangeUpdateSegTree {
  int size = 1;
  size_t time = 1;
  std::vector<pair<size_t, T>> tree; // 1-indexed

public:
  RangeUpdateSegTree(const int n = 0) {
    while (size < n) size *= 2;
    tree.resize(size * 2);
  }

  RangeUpdateSegTree(const int n, const T &x) {
    while (size < n) size *= 2;
    tree.assign(size * 2, {0, x});
  }

  template<typename InputIterator> RangeUpdateSegTree(InputIterator first, InputIterator last) {
    size_t n = std::distance(first, last);
    while (size < n) size *= 2;
    tree.resize(size * 2);

    auto result = tree.begin() + size;
    while (first != last) {
      result->second = *first;
      ++result, ++first;
    }
  }

  // [l, r)
  void update(int l, int r, const T &x) {
    for (l += size, r += size; l < r; l /= 2, r /= 2) {
      if (l & 1) tree[l++] = {time, x};
      if (r & 1) tree[--r] = {time, x};
    }
    time++;
  }

  const T operator[](int i) const {
    pair<size_t, T> p = tree[i += size];
    while (i /= 2) p = max(p, tree[i]);
    return p.second;
  }
};

class RangeUnionFind {
  RangeUpdateSegTree<int> rust;

public:
  RangeUnionFind(const int n) {
    vector<int> ufInit(n);
    iota(all(ufInit), 0);
    rust = RangeUpdateSegTree<int>(all(ufInit));
  }

  int root(int x) {
    int a = rust[x];
    if (a == x) return x;
    int b = root(a);
    rust.update(x, x + 1, b);
    return b;
  }

  bool same(const int a, const int b) { return root(a) == root(b); }

  void unite(int a, int b) { // unite [a, b)
    int r = root(a);
    if (a == b) return;
    rust.update(a, b, r);
  }
};

struct query {
  int id, type, d, a, b;
  query(const int id, const int type, const int d, const int a, const int b) : id(id), type(type), d(d), a(a), b(b) {}
};

bool operator<(const query &a, const query &b) { return a.d < b.d; }

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  vector<query> v;
  v.reserve(m + q);
  rep(i, m) {
    int d, a, b;
    cin >> d >> a >> b;
    v.emplace_back(0, 0, d, --a, --b);
  }
  rep(i, q) {
    int e, s, t;
    cin >> e >> s >> t;
    v.emplace_back(i, 1, e, --s, --t);
  }
  sort(v.begin(), v.end());
  vector<int> ans(q);
  RangeUnionFind ruf(n);
  for (auto &p : v) {
    if (p.type == 0) {
      ruf.unite(p.a, p.b + 1);
    } else {
      ans[p.id] = p.b <= p.a || ruf.same(p.a, p.b);
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
