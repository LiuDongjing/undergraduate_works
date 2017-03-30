#include <stdio.h>
#include <stdlib.h>
#define word 32
union {
    	int x;
    	struct{
     	char a;
     	char b;
     	char c;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int:1;
     	unsigned int y:1;
       	}bs;   	
      }byte;
int main(void)
{
    int i,n;
    scanf("%d",&n);
    for(i=0;i<word;i++)
     {
         byte.x=n;
         printf("%u",byte.bs.y);
         n=n<<1;
        //printf("\t\t%d\t",byte.x); 
     }
    system("pause");
    return 0;
}
