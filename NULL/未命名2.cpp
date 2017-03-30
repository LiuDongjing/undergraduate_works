#include <stdio.h>
#include <stdlib.h>
int main (void)
	{
     int f1,f2;
     char a='%';
     printf ("请输入两个整数...\n");
     scanf ("%d%d",&f1,&f2);
     printf ("f1+f2=%d;f1*f2=%d;f1-f2=%d;\nf1/f2=%f;f1%cf2=%d\n",f1+f2,f1*f2,f1-f2,
     (float)(f1)/f2,a,f1%f2);
     system ("pause");
     return 0;
     }
