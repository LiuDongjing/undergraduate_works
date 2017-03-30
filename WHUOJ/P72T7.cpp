#include <stdio.h>
#include <stdlib.h>
int main()
{
    float T;
    printf("请输入华氏温度:");
    scanf("%f",&T);
    T=(T-32)*5/9;
    printf("\n转化后摄氏温度：%f\n",T);
    system("pause");
    return 0;
    
}
