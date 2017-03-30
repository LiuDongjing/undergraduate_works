#include "stdio.h"
#include "stdlib.h"
#include "math.h"
long int sort(long int a);
int main(void)
{
    long int i;
    int count;  
    for(i=10;i<1000000;i++)
     {
         for(count=2;count<10;count++)
          if(sort(i)!=sort(i*count)) break;
         if(count>=5) printf("%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t%ld\t",i,i*2,i*3,i*4,i*5,i*6,i*7);
     }
    system("echo.&pause");
    return 0;
}
long int sort(long int a)
{
 	int num[7],j,m,mark,temp;
  	for(j=0;a;j++)
     {
         num[j]=(int)a%10;
         a/=10;
     }
    mark=j-1;  
    for(;j>0;j--)
     for(m=0;m<j;m++)
      {
          if(num[m]>num[m+1])
           {
               temp=num[m+1];
               num[m+1]=num[m];
               num[m]=temp;
           }}
    for(;mark>=0;mark--)
     {
         a+=(long int)pow(10,mark)*(long int)num[mark];
     }
    return a;
} 
