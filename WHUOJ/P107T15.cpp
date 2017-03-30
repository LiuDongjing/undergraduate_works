#include <stdio.h>
char trans(int t);
int main(void)
{
    int x,y,z;
    for(x=1;x<=3;x++)
     for(y=1;y<=3;y++)
      for(z=1;z<=3;z++)
       {
           if(((x+y+z)==6)&&(x!=y))
            printf("A %c\nB %c\nC %c\n",trans(x),trans(y),trans(z));
       }
    for(x=1;x<=3;x++)
     for(y=1;y<=3;y++)
      for(z=1;z<=3;z++)
       {
           if(((x+y+z)==6)&&(x!=y)&&(x!=1)&&(z!=1)&&(z!=3))
            printf("A %c\nB %c\nC %c\n",trans(x),trans(y),trans(z));
       }
      getchar();
    return 0;
}
char trans(int t)
{
    switch(t)
    {
        case 1:
            return 'X';
        case 2:
            return 'Y';
        case 3:
            return 'Z';
    }
}    
