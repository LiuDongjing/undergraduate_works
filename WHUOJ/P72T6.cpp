#include <stdio.h>
#include <stdlib.h>
int main()
{
    long int N,a[4],temp,i;
    printf("请输入一个五位整数...");
    scanf("%li",&N);
    temp=N/10000;
    a[0]=temp;
    temp=N/1000;
    a[1]=temp%10;
    temp=N/100;
    a[2]=temp%10;
    temp=N/10;
    a[3]=temp%10;
    a[4]=N%10;
    for(i=0;i<5;i++)
    	printf("%3li",a[i]);
   	system("pause");
   	return 0;
    }
