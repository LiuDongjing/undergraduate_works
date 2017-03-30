#include <stdio.h>
#include <stdlib.h>
void reverse(long int n);
int main(void)
{
    long int N;
    scanf("%ld",&N);
    reverse(N);
    system("pause");
    return 0;
}
void reverse(long int n)
{
    if(n>=1000)
     reverse(n/1000);
    printf("%d ",n%1000);
}
