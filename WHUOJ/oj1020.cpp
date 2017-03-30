#include <stdio.h>
int fun(int x,int z);
void cheek(void);
int main(void)
{
    int n;
    scanf("%d",&n);
    while(n-->0)
    {
      cheek();
    }
    return 0;
}
int fun(int x,int z)
{
    return 2*x*x*x-4*x*x+3*x-6-z;
}
void cheek(void)
{
    int a=-10,b=10,mid,y;
    scanf("%d",&y);
    if(fun(a,y)*fun(b,y)>=0)
    	printf("NULL\n");
    else
    	while(1)
     		{
           		mid=(a+b)/2;
             	if(b-a<=1)
              		{printf("NULL\n");break;}
                else if(fun(mid,y)==0)
                		{printf("%d\n",mid);break;}
               		 else if(fun(a,y)*fun(mid,y)<0)
                  			b=mid;
             		      else
                     		a=mid;
             }
}
