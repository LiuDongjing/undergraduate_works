#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double f(int y);
int main(void)
{
    double sum=0;
    int x;
    for(x=0;x<=1000;x+=50)
    	{
         printf("%.4lf %.4lf\n",f(x),sum+=f(x));
         }
    system("pause");
    return 0;
}
double f(int y)
{
    return sqrt((6*y+2));
}
