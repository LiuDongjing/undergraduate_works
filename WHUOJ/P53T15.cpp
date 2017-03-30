#include <stdio.h>
#include <stdlib.h>
int main(void)
	{
     int N;
     char pd;
     printf("please enter an intger...\n");
     scanf ("%d",&N);
     pd=(N%2==0)? 'Y':'N';
     printf ("%dÊÇ·ñÎªÅ¼Êı£¿%c\n",N,pd);
     system("pause");
     return 0;
     }
