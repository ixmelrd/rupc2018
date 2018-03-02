#include <algorithm>
#include <iostream>
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
  Graph g(n);
  loop(i, 1, n) g.addArc(i, i - 1);
  vector<int> ans(q);
  for (auto &p : v) {
    if (p.type == 0) {
      if (p.b < p.a) swap(p.a, p.b);
      g.addArc(p.a, p.b);
    } else {
      vector<int> done(n);
      queue<int> que;
      done[p.a] = true;
      for (que.emplace(p.a); que.size(); que.pop()) {
        int u = que.front();
        if (u == p.b) {
          ans[p.id] = true;
          break;
        }
        if (done[u]) continue;
        done[u] = true;
        for (auto &e : g[u]) que.emplace(e.dst);
      }
    }
  }
  for(auto &x: ans) cout << (x ? "Yes" : "No") << endl;
}
