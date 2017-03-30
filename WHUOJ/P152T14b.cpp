#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define min(a,b,c) ((a>b?a:b)>c)?(a>b?a:b):c
#define x 3
#undef x 2
int StoQ(int);
int main(void)
{
    int m;
    printf("");
    scanf("%d",&m);
    printf("%d\n",StoQ(m));
    printf("%d",x);
    system("pause");
    return 0;
}
int StoQ(int n)
{
    int i,sum=0;
    for(i=0;n;i++)
    {
        sum+=(n%7)*(int)pow(10,i);
        n=n/7;
    }
return sum;
}
