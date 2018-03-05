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
// #define mt make_tuple
//typedef tuple<pii,int,int> tp;
//typedef vector<tp> vt;
template<typename A,typename B>bool cmin(A &a,const B &b){return a>b?(a=b,true):false;}
template<typename A,typename B>bool cmax(A &a,const B &b){return a<b?(a=b,true):false;}
//template<class C>constexpr int size(const C &c){return (int)c.size();}
//template<class T,size_t N> constexpr int size(const T (&xs)[N])noexcept{return (int)N;}
const double PI=acos(-1);
const double EPS=1e-7;
Def inf = sizeof(Def) == sizeof(long long) ? 2e18 : 1e9+10;
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int main(){
	int n;
	cin>>n;
	vi in(n);
	rep(i,n)cin>>in[i];
	vi t=in;
	sort(all(t));
	t.erase(unique(all(t)),t.end());
	rep(i,n)in[i]=lower_bound(all(t),in[i])-t.begin();
	
	int N=t.size(),out=0,co=N;
	vi a(N),b(N);
	rep(i,n){
		if(a[in[i]]==b[in[i]])co--;
		a[in[i]]++;
		if(a[in[i]]==b[in[i]])co++;

		if(a[in[n-1-i]]==b[n-1-in[i]])co--;
		b[in[n-1-i]]++;
		if(a[in[n-1-i]]==b[in[n-1-i]])co++;
		
		if(co==N)out++;
	}
	cout<<out<<endl;
}





