#include <stdio.h>
#include <math.h>
int main(void)
{
    int i,j=0,n,sum=0;
    scanf("%d",&i);
    while(i-->0)
     {
         scanf("%d",&n);
         do{
             sum=sum+(n%7)*pow(10,j);
             j++;
         }while((n=n/7))
         printf("%d\n",sum);
     }
     return 0;
}
