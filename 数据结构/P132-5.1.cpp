#include "stdio.h"
#include "stdlib.h"
float Average(int a[],int i);
int main(void)
{
    int A[5]={-1,2,3,-4,10};
    printf("%f",Average(A,4));
    system("pause");
    return 0;
}
float Average(int a[],int i)
{
    if(i==0) return (float)a[i];
    return (Average(a,i-1)*i+a[i])/(i+1);
}
