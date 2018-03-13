#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(){
  int n;
  cin>>n;
  vector<int> a(n);
  for(int i=0;i<n;i++)cin>>a[i];
  vector<int> ans;
  for(int i=1;i<=n;i++){
    vector<int> f(a.begin(),a.begin()+i);
    vector<int> b(a.begin()+(n-i),a.end());
    sort(f.begin(),f.end());
    sort(b.begin(),b.end());
    if(f==b)ans.push_back(i);
  }
  for(int i=0;i<ans.size();i++){
    if(i)cout<<' ';
    cout<<ans[i];
  }
  cout<<endl;


  return 0;
}
