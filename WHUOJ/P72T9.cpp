#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float YL,GL,d;
    d=1.609344;
    printf("请输入英里：");
    scanf("%f",&YL);
    while(YL<0)
    {
        printf("输入的数据不符实际，请重新输入！\n英里：");
        scanf("%f",&YL);
    }
    GL=d*YL;
    printf("转化后是%f公里。\n",GL);
    system("pause");
    return 0;
}
