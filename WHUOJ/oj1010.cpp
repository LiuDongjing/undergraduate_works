#include <stdio.h>
int main(void)
{
    float a,b;
    printf("请输入价格：\n");
    scanf("%f",&a);
    printf("支付金额：\n");
    scanf("%f",&b);
    printf("%.2f",b-a);
}
