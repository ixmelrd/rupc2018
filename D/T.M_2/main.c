#include<stdio.h>
double MAX(double a,double b){return a<b?b:a;}
int main(){
  int n,m,i,j,k;
  double d[510][510]={};
  long long s[510]={};
  scanf("%d %d",&n,&m);
  for(i=0;i<n;i++){
    scanf("%lld",&s[i+1]);
    s[i+1]+=s[i];
  }
  //for(i=0;i<=n;i++)printf("%lld ",s[i]);printf("\n");
  if(m==1){
    printf("%.10lf\n",1.0*s[n]/n);
    return 0;
  }
  for(j=1;j<n;j++)d[1][j]=1.0*s[n-j]/(n-j);//printf("%lf ",d[1][j]);
  //printf("\n");//*/
  for(i=2;i<m;i++){
    for(j=1;j<n-i+2;j++){
      for(k=j+1;k<n-i+2;k++)d[i][j]=MAX(d[i][j],d[i-1][k]+1.0*(s[n-j]-s[n-k])/(k-j));
    }
  }
  /*for(i=0;i<m;i++){
    for(j=0;j<=n;j++)printf("%10.5lf ",d[i][j]);printf("\n");
    }//*/
  for(i=1;i<n-m+2;i++)d[m][1]=MAX(d[m][1],d[m-1][i]+1.0*(s[n]-s[n-i])/i);
  printf("%.10lf\n",d[m][1]);
  return 0;
}
	
