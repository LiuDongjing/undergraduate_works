#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float w=4.4;
    double x=4.4;
    printf("x is %.12f,w is %.12f\n",x,w);
    printf("IS x==(double)w?%i\n",(x==(double)w));
    printf("IS (float)x==w?%i\n",((float)x==w));
    system("pause");
    return 0;
} 
