#include "stdio.h"
#include "stdlib.h"
#define SIZE 10
typedef struct Queue
{
    int data[SIZE];
    int front;
    int len;
};
bool EnQueue(Queue &q,int e);
bool DeQueue(Queue &q,int &e);
int main(void)
{
    Queue Q;
    Q.front=Q.len=0;
    int tmp;
    printf("Please enter an int:");
    scanf("%d",&tmp);
    while(tmp!=0)
    {
        if(tmp>0) EnQueue(Q,tmp);
        else if(DeQueue(Q,tmp)) printf("\n%d",tmp);
        printf("\nPlease enter an int:");
        scanf("%d",&tmp);
    }
    system("pause");
    return 0;
}
bool EnQueue(Queue &q,int e)
{
    if(q.len==SIZE-1) {printf("\nOVER!");return false;}
    q.len++;
    q.data[(q.front+q.len)%SIZE]=e;
    return true;
}
bool DeQueue(Queue &q,int &e)
{
    if(q.len==0) {printf("\nNULL!");return false;}
    q.front=(q.front+1)%SIZE;
    e=q.data[q.front];
    q.len--;
    return true;
}    
