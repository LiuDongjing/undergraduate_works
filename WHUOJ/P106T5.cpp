#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    float a,b,c,v;
    printf("请输入X^2的系数：a=");
    scanf("%f",&a);
    printf("请输入X的系数：b=");
    scanf("%f",&b);
    printf("请输入常系数：c=");
    scanf("%f",&c);
    v=sqrt(pow(b,2)-4*a*c);
    if(v<0)
    	printf("此方程无解！");
    else
  		printf("方程%fx^2+%fx+%f=0的解是：x1=%f;x2=%f",a,b,c,(v-b)/(2*a),(-v-b)/(2*a));
    printf("\n");
    system("pause");
    return 0;
}
