#include "stdio.h"
#include "stdlib.h"
typedef struct LinkList
{
    char data;
    LinkList *next;
};
void Create(LinkList *&L,char a[],int n);
void Display(LinkList *&L);
LinkList *  Link(LinkList *&ha,LinkList *&hb);
void DestroyList(LinkList *&L);
int main(void)
{ 
    char arr[10]={'a','b','c','d','e','f','g','h','i','j'};
    char arr0[10]={'k','l','m','n','o','p','q','r','s','t'};
    LinkList *ha=(LinkList *)malloc(sizeof(LinkList));
    LinkList *hb=(LinkList *)malloc(sizeof(LinkList));
    Create(ha,arr,10);
    Create(hb,arr0,10);
    Link(ha,hb);
    Display(ha);
    system("echo OK!¡£¡£¡£&pause>nul");
    DestroyList(ha);
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
         tail->next=p;
         tail=p;
         }
    tail->next=L;
}
void Display(LinkList *&L)
{
    LinkList *p=L->next;
    while(p!=L)
    {
        printf("%c\t",p->data);
        p=p->next;
    }
    printf("\n");
}
void DestroyList(LinkList *&L)
{
    LinkList *p=L->next,*q=p->next;
    while(q!=L)
    {
        free(p);
        p=q;
        q=p->next;
    }
    free(p);
}
LinkList * Link(LinkList *&ha,LinkList *&hb)
{
    LinkList *p=ha,*q=hb;
    while(p->next!=ha) p=p->next;
    while(q->next!=hb) q=q->next;
    p->next=hb->next;
    free(hb);
    q->next=ha;
    return ha;
}
