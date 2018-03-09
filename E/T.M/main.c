#include<stdio.h>
int main(){
  int M=1e9+7,i,j,k,l,nj,nk,lim,d[100010][5][2]={1};
  int n[]={5,1,0,3};
  char s[100010];
  scanf("%s",s);
  for(i=0;s[i];i++){
    for(j=0;j<5;j++){
      for(k=0;k<2;k++){
	if(k==0)lim=s[i]-'0';
	else    lim=9;
	//printf("%d %d\n",s[i]-'0',lim);
	for(l=0;l<=lim;l++){//printf("%d",l);
	  //*
	  nk=0;
	  if(k==1||l<lim)nk=1;
	  nj=0;
	  if(l==5      )nj=1;
	  if(l==1&&j==1)nj=2;
	  if(      j==2)nj=3;
	  if(l==3&&j==3)nj=4;
	  if(      j==4)nj=4;
	  d[i+1][nj][nk]=(d[i+1][nj][nk]+d[i][j][k])%M;
	  if(l==5&&j==2)d[i+1][1][nk]=(d[i+1][1][nk]+d[i][j][k])%M;
	  /*/
	  if(k==1||l<lim){
	    nj=0;
	    if(j==2||l==n[j])nj=j+1;
	    if(j==4)nj=4;
	    d[i+1][nj][1]+=d[i][j][k];
	    /*
	    if(j==0){
	      if(l==5)d[i+1][1][1]+=d[i][0][1];
	      else    d[i+1][0][1]+=d[i][0][1];
	    }
	    if(j==1){
	      if(l==1)d[i+1][2][1]+=d[i][1][1];
	      else    d[i+1][0][1]+=d[i][1][1];
	    }
	    if(j==2){
	              d[i+1][3][1]+=d[i][2][1];
	    }
	    if(j==3){
	      if(l==3)d[i+1][4][1]+=d[i][3][1];
	      else    d[i+1][0][1]+=d[i][3][1];
	    }
	    if(j==4){
	              d[i+1][4][1]+=d[i][4][1];
	    }
	    //*
	  }
	  else{
	    nj=0;
	    if(j==2||l==n[j])nj=j+1;
	    if(j==4)nj=4;
	    d[i+1][nj][0]+=d[i][j][0];
	    /*
	    if(j==0){
	      if(l==5)d[i+1][1][0]+=d[i][0][0];
	      else    d[i+1][0][0]+=d[i][0][0];
	    }
	    if(j==1){
	      if(l==1)d[i+1][2][0]+=d[i][1][0];
	      else    d[i+1][0][0]+=d[i][1][0];
	    }
	    if(j==2){
	              d[i+1][3][0]+=d[i][2][0];
	    }
	    if(j==3){
	      if(l==3)d[i+1][4][0]+=d[i][3][0];
	      else    d[i+1][0][0]+=d[i][3][0];
	    }
	    if(j==4){
	              d[i+1][4][0]+=d[i][4][0];
	    }
	    //*
	  }
	    //*/
	}//printf("\n");
      }
    }
  }
  /*for(j=0;j<=i;j++){
    for(k=0;k<=4;k++)printf("%4d %4d|",d[j][k][0],d[j][k][1]);printf("\n");
    }//*/
  printf("%d\n",(d[i][4][0]+d[i][4][1])%M);
  return 0;
}
	    
	      
	
