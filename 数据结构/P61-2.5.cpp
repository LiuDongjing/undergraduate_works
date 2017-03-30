#include "stdio.h"
#include "stdlib.h"
typedef struct LinkList
{
    int freq;
    char data;
    LinkList *prior;
    LinkList *next;
};
void Create(LinkList *&L,char a[],int n);
void Display(LinkList *&L);
int LocateNode(LinkList *&L,char x);
void DestroyList(LinkList *&L);
int main(void)
{ 
    char arr[10]={'a','b','c','d','e','f','g','h','i','j'};
    int i=0;
    char tmp;
    LinkList *chain=(LinkList *)malloc(sizeof(LinkList));
    chain->next=NULL;
    Create(chain,arr,10);
    Display(chain);
    for(;i<10;i++)
    	{
         fflush(stdin);
         scanf("%c",&tmp);
         LocateNode(chain,tmp);
         }
    Display(chain);
    system("echo OK!¡£¡£¡£&pause>nul");
    DestroyList(chain);
    return 0;
}
void Create(LinkList *&L,char a[],int n)
{
    LinkList *tail=L,*p;
    int i=0;
    for(;i<n;i++)
    	{
         p=(LinkList *)malloc(sizeof(LinkList));
         p->data=a[i];
         p->freq=0;
         tail->next=p;
         p->prior=tail;
         tail=p;
         }
    tail->next=NULL;
}
void Display(LinkList *&L)
{
    LinkList *p=L->next;
    while(p!=NULL)
    {
        printf("%c %d\t",p->data,p->freq);
        p=p->next;
    }
    printf("\n");
}
int LocateNode(LinkList *&L,char x)
{
    LinkList *p=L->next,*mark;
    int count=1;
    while(p!=NULL&&p->data!=x) 
    {
        p=p->next;
        count++;
    }    
    if(p==NULL) return 0;
    mark=p;
    p=L->next;
    mark->freq++;
    while(p->freq>=mark->freq) p=p->next;
    if(mark->next!=NULL)
    {
        mark->next->prior=mark->prior;
        mark->prior->next=mark->next;
    }
    else mark->prior->next=NULL;    
    mark->prior=p->prior;
    p->prior->next=mark;
    mark->next=p;
    p->prior=mark;
    return count;
}
void DestroyList(LinkList *&L)
{
    LinkList *p=L->next,*q=p->next;
    while(q!=NULL)
    {
        free(p);
        p=q;
        q=p->next;
    }
    free(p);
}
