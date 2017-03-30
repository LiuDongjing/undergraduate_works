#include "stdio.h"
#include "stdlib.h"
int count(unsigned int n);
int main(void)
{
    printf("%d\n",count(0xF0FFu));
    system("pause");
    return 0;
}
int count(unsigned int n)
{
    if(n==0u) return 0;
   	if(n%2==1) return count(n>>1)+1;
    return count(n>>1);
}
