#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

using namespace std;

int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i=0;i<n;i++)cin>>a[i];
  vector<int> b=a;
  reverse(b.begin(),b.end());
  vector<int> ans;
  int flag=1;
  multiset<int> na,nb;
  for(int i=0;i<n;i++){
    if(a[i]==b[i]){
      if(na.empty()&&nb.empty())ans.push_back(i+1);
    }else{
      if(na.empty()){
        na.insert(b[i]);
        nb.insert(a[i]);
      }else{
        int fa=0,fb=0;
        if(na.find(a[i])!=na.end())fa=1;
        if(nb.find(b[i])!=nb.end())fb=1;
      //  cout<<i<<' '<<fa<<' '<<fb<<endl;
        if(fa)na.erase(na.find(a[i]));
        else nb.insert(a[i]);
        if(fb)nb.erase(nb.find(b[i]));
        else na.insert(b[i]);
      }
      if(na.empty()&&nb.empty())ans.push_back(i+1);
    //   cout<<i<<endl;
    //   for(auto x:na){
    //     cout<<x<<' ';
    //   }
    //   cout<<endl;
    //   for(auto x:nb){
    //     cout<<x<<' ';
    //   }cout<<endl;
    // }
    // cout<<endl;
    }
  }
  for(int i=0;i<ans.size();i++){
    if(i)cout<<' ';
    cout<<ans[i];
  }
  cout<<endl;


  return 0;
}
