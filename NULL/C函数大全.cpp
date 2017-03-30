#include <stdio.h>
//#include "C:\\Dev-Cpp\\stdlib1.h"
#include <stdlib.h>
#include <conio.h>
struct node 
{
    unsigned a:1;
    //unsigned b:1;
    //unsigned c:1;
    //unsigned d:1;
    //unsigned e:1;
    //unsigned f:1;
    //unsigned g:1;
    //unsigned h:1;
    }Byte[8]={1,0,0,1,0,0,0,1};
int main(void)
{
    int i;
    //randomize();
    for(i=0;i<8;i++)
    //printf("%d",random(50));
    printf("%u\n",Byte[i].a);
    system("color 71");
    system("pause");
    return 0;
    }
