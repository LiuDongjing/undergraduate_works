#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main(void)
{
    time_t t;
    srand((unsigned int) time(&t));
    int a[4][5],*p,i,j,sum;
    p=&a[0][0];
    for(i=0;i<20;i++)
     p[i]=rand()%100;
    for(i=0,sum=0;i<4;i++)
     {
         for(j=0;j<5;j++)
          sum=sum+a[i][j];
         printf("第%d行的平均值是：%d\n",i+1,sum/5);
     }
    for(sum=0,j=0;j<5;j++)
     {
         for(i=0;i<4;i++)
          sum=sum+a[i][j];
          printf("第%d列的平均值是：%d\n",j+1,sum/5);
     }
     system("pause");
     return 0;
     }
