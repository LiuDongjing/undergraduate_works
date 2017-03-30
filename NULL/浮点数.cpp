#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float y;
    int i;
    for(i=0,y=.2;(y<1.0)&&(i<20);y+=.2,i++)
     printf("%f\t",y);
    system("pause");
    return 0;
}
