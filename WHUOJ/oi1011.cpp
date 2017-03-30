#include <stdio.h>
void cal(int,int,int);
int main(void)
{
    int a,b,c,count;
    scanf("%d",&count);
    while(count--!=0)
     {
         scanf("%d %d %d",&a,&b,&c);
         cal(a,b,c);
     }
    return 0;
}
void cal(int i,int j,int k)
{
    printf("%d %.2f %d %d %d\n",i+j+k,((float)i+j+k)/3,i*j*k,(i<j?i:j)<k?(i<j?i:j):k,(i>j?i:j)>k?(i>j?i:j):k);
}
