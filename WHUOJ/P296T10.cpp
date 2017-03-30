#include <stdio.h>
#include <stdlib.h>
struct node 
{
    char c;
    struct node *next;
};
struct node * create();
struct node * FX(struct node *p);
void print(struct node *m);
int main(void)
{
    struct node *head;
    printf("\t\t创建链表...\n");
    head=create();
    print(head);
    printf("\t\t反向链表...\n");
    head=FX(head);
    print(head);
    system("pause");
    return 0;
}
struct node * create()
{
    struct node *start,*end,*New;
    char st;
    printf("请输入数字或字符，输入0结束链表创建...\n");
    scanf("%c",&st);
    start=NULL;
    while(st!='0')
     {
         New=(struct node *)malloc(sizeof(struct node));
         New->c=st;
         New->next=NULL;
         if(start==NULL)
          start=New;
         else
          end->next=New;
         end=New;
         scanf("%c",&st);
     }
    return start;
}
struct node * FX(struct node *p)
{
    struct node *last,*me,*next;
    me=p;
    last=NULL;
    while(me->next!=NULL)
     {
         next=me->next;
         me->next=last;
         last=me;
         me=next;
     }
     me->next=last;
    return me;
}
void print(struct node *m)
{
    while(m->next!=NULL)
     {
         printf("%c",m->c);
         m=m->next;
     }
    printf("%c",m->c);
}
