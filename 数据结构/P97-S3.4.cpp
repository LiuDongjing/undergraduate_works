#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
    QueueHandle *Q;
    Type_6 temp;
    InitQueue(Q);
    printf("Emty?:%d\n",QueueEmpty(Q));
    EnQueue(Q,'a');
    EnQueue(Q,'b');
    EnQueue(Q,'c');
    DeQueue(Q,temp);
    printf("Element?:%c\n",temp);
    printf("Len:%d\n",QueueLength(Q));
    EnQueue(Q,'d');
    EnQueue(Q,'e');
    EnQueue(Q,'f');
    while(Q->front!=NULL)
    {
        DeQueue(Q,temp);
        printf("%c",temp);
    }
    printf("\n");
    DestroyQueue(Q);
    system("pause");
    return 0;
}
