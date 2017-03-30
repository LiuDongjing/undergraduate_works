#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int i,j,ch;
    for(i=0;i<4;i++)
     for(j=0;j<19;j++)
      {
          switch(j)
           {
               case 8:
               case 18:
                   ch=10;break;
               case 9:
                   ch=32;break;
               default:
                   ch=42;break;
           }
          printf("%c",ch);
      }
    system("pause");
    return 0;
}
