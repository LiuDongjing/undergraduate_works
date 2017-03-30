#include <stdio.h>
#include <stdlib.h>
int main (void)
	{
	 int i,n;
	 char pd;
     printf ("请输入两个整数。。。\n");
     scanf ("%d%d",&i,&n);
     pd=(n%i==0)? 'Y':'N';
     printf ("n是否为i的倍数？%c\n",pd);
     system("pause");
     return 0;
     }
