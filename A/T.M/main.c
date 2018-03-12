#include<stdio.h>
int main(){
  int n,i,a[1010],b[1010]={};
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%d",&a[i]);
  for(i=0;i<n;i++){
    if(b[a[i]%(n-1)]){
      printf("%d %d\n",b[a[i]%(n-1)],a[i]);
      return 0;
    }
    b[a[i]%(n-1)]=a[i];
  }
}
