#include <stdio.h>
#include <stdlib.h>
int main (void)
	{
	 int i,n;
	 char pd;
     printf ("��������������������\n");
     scanf ("%d%d",&i,&n);
     pd=(n%i==0)? 'Y':'N';
     printf ("n�Ƿ�Ϊi�ı�����%c\n",pd);
     system("pause");
     return 0;
     }
