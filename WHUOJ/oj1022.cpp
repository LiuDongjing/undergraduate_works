#include <stdio.h>
#include <math.h>
#include <stdlib.h>
double distance(double x1, double y1, double x2, double y2);
int main(void)
{
    int n;
    double X1,Y1,X2,Y2;
    scanf("%d",&n);
    while(n-->0)
    {
        scanf("%lf %lf %lf %lf",&X1,&Y1,&X2,&Y2);
        printf("%.4lf\n",distance(X1,Y1,X2,Y2));
    }
    system("pause");
    return 0;
}
double distance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}
