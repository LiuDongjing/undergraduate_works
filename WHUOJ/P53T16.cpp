#include <stdio.h>
#include <stdlib.h>
#define PI 3.141592
int main (void)
	{
	    float r;
	    printf ("请输入半径...\n");
	    scanf ("%f",&r);
	    printf ("直径：%f;周长：%f;面积：%f;\n",2*r,2*PI*r,2*PI*r*r);
	    system("pause");
	    return 0;
     }
