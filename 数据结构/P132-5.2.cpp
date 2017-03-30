#include "stdio.h"
#include "stdlib.h"
typedef int Elem;
typedef struct node
{
    Elem data;
    node *next;
};
int Length(node *p);
void Show(node *p);
void ShowFromEnd(node *p);
node *DelOne(node *p,Elem x);
node *DelAll(node *p,Elem x);
int Max(node *p);
int Min(node *p);
int main(void)
{
    node *head=NULL;
    Elem tem;
    printf("Enter:");
    scanf("%d",&tem);
    while(tem!=-1)
    {
        node *tmp=(node *)malloc(sizeof(node));
        tmp->data=tem;
        tmp->next=head;
        head=tmp;
        printf("\nEnter:");
        scanf("%d",&tem);
    }
    printf("L:%d\n",Length(head));
    Show(head);
    head=DelOne(head,12);
    Show(head);
    head=DelAll(head,1);
    printf("Max:%d\tMin:%d\n",Max(head),Min(head));
    Show(head);
    system("pause");
    return 0;
}
int Length(node *p)
{
    if(p==NULL) return 0;
    return Length(p->next)+1;
}
void Show(node *p)
{
    if(p!=NULL)
    {
        printf("%d\t",p->data);
        Show(p->next);
    }
    else printf("\n");
}
void ShowFromEnd(node *p)
{
    if(p!=NULL)
    {
        ShowFromEnd(p->next);
        printf("%d\t",p->data);
    }
    else printf("\n");
}
node *DelOne(node *p,Elem x)
{
    if(p==NULL) return NULL;
    if(p->data==x)
    {
        node *tmp=p->next;
        free(p);
        return tmp;
    }
    node *q=DelOne(p->next,x);
    p->next=q;
    return p;
}
node *DelAll(node *p,Elem x)
{
    if(p==NULL) return NULL;
    node *q=DelAll(p->next,x);
    if(p->data==x)
    {
        free(p);
        return q;
    }
    p->next=q;
    return p;
}
int Max(node *p)
{
    if(p==NULL)
    {
        printf("Pointer is NULL!\n");
        system("pause");
        exit(0);
    }
    if(p->next==NULL) return p->data;
    int n=Max(p->next);
    return p->data>n?p->data:n;
}
int Min(node *p)
{
	if(p==NULL)
 	{
     printf("Pointer is NULL!\n");
     system("pause");
     exit(0);
     }
    if(p->next==NULL) return p->data;
    int n=Min(p->next);
    return p->data<n?p->data:n;
}
