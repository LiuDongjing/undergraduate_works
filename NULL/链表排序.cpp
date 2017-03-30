#include "stdio.h"
#include "stdlib.h"
typedef struct NODE 
{
    int num;
    NODE *next;
};//定义节点 
void swap(NODE *pa,NODE *pb);
int main(void)
{
    NODE *head=NULL;
    NODE *p=NULL,*link=NULL,*p1,*p2;
    int choose,count=0;
    scanf("%d",&choose);
    int i=0,j=0;
    while(choose!=-1)
    {
        p=(NODE *)malloc(sizeof(NODE));
        p->num=choose;
        count++;
        if(head==NULL)
        {
            head=link=p;
            p->next=NULL;
        }
        else
        {
            link->next=p;
            p->next=NULL;
            link=p;
        }
        scanf("%d",&choose);
    }
    //链表输入操作 
    p=head;
    while(p!=NULL)
    {
        printf("%d\t",p->num);
        p=p->next;
    }
    //链表输出 
    for(i=0;i<count-1;i++)
    	for(j=0,p1=head,p2=head->next;j<count-i-1;p1=p1->next,p2=p2->next,j++)
           if(p1->num>p2->num)
           	swap(p1,p2);
   	//冒泡排序 
   	for(p1=head;p1!=NULL;p1=p1->next)
   		printf("%d\t",p1->num);
    //排序后输出 
    system("pause");
   	return 0;
}
void swap(NODE *pa,NODE *pb)
{
    int temp;
    temp=pa->num;
    pa->num=pb->num;
    pb->num=temp;
}
//交换链表中的数据 
