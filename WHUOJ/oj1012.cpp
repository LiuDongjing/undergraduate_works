#include <stdio.h>
int main(void)
{
    int n;
    float temp;
    scanf("%d",&n);
    while(n-->0)
    {
        scanf("%f",&temp);
        printf("%.2f\n",temp*1.609344);
    }
    getchar();
    return 0;
}
