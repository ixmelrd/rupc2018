#include<stdio.h>
int main(){
  int i,j,k,l,nj,nk,lim;
  long long d[20][6][2]={1};
  char s[100010];
  scanf("%s",s);
  for(i=0;s[i];i++){
    for(j=0;j<6;j++){
      for(k=0;k<2;k++){
	lim=k?9:s[i]-'0';
	for(l=0;l<=lim;l++){//printf("%d",l);
	  nj=nk=0;
	  if(k==1||l<lim)nk=1;
	  if(l==5      )nj=1;
	  if(l==1&&j==1)nj=2;
	  if(      j==2)nj=3;
	  if(l==5&&j==2)nj=4;
	  if(l==3&&j==3)nj=5;
	  if(l==3&&j==4)nj=5;
	  if(l==1&&j==4)nj=2;
	  if(      j==5)nj=5;
	  d[i+1][nj][nk]+=d[i][j][k];
	}
      }
    }
  }
  printf("%lld\n",d[i][5][0]+d[i][5][1]);
  return 0;
}
