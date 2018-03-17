#include <iostream>
#include <vector>
#include <queue>
#include<tuple>
#include<algorithm>
#include<climits>
using namespace std;

#define int long long

const int INF = (1LL << 60);

class Edge{
	public:
		int to, cost;
		Edge(int to, int cost) : to(to) ,cost(cost) {}
};

class Node{
	public:
		int dis;
		bool isUsed;
		Node(){
			this->dis = INF;
			this->isUsed = 0;
		}
};

typedef vector<vector<Edge>> AdjList;

int dijkstra(AdjList g, int start, int goal, int n){
    vector<Node> node(n);
    priority_queue<int, vector<pair<int, int>>, greater<pair<int, int>>> q;

    q.push(make_pair(0, start));
    node[start].dis = 0;

    pair<int, int> u;
    while(not q.empty()){
        u = q.top(); q.pop();
        int current = u.second;
        node[current].isUsed = 1;

        for(int i = 0; i < g[current].size(); i++){
            int next = g[current][i].to;
            if(node[next].isUsed == 0){
                if(node[next].dis > node[current].dis + g[current][i].cost){
                    node[next].dis = node[current].dis + g[current][i].cost;
                    q.push(make_pair(node[next].dis, next));

                }
            }
        }
    }
    return node[goal].dis;
}

void addEdge(AdjList& g, int from, int to, int cost){
	g[from].emplace_back(to, cost);
	g[to].emplace_back(from, cost);
}

signed main() {
	int n, m, s, t;
	cin >> n >> m >> s >> t;

	AdjList g(n);
	for (int i = 0; i < m; i++) {
		int a, b, c, d;
		cin >> a >> b >> c >> d;
		a--; b--; c--;
		addEdge(g, a, b, d);
		addEdge(g, a, c, d);
		addEdge(g, b, c, d);
	}

	cout << dijkstra(g, s - 1, t - 1, n) << endl;
}
