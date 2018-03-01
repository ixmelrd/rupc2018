#include<stdio.h>
double MAX(double a,double b){return a<b?b:a;}
int main(){
  int n,m,i,j,k,s[510]={};
  double d[510][510]={};
  scanf("%d %d",&n,&m);
  for(i=0;i<n;i++){
    scanf("%d",&s[i+1]);
    s[i+1]+=s[i];
  }
  //s[n+1]=s[n];
  //for(i=0;i<=n+1;i++)printf("%d ",s[i]);printf("\n");
  for(i=1;i<n;i++){
    double e[510][510]={};
    for(j=0;j<m;j++){
      if(i<j)continue;
      for(k=1;k<=n;k++){
	if(i<k)continue;//printf("!%d %d %d\n",i,j,k);
	e[j][k+1]=MAX(e[j][k+1],d[j][k]);
	e[j+1][1]=MAX(e[j+1][1],d[j][k]+1.0*(s[i]-s[i-k])/(k));
      }
    }
    for(j=0;j<=m;j++){
      for(k=0;k<n;k++)d[j][k]=e[j][k];
      //for(k=0;k<=n;k++)printf("%lf ",d[j][k]);printf("\n");
    }//printf("\n");
  }
  for(i=n-m+1;i<=n;i++){
    d[m][0]=MAX(d[m][0],d[m-1][i]+1.0*(s[n]-s[n-i])/i);
  }
  /*for(i=0;i<=m;i++){
    for(j=0;j<=n;j++)printf("%lf ",d[i][j]);printf("\n");
    }//*/
  printf("%lf\n",d[m][0]);
  return 0;
}
