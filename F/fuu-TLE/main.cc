#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n,m,q;
  cin>>n>>m>>q;
  vector<pair<int,pair<int,int>>> dab(m);
  for(int i=0;i<m;i++){
    int d,a,b;
    cin>>d>>a>>b;
    a--;b--;
    dab[i]=make_pair(d,make_pair(a,b));
  }
  sort(dab.begin(),dab.end());
  // for(auto x:dab){
  //   cout<<x.first<<' ';
  // }
  // cout<<endl;

  vector<pair<pair<int,int>,pair<int,int>>> est(q);
  for(int i=0;i<q;i++){
    int e,s,t;
    cin>>e>>s>>t;
    s--;t--;
    est[i]=make_pair(make_pair(e,i),make_pair(s,t));
  }
  sort(est.begin(),est.end());
  vector<int> ans(q);
  vector<int> path(3*n);
  int l=0;
  for(int i=0;i<q;i++){
    int S=est[i].second.first;
    int T=est[i].second.second;
    //cout<<'a'<<' '<<est[i].first.first<<' '<<dab[l].first<<endl;
    while(l<m&&est[i].first.first>dab[l].first){
        //cout<<'a'<<' '<<est[i].first.first<<' '<<dab[l].first<<endl;
      for(int j=2*dab[l].second.first;j<2*dab[l].second.second+1;j++){
        path[j]++;
      }
      //cout<<2*dab[l].second.first<<' '<<2*dab[l].second.second+1<<endl;
      l++;
    }
    int flag=true;
    if(S>=T)ans[est[i].first.second]=1;
    for(int j=2*S;j<2*T+1;j++){
      if(path[j]==0){
        flag=false;
        break;
      }
    }
    if(flag)ans[est[i].first.second]=1;
    // for(auto x:path)cout<<x<<' ';
    // cout<<endl;
  }

  for(int i=0;i<q;i++){
    cout<<(ans[i]==1?"Yes":"No")<<endl;
  }

  return 0;
}
