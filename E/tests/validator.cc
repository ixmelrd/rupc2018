#include "./testlib.h"
#include "./constraints.hpp"
#include <cassert>
#include <queue>
#include <iostream>
using namespace std;

vector<int> g[MAX_N];

bool isConnected(int n, int s, int t){
    bool isVisited[MAX_N] = {0};
    queue<int> q;

    isVisited[s] = 1;
    q.push(s);

    int u;
    while(not q.empty()){
        u = q.front(); q.pop();
        for(int i = 0; i < (int)g[u].size(); i++){
            int next = g[u][i];
            if(isVisited[next] == 0){
                q.push(next);
                isVisited[next] = 1;
            }
        }
    }
    return isVisited[t];
}

int main(){
	registerValidation();

    int N = inf.readInt(MIN_N, MAX_N);
    inf.readSpace();
    int M = inf.readInt(MIN_M, MAX_M);
    inf.readSpace();
	int s = inf.readInt(1, N);
    inf.readSpace();
	int t = inf.readInt(1, N);
    inf.readEoln();

	assert(s != t);

    for(int i = 0; i < M; i++){
        int a = inf.readInt(1,N);
        inf.readSpace();
        int b = inf.readInt(1,N);
        inf.readSpace();
        int c = inf.readInt(1,N);
        inf.readEoln();

		assert(a <= b);
		assert(b <= c);

        a--; b--; c--;
        g[a].emplace_back(b);
        g[b].emplace_back(a);

        g[a].emplace_back(c);
        g[c].emplace_back(a);

        g[b].emplace_back(c);
        g[c].emplace_back(b);
    }

    assert(isConnected(N, s - 1, t - 1));

	inf.readEof();
}
