#include "stdio.h"
#include "stdlib.h"
#define SIZE 20
void Life(char world[SIZE][SIZE]);
int main(void)
{
    char life[SIZE][SIZE],enter='s';
    int i,j;
    for(i=0;i<SIZE;i++)
    	for(j=0;j<SIZE;j++)
     		life[i][j]='+';
    life[4][4]='*';
    life[3][5]='*';
    life[3][3]='*';
    life[1][2]='*';
    life[6][3]='*';
    life[2][2]='*';
    while(enter!='e')
    {
        for(i=0;i<SIZE;i++)
    	{
         for(j=0;j<SIZE;j++)
         	printf("%c ",life[i][j]);
         printf("\n");
         }
        //system("pause");
        Life(life);
        fflush(stdin);
        scanf("%c",&enter);
     }
    system("pause");
    return 0;
}
void Life(char world[SIZE][SIZE])
{
    char _world[SIZE][SIZE];
    bool envi[8];
    int i,j,k,n;
    for(i=0;i<SIZE;i++)
    	for(j=0;j<SIZE;j++)
     		_world[i][j]=world[i][j];
    for(i=0;i<SIZE;i++)
    	for(j=0;j<SIZE;j++)
     	{
          n=0;
          if(i-1>=0&&j-1>=0&&_world[i-1][j-1]=='*') envi[0]=true;
          else envi[0]=false;
          if(i+1<SIZE&&j+1<SIZE&&_world[i+1][j+1]=='*') envi[1]=true;
          else envi[1]=false;
          if(i-1>=0&&j+1<SIZE&&_world[i-1][j+1]=='*') envi[2]=true;
          else envi[2]=false;
          if(i+1<SIZE&&j-1>=0&&_world[i+1][j-1]=='*') envi[3]=true;
          else envi[3]=false;
          if(j-1>=0&&_world[i][j-1]=='*') envi[4]=true;
          else envi[4]=false;
          if(j+1<SIZE&&_world[i][j+1]=='*') envi[5]=true;
          else envi[5]=false;
          if(i-1>=0&&_world[i-1][j]=='*') envi[6]=true;
          else envi[6]=false;
          if(i+1<SIZE&&_world[i+1][j]=='*') envi[7]=true;
          else envi[7]=false;
          for(k=0;k<8;k++)
          	if(envi[k]) n++;
//ÅÐ¶ÏÁÚ¾Ó  	      
          if(n>=2&&n<=6) world[i][j]='*';
  	      else if(n==1) continue;
  	      else world[i][j]='+';
     }
} 
