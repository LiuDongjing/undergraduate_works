#include "stdio.h"
#include "stdlib.h"
typedef struct NODE 
{
    int num;
    NODE *next;
};//����ڵ� 
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
    //����������� 
    p=head;
    while(p!=NULL)
    {
        printf("%d\t",p->num);
        p=p->next;
    }
    //������� 
    for(i=0;i<count-1;i++)
    	for(j=0,p1=head,p2=head->next;j<count-i-1;p1=p1->next,p2=p2->next,j++)
           if(p1->num>p2->num)
           	swap(p1,p2);
   	//ð������ 
   	for(p1=head;p1!=NULL;p1=p1->next)
   		printf("%d\t",p1->num);
    //�������� 
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
//���������е����� 
