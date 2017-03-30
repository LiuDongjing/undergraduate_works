#include <stdio.h>
#include <stdlib.h>
void move(char,char);
void hanoi(int n,char curPos,char frePos,char desPos);
int Num=0;
int main(void)
{
    int count;
    printf("Desk Connt:");
    scanf("%d",&count);
    hanoi(count,'A','B','C');
    printf("共用去%d步。",Num);
    system("pause");
    return 0;
}
void move(char CurPos,char DesPos)
{
    printf("%c->%c\n",CurPos,DesPos);
    Num++;
}
void hanoi(int n,char curPos,char frePos,char desPos)
{
    if(n==1)
    	move(curPos,desPos);
    else
    	{
         hanoi(n-1,curPos,desPos,frePos);
         move(curPos,desPos);
         hanoi(n-1,frePos,curPos,desPos);
         }
}
