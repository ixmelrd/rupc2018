#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
#define INF 1e10
#define int long long
using namespace std;

typedef int Weight;
struct Edge{
  int src;int dst;
  Weight wei;
  Edge(int s=0,int d=0,Weight w=0):
    src(s),dst(d),wei(w){}
};

using Graph = vector<vector<Edge>>;

vector<int> Dij(Graph&g,int s){
    using state = pair<int,int>;//コストの総和、どこから見ているのか
    priority_queue<state,vector<state>,greater<state>> pq;
    vector<int> dis(g.size(),INF);
    dis[s]=0;
    pq.push(state(0,s));
    while(!pq.empty()){
      int d=pq.top().first;
      int v=pq.top().second;
      pq.pop();
      if(dis[v]<d)continue;
      for(int i=0;i<g[v].size();i++){
        Edge &e=g[v][i];
        if(dis[e.dst]>dis[v]+e.wei){
          dis[e.dst]=dis[v]+e.wei;
          pq.push(state(dis[e.dst],e.dst));
        }
      }
    }
    return dis;
}

signed main(){
  int n,m,s,t;
  cin>>n>>m>>s>>t;
  s--;t--;
  Graph g(n);
  for(int i=0;i<m;i++){
    int a,b,c,d;
    cin>>a>>b>>c>>d;
    a--;b--;c--;
    g[a].emplace_back(a,b,d);
    g[b].emplace_back(b,a,d);
    g[b].emplace_back(b,c,d);
    g[c].emplace_back(c,b,d);
    g[c].emplace_back(c,a,d);
    g[a].emplace_back(a,c,d);
  }

  vector<int> ans=Dij(g,s);
  cout<<ans[t]<<endl;

  return 0;
}
