#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int iMar,i;
    float fNum,fVal=0;
    printf("请依次输入产品号和每天的销售数量:\n");
    for(i=1;i<=5;i++)
     {
         printf("\n产品号：");
         scanf("%d",&iMar);
         printf("日销售量：");
         scanf("%f",&fNum);
         switch(iMar)
          {
              case 1:
                  printf("\n1号产品的单价是2.98元。");
                  fVal=fVal+2.98*fNum;
                  break;
              case 2:
                  printf("\n2号产品的单价是4.50元。");
                  fVal=fVal+4.50*fNum;
                  break;
              case 3:
                  printf("\n3号产品的单价是9.98元。");
                  fVal=fVal+9.98*fNum;
                  break;
              case 4:
                  printf("\n4号产品的单价是4.49元。");
                  fVal=fVal+4.49*fNum;
                  break;
              case 5:
                  printf("\n5号产品的单价是6.87元。");
                  fVal=fVal+6.87*fNum;
                  break;
          }
    }
    printf("\n上周的总销售额是：%f\n",fVal*7);
    system("pause");
    return 0;
}
