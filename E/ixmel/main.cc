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
ll dp[100010][5][2][2];
int main(){
	dp[0][0][0][0]=1;
	
	string s,t="51*3";
	cin>>s;
	int n=s.size();
	
	rep(i,n)rep(j,5)rep(k,2)rep(l,2)rep(x,10){
		if(!k&&s[i]-'0'<x)continue;
		int I=i+1,J=j,K=k||(x<s[i]-'0'),L=j==2&&x==5;
		if(J!=4)
			if(J==2||t[J]-'0'==x)J++;
			else if(l&&x==1)J=2;
			else if(x==5)J=1;
			else J=0;
		dp[I][J][K][L]+=dp[i][j][k][l];
	}
	cout<<dp[n][4][0][0]+dp[n][4][1][0]<<endl;
}





