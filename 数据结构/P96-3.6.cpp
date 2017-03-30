#include "stdio.h"
#include "stdlib.h"
typedef struct QueueData
{
    int data;
    QueueData *next;
};
typedef struct QueueHead
{
    QueueData *front;
    QueueData *rear;
};
int main(void)
{
	QueueHead QueueArray[10];
 	QueueData *head=NULL,*tail=NULL;
 	int i=0,tmp;
 	QueueData *Qd=NULL;
 	for(;i<10;i++) QueueArray[i].front=QueueArray[i].rear=NULL;
 	printf("Please enter an int:");
    scanf("%d",&tmp);
    while(tmp!=-1)
    {
        if(tmp<0||tmp>9)
        	{
             printf("\nWrong!Please enter again!\n");
        	 scanf("%d",&tmp);continue;
          	}
        Qd=(QueueData *)malloc(sizeof(QueueData));
        Qd->data=tmp;
        Qd->next=NULL;
        if(QueueArray[tmp].front==NULL)
        	QueueArray[tmp].front=QueueArray[tmp].rear=Qd;
        else
        	{
             QueueArray[tmp].rear->next=Qd;
             QueueArray[tmp].rear=Qd;
             }
    printf("\nPlease enter an int:");
    scanf("%d",&tmp);
    }
    for(i=0;i<10;i++)
    if(QueueArray[i].front!=NULL)
    	if(head==NULL) {head=QueueArray[i].front;tail=QueueArray[i].rear;}
    	else {tail->next=QueueArray[i].front;tail=QueueArray[i].rear;}
   	QueueData *p=head;
   	while(p!=NULL)
   	{
        printf("%d\t",p->data);
        p=p->next;
    }
 	system("pause");
    return 0;
}
