#include <stdio.h>
#include <stdlib.h>
#define size 10
int tolow(int array[],int sub,int num);
void move(int array2[],int sub2,int tail);
int main(void)
{
    int a[10],i,temp;
    printf("先输入两个数：\n");
    scanf("%d %d",&a[0],&a[1]);
    if(a[0]>a[1])
     {
         temp=a[1];
         a[1]=a[0];
         a[0]=temp;
     }
    for(i=2;i<size;i++)
     {
         scanf("%d",&a[i]);
         temp=a[i];
         move(a,tolow(a,i-1,temp),i-1);
         a[tolow(a,i-1,temp)+1]=temp;
     }
    for(i=0;i<size;i++)
     printf("%d\t",a[i]);
    system("pause");
    return 0;
}
int tolow(int array[],int sub,int num)
{
    for(;sub>=0;sub--)
     if(array[sub]<=num)
     	return sub;
    return -1;
}
void move(int array2[],int sub2,int tail)
{
    for(;sub2!=tail;tail--)
     array2[tail+1]=array2[tail];
}
