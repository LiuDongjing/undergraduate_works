#include <stdio.h>
#include <stdlib.h>
struct node
{
    int a:1;
};
union INT
{
    struct node x[32];
    int y;
}IB;
int main(void)
{
    int i,p;
    printf("%d,,%d",sizeof(struct node),sizeof(union INT));
    /*for(i=0;i<32;i++)
     {
         printf("\tµÚ%dÎ»:",i+1);
         scanf("%d",&p);
         IB.x[i].a=p;
     }
printf("yes:%d",IB.y);*/
system("pause");
return 0;
}
