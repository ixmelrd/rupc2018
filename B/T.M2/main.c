#include<stdio.h>
int main(){
  int a[100010],b,n,i,s=0,u[100010]={};
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%d",&a[i]);
  for(i=0;i<n;i++){
    scanf("%d",&b);
    s+=u[b];
    u[b]=1;
  }
  if(s==0){
    printf("Yes\n");
    return 0;
  }
  printf("No\n");
  for(i=0;i<n;i++)printf("%d%c",u[a[i]]+1,n-i-1?' ':'\n');
  for(i=0;i<n;i++)printf("2%c",n-i-1?' ':'\n');
  return 0;
}
