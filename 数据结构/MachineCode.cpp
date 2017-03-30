#include "stdio.h"
#include "stdlib.h"
void ShowMachinecode(long int data)
{
    int flag=0;
    long int tmp=data&2147483647;
    if(tmp!=data) flag=1;
    long int head=tmp/268435456;
    long int tail=tmp%268435456;
    if(flag) head+=8;
    printf("\n%X%X\n",head,tail);
}
