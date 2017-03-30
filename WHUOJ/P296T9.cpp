#include <stdlib.h>
#include <stdio.h>
struct node
{
    int data;
    struct node *end;
};
struct node * creat(void);
void concatenate(struct node *pa,struct node *pb);
void print(struct node *p);
struct node * creat1();
int main(void)
{
    struct node *p1,*p2;
    printf("创建第一个链表：\n");
    p1=creat1();
    printf("\n创建第二个链表：\n");
    p2=creat1();
    printf("\n连接链表：\n");
    concatenate(p1,p2);
    printf("\n打印链表：\n");
    print(p1);
    system("pause");
    return 0;
} 
struct node * creat()
{
    struct node *head,*New;
    int n;
    head=NULL;
    printf("输入-1结束链表的创建，输入其他数字创建链表\n");
    scanf("%d",&n);
    while(n!=-1)
     {
         New=(struct node *) malloc(sizeof(struct node));
         New->data=n;
         New->end=head;
         head=New;
         scanf("%d",&n);
     }
    return head;
}
void concatenate(struct node *pa,struct node *pb)
{
    struct node *mark;
    mark=pa;
    while(mark->end!=NULL)
     mark=mark->end;
    mark->end=pb;
}
void print(struct node *p)
{
  while(p->end!=NULL)
  {
      printf("%d\t",p->data);
      p=p->end;
   }
  printf("%d\t",p->data);
}
struct node * creat1()
{
    struct node *head,*New,*tail;
    int n;
    head=NULL;
    printf("输入-1结束链表的创建，输入其他数字创建链表\n");
    scanf("%d",&n);
    while(n!=-1)
     {
         New=(struct node *) malloc(sizeof(struct node));
         New->data=n;
         New->end=NULL;
         if(head==NULL)
            head=New;
         else
         	tail->end=New;
         tail=New;
         scanf("%d",&n);
     }
    return head;
}
