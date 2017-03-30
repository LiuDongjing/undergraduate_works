#include <stdio.h>
#include <stdlib.h>
struct Intbyte
	{
     int a:1;
     int b:1;
     int c:1;
     int d:1;     
     int e:1;
     int f:1;
     int g:1;
     int h:1;
     int i:1;
     int j:1;
     int k:1;
     int l:1;
     int m:1;
     int n:1;
     int o:1;
     int p:1;
     int q:1;
     int r:1;
     int s:1;
     int t:1;
     int u:1;
     int v:1;
     int w:1;
     int x:1;
     int y:1;
     int z:1;
     int aa:1;
     int ab:1;
     int ac:1;
     int ad:1;
     int ae:1;
     int af:1;
 }IB={0};
 union INT
 {
     struct Intbyte er;
     int shi;
 }IT;
 /*struct point
 {
  int *x:1;
 }p;*/
 int main(void)
 {
     int i;
    // p.x=&(IT->er->a);
     for(i=0;i<32;i++)
      {
          printf("\n请输入第%d位:",i+1);
          scanf("%d",&(IT.er)+i);
          //p++;
      }
 printf("数字：%d",IT.shi);
 system("pause");
 return 0;
 }
