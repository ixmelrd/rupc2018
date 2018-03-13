#include <iostream>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

int main(){
  int n;
  cin>>n;
  vector<int> a(n),b(n);
  set<int> s;
  bool flag=false;
  for(int i=0;i<n;i++)cin>>a[i];
  for(int i=0;i<n;i++){
    cin>>b[i];
    if(s.find(b[i])==s.end()){
      s.insert(b[i]);
    }else{
      flag=true;
    }
  }
  if(!flag){
    cout<<"Yes"<<endl;
  }else{
    cout<<"No"<<endl;
    vector<int> dif(n);
    int c=a[0],d=a[1];
    for(int i=0;i<n;i++){
      if(s.find(a[i])==s.end()){
        dif[i]=1;
      }
    }
    for(int i=0;i<n;i++){
      if(i)cout<<' ';
      cout<<c;
    }
    cout<<endl;
    for(int i=0;i<n;i++){
      if(i)cout<<' ';
      if(dif[i])cout<<d;
      else cout<<c;
    }
    cout<<endl;
  }

}
