#include <stdio.h>
#include <stdlib.h>
#include <math.h>
//int i=0,sum=0;
int StoQ(int);
int main(void)
{
    int a;
    printf("请输入十进制数:\n");
    scanf("%d",&a);
    printf("七进制:%d",StoQ(a));
    system("pause");
    return 0;
}
int StoQ(int b)
{
	static int i=0,sum=0;
    if(b)
     {sum+=(b%7)*(int)pow(10,i);
     i++;
     return StoQ(b/7);
     }
    else
     return sum;
}
