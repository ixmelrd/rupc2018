// g++ -std=c++11 a.cpp
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>	
#include<map>
#include<set>
#include<utility>
#include<cmath>
#include<random>
#include<cstring>
#include<queue>
#include<stack>
#include<bitset>
#include<cstdio>
#include<sstream>
#include<iomanip>
#include<assert.h>
#include<typeinfo>
#define loop(i,a,b) for(int i=a;i<b;i++) 
#define rep(i,a) loop(i,0,a)
#define pb push_back
#define all(in) in.begin(),in.end()
#define shosu(x) fixed<<setprecision(x)
using namespace std;
//kaewasuretyuui
typedef long long ll;
//#define int ll
typedef int Def;
typedef pair<Def,Def> pii;
typedef vector<Def> vi;
typedef vector<vi> vvi;
typedef vector<pii> vp;
typedef vector<vp> vvp;
typedef vector<string> vs;
typedef vector<double> vd;
typedef vector<vd> vvd;
typedef pair<Def,pii> pip;
typedef vector<pip>vip;
#define mt make_tuple
typedef tuple<int,int,int,int> tp;
typedef vector<tp> vt;
template<typename A,typename B>bool cmin(A &a,const B &b){return a>b?(a=b,true):false;}
template<typename A,typename B>bool cmax(A &a,const B &b){return a<b?(a=b,true):false;}
//template<class C>constexpr int size(const C &c){return (int)c.size();}
//template<class T,size_t N> constexpr int size(const T (&xs)[N])noexcept{return (int)N;}
const double PI=acos(-1);
const double EPS=1e-7;
Def inf = sizeof(Def) == sizeof(long long) ? 2e18 : 1e9+10;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
set<pii>data;
void add(pii a){
	for(auto it=data.begin();it!=data.end();it++){
		if(it->first<=a.first&&a.second<=it->second)return;
		if(a.first<=it->second&&it->second<=a.second){
			a.first=min(a.first,it->first);
			data.erase(it++);
			it--;
		}
		if(a.first<=it->first&&it->first<=a.second){
			a.second=max(a.second,it->second);
			data.erase(it++);
			it--;
		}
	}
	data.insert(a);
}
bool query(pii a){
	bool h=false;
	auto it=data.upper_bound({a.first,inf});
	if(it!=data.begin()){
		it--;
		if(it->first<=a.first&&a.second<=it->second)h=true;
	}
	return h;
}
int main(){
	int n,m,q;
	cin>>n>>m>>q;

	vip in(m);
	rep(i,m)cin>>in[i].first>>in[i].second.first>>in[i].second.second;
	sort(all(in));

	vt que(q);
	rep(i,q){
		int a,b,t;
		cin>>t>>a>>b;
		que[i]=tp(t,a,b,i);
	}
	sort(all(que));

	int r=0;
	vs out(q,"No");
	rep(i,q){
		int t,x,y,w;
		tie(t,x,y,w)=que[i];
		while(r<m&&in[r].first<t)add(in[r++].second);
		if(query({x,y}))out[w]="Yes";
	}
	rep(i,q)cout<<out[i]<<endl;
}





