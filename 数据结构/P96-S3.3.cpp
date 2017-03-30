#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
	QueueList *Q=NULL;
	Type_5 tmp;
	InitQueue(Q);
	printf("QueueEmpty:%d\n",QueueEmpty(Q));
	EnQueue(Q,'a');
	EnQueue(Q,'b');
	EnQueue(Q,'c');
	DeQueue(Q,tmp);
	printf("Element:%c\n",tmp);
	printf("size:%d\n",(MaxSize+Q->rear-Q->front)%MaxSize);
	EnQueue(Q,'d');
	EnQueue(Q,'e');
	EnQueue(Q,'f');
	printf("size:%d\n",(MaxSize+Q->rear-Q->front)%MaxSize);
	while(!QueueEmpty(Q))
	{
     DeQueue(Q,tmp);
     printf("Element:%c\t",tmp);
     }
    DestroyQueue(Q);
 	system("pause");
    return 0;
}
