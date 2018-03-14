#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <vector>
#define loop(i, a, n) for (int i = (a); i < (n); i++)
#define rep(i, n) loop(i, 0, n)
using namespace std;

using Weight = int;
struct Edge {
  int src, dst;
  Weight weight;
  Edge(const int s = 0, const int d = 0, const Weight w = 0) : src(s), dst(d), weight(w) {}
};

using Edges = std::vector<Edge>;
using Array = std::vector<Weight>;
using Matrix = std::vector<Array>;

class Graph {
  std::vector<Edges> g;
  using iterator = std::vector<Edges>::iterator;
  using const_iterator = std::vector<Edges>::const_iterator;

public:
  Graph(const int size = 0) : g(size) {}
  size_t size() const { return g.size(); }
  const Edges &operator[](const int i) const { return g[i]; }
  void addArc(const int src, const int dst, const Weight w = 1) { g[src].emplace_back(src, dst, w); }
  void addEdge(const int node1, const int node2, const Weight w = 1) {
    addArc(node1, node2, w);
    addArc(node2, node1, w);
  }
  iterator begin() { return g.begin(); }
  const_iterator begin() const { return g.begin(); }
  iterator end() { return g.end(); }
  const_iterator end() const { return g.end(); }
};

int main() {
  int n, m, q;
  cin >> n >> m >> q;
  multimap<int, int> w;
  vector<int> d(m + q), a(m + q), b(m + q);
  rep(i, m + q) cin >> d[i] >> a[i] >> b[i];
  rep(i, m + q) w.emplace(d[i] << 1 | (i < m), i);
  Graph g(n);
  loop(i, 1, n) g.addArc(i, i - 1);
  vector<int> ans(q);
  for (auto &p : w) {
    int i = p.second;
    if (i < m) {
      g.addArc(a[i] - 1, b[i] - 1);
    } else {
      vector<int> done(n);
      queue<int> que;
      for (que.emplace(a[i] - 1); que.size(); que.pop()) {
        int u = que.front();
        if (u == b[i] - 1) {
          ans[i - m] = true;
          break;
        }
        if (done[u]) continue;
        done[u] = true;
        for (auto &e : g[u]) que.emplace(e.dst);
      }
    }
  }
  for (auto &x : ans) cout << (x ? "Yes" : "No") << endl;
}
