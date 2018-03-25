#include<stdio.h>
int main(){
  int M=1e9+7,i,j,k,l,nj,nk,lim;
  long long d[20][5][2]={1};
  char s[100010];
  scanf("%s",s);
  for(i=0;s[i];i++){
    for(j=0;j<5;j++){
      for(k=0;k<2;k++){
	if(k==0)lim=s[i]-'0';
	else    lim=9;
	for(l=0;l<=lim;l++){//printf("%d",l);
	  nk=0;
	  if(k==1||l<lim)nk=1;
	  nj=0;
	  if(l==5      )nj=1;
	  if(l==1&&j==1)nj=2;
	  if(      j==2)nj=3;
	  if(l==3&&j==3)nj=4;
	  if(      j==4)nj=4;
	  if(k==0&&d[i][j][k])d[i][j][k]=1;
	  d[i+1][nj][nk]+=d[i][j][k];
	  if(l==5&&j==2)d[i+1][1 ][nk]+=d[i][j][k];
	}
      }
    }
  }
  /*for(j=0;j<=i;j++){
    for(k=0;k<=4;k++)printf("%d %7d|",d[j][k][0],d[j][k][1]);printf("\n");
    }//*/
  if(d[i][4][0])d[i][4][1]++;
  printf("%lld\n",d[i][4][1]);
  return 0;
}
