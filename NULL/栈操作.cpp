#include <stdio.h>
#include <stdlib.h>
#define size 20
int zout(int a[],int len);
int zin(int a[],int len,int m);
int main(void)
{
    int down,i,n;
    down=0;
    int a[size]={};
    printf("输入0出栈，-1退出程序，其余数字入栈...\n");
    scanf("%d",&n);
    while(n!=-1)
     {
         if(n==0)
         	if(down==0)
          		printf("栈空！\n");
            else
            	down=zout(a,down);
         else
         	if(down==size-1)
          		printf("栈满！\n");
       		else
         		down=zin(a,down,n);
         scanf("%d",&n);
     }
    return 0;
}
int zout(int a[],int len)
{
    printf("%d",a[0]);
    int k;
    for(k=0;k<=len;k++)
     a[k]=a[k+1];
    return len-1;
} 
int zin(int a[],int len,int m)
{
    int k;
    for(k=len;k>=0;k--)
    	a[k+1]=a[k];
    a[0]=m;
    return len+1;
}
