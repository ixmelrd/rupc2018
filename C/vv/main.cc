#include <algorithm>
#include <iostream>
#include <map>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

template<typename Monoid> class SegTree {
  using T = typename Monoid::value_type;

  Monoid m;
  std::vector<T> tree; // 1-indexed
  int size = 1;

public:
  SegTree(const int n = 0) {
    while (size < n) size *= 2;
    tree.assign(size * 2, m.id());
  }

  SegTree(const int n, const T &x) {
    while (size < n) size *= 2;
    tree.assign(size * 2, x);
    for (int i = size - 1; i >= 1; i--) tree[i] = m(tree[i * 2], tree[i * 2 + 1]);
  }

  T fold(int l, int r) { // [l, r)
    T accl = m.id(), accr = m.id();
    for (l += size, r += size; l < r; l /= 2, r /= 2) {
      if (l & 1) accl = m(accl, tree[l++]);
      if (r & 1) accr = m(tree[--r], accr);
    }
    return m(accl, accr);
  }

  void update(int i, const T &x) {
    tree[i += size] = x;
    while (i /= 2) tree[i] = m(tree[i * 2], tree[i * 2 + 1]);
  }

  const T &operator[](int i) const { return tree[i + size]; }
};

template<typename T = bool> struct anyMonoid {
  using value_type = T;
  constexpr value_type id() { return false; }
  constexpr value_type operator()(const value_type &a, const value_type &b) { return a | b; }
};

std::vector<int> compressByOrd(const std::vector<int> &v) {
  size_t n = v.size();
  int k = 0;
  std::map<int, int> m;
  std::vector<int> w(v.begin(), v.end());
  std::sort(w.begin(), w.end());
  rep(i, n) if (!m.count(w[i])) m[w[i]] = k++;
  rep(i, n) w[i] = m[v[i]];
  return w;
}

int main() {
  int n;
  cin >> n;
  vector<int> a(n);
  for (int &x : a) cin >> x;
  vector<int> b = compressByOrd(a);
  vector<int> ans;
  ans.reserve(n);
  SegTree<anyMonoid<int>> st(n);
  rep(i, n) {
    st.update(b[i], st[b[i]] + 1);
    st.update(b[n - 1 - i], st[b[n - 1 - i]] - 1);
    if (st.fold(0, n) == 0) ans.emplace_back(i + 1);
  }
  int m = static_cast<int>(ans.size());
  rep(i, m) cout << ans[i] << " \n"[i == m - 1];
}
