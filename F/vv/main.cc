#include <algorithm>
#include <iostream>
#include <map>
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

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  multimap<int, int> w;
  vector<int> d(m + q), a(m + q), b(m + q);
  rep(i, m + q) cin >> d[i] >> a[i] >> b[i];
  rep(i, m + q) w.emplace(d[i] << 1 | (i < m), i);
  vector<int> ans(q);
  RangeUnionFind ruf(n);
  for (auto &p : w) {
    int i = p.second;
    if (i < m) {
      ruf.unite(a[i] - 1, b[i]);
    } else {
      ans[i - m] = b[i] <= a[i] || ruf.same(a[i] - 1, b[i] - 1);
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
