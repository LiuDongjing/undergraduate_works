#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int iNum,iMont=1;
    scanf("%d",&iNum);
    while(iNum-->1)
    {
        iMont=2*iMont+2;
    }
    printf("%d",iMont);
    system("pause");
    return 0;
}
