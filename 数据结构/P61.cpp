//#Common#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
#include "stdlib.h"
#include "stdio.h"
#define MaxSize 10
//#1#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef int Type_1;
typedef struct {
    Type_1 data[MaxSize];
    int Length;
    }SqList;
void InitList(SqList * &L)
{
    L=(SqList *)malloc(sizeof(SqList));
    L->Length=0;
}
void DestroyList(SqList * &L){free(L);}
bool ListEmpty(SqList * &L){return L->Length==0;}
int ListLength(SqList * &L){return L->Length;}
void DispList(SqList * &L)
{
    int i=0;
    for(;i<L->Length;i++)
    	printf("%d\t",L->data[i]);//修改Type时应改此句 
    printf("\n");
}
bool GetElem(SqList * &L,int i,Type_1 &e)
{
    if(i<1 || i>L->Length) return false;
    e=L->data[i-1];
    return true;
}
int LocateElem(SqList * &L,Type_1 &e)
{
    int i=0;
    while(i<L->Length && L->data[i]!=e) i++;
    if(i==L->Length) return 0;
    else
    	return i+1;
}
bool ListInsert(SqList * &L,int i,Type_1 e)
{
    if(i<1 || i>L->Length+1) return false;
    int j=L->Length;
    for(;j>i-1;j--) L->data[j]=L->data[j-1];
    L->data[i-1]=e;
    L->Length++;
    return true;
}
bool ListDelete(SqList * &L,int i,Type_1 &e)
{
    if(i<1 || i>L->Length) return false;
    e=L->data[i-1];
    for(;i<L->Length;i++)
    	L->data[i-1]=L->data[i];
    L->Length--;
    return true;
}
//#2#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
typedef int Type_2;
typedef struct LNode {
    Type_2 data;
    LNode *next;
    };
void ListSort(LNode *&L)
{
    LNode *q=L->next->next,*m,*p;
    L->next->next=NULL;
    while(q!=NULL)
    {
        m=q->next;
        p=L;
        while(p->next!=NULL&&p->next->data<=q->data) p=p->next;
        q->next=p->next;
        p->next=q;
        q=m;
    }
}
void InitList(LNode *&L)
{
    L=(LNode *)malloc(sizeof(LNode));
    L->next=NULL;
}
void DestroyList(LNode *&L)
{
    LNode *p=L->next;
    while(p!=NULL)
    {
        free(L);
        L=p;
        p=p->next;
    }
    free(L);
}
bool ListEmpty(LNode *&L)
{
    return L->next==NULL;
}
int ListLength(LNode *&L)
{
    int count=0;
    LNode *p=L->next;
    while(p!=NULL)
    {
        count++;
        p=p->next;
    }
    return count;
}
void DispList(LNode *&L)
{
    LNode *p=L->next;
    while(p!=NULL)
    {
        printf("%d\t",p->data);//修改Type时应改此句 
        p=p->next;
    }
    printf("\n");
}
bool GetElem(LNode *&L,int i,Type_2 &e)
{
    int count=1;
    LNode *p=L->next;
    while(p!=NULL&&count<i)
    {
        count++;
        p=p->next;
    }
    if(p==NULL||i<1) return false;
    e=p->data;
    return true;
}
int LocateElem(LNode *&L,Type_2 e)
{
    int count=1;
    LNode *p=L->next;
    while(p!=NULL&&p->data!=e)
    {
        count++;
        p=p->next;
    }
    if(p==NULL) return false;
    return count;
}
bool ListInsert(LNode *&L,int i,Type_2 e)
{
    int count=1;
    LNode *p=L->next,*New;
    while(p!=NULL&&count<i-1)
    {
        count++;
        p=p->next;
    }
    if(p!=NULL)
    	{
         New=(LNode *)malloc(sizeof(LNode));
         New->data=e;
         New->next=p->next;
         p->next=New;
         return true;
         }
    return false;
}
bool ListDelete(LNode *&L,int i,Type_2 &e)
{
    int count=1;
    LNode *p=L->next,*me;
    while(p!=NULL&&count<i-1)
    {
        count++;
        p=p->next;
    }
    if(p==NULL) return false;
    me=p->next;
    if(me==NULL) return false;
    e=me->data;
    p->next=me->next;
    free(me);
    return true;
}
void CreateListByTail(LNode *&L,Type_2 a[],int n)
//尾插法 
{
    int i=0;
    LNode *tail=L,*tmp;
    for(;i<n;i++)
    {
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=a[i];
        tail->next=tmp;
        tail=tmp;
    }
    tail->next=NULL;
}
void CreateListByHead(LNode *&L,Type_2 a[],int n)
//头插法 
{
    int i=0;
    LNode *tmp;
    for(;i<n;i++)
    {
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=a[i];
        tmp->next=L->next;
        L->next=tmp;
    }
}
//#3#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef int Type_3;
typedef struct Poly
{
    float Coef;
    int Index;
    Poly *next;
};
void CreateListByTail(Poly *&L,Type_3 a[],float b[],int n)
//尾插法
{
    int i=0;
    Poly *tail=L,*tmp;
    for(;i<n;i++)
    {
        tmp=(Poly *)malloc(sizeof(Poly));
        tmp->Index=a[i];
        tmp->Coef=b[i];
        tail->next=tmp;
        tail=tmp;
    }
    tail->next=NULL;
}
void DispList(Poly *&L)
{
    Poly *p=L->next;
    while(p!=NULL)
    {
        printf("An:%.1f N:%d\t",p->Coef,p->Index);//
        p=p->next;
    }
    printf("\n");
}
void DestroyList(Poly *&L)
{
    Poly *p=L->next;
    while(p!=NULL)
    {
        free(L);
        L=p;
        p=p->next;
    }
    free(L);
}
//#4:P96-S3.1#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
typedef char Type_4;
typedef struct SqStack{
    Type_4 data[MaxSize];
    int top;
    };
void InitStack(SqStack *&S)
{
    S=(SqStack *)malloc(sizeof(SqStack));
    S->top=-1;
}
void DestroyStack(SqStack *&S){free(S);}
bool EmptyStack(SqStack *&S) {return S->top==-1;}
bool Push(SqStack *&S,Type_4 e)
{
    if(S->top==MaxSize-1) return false;
    S->top++;
    S->data[S->top]=e;
    return true;
}
bool Pop(SqStack *&S,Type_4 &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    S->top--;
    return true;
}
bool GetTop(SqStack *&S,Type_4 &e)
{
    if(S->top==-1) return false;
    e=S->data[S->top];
    return true;
}
//#5:P96-S3.2#<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
typedef char Type_5;
typedef struct LiStack{
    Type_5 data;
    LiStack *next;
    };
void InitStack(LiStack *&S)
{
    S=(LiStack *)malloc(sizeof(LiStack));
    S->next=NULL;
}
void DestroyStack(LiStack *&S)
{
    LiStack *p=S,*q;
    while(p!=NULL)
    {
        q=p->next;
        free(p);
        p=q;
    }
}
bool EmptyStack(LiStack *&S)
{
    return S->next==NULL;
}
void Push(LiStack *&S,Type_5 e)
{
    LiStack *p=(LiStack *)malloc(sizeof(LiStack));
    p->data=e;
    p->next=S->next;
    S->next=p;
}
bool Pop(LiStack *S,Type_5 &e)
{
    if(S->next==NULL) return false;
    LiStack *p=S->next;
    e=p->data;
    S->next=p->next;
    free(p);
    return true;
}
bool GetTop(LiStack *S,Type_5 &e)
{
    if(S->next==NULL) return false;
    e=S->next->data;
    return true;
}
int GetSize(LiStack *S)
{
    int count=0;
    LiStack *p=S;
    while(p->next!=NULL)
    {
        p=p->next;
        count++;
    }
    return count;
}
//#6:P96-S3.3#<<>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef char Type_5;
typedef struct QueueList
{
    Type_5 data[MaxSize];
    int front;
    int rear;
};
void InitQueue(QueueList *&q)
{
    q=(QueueList*)malloc(sizeof(QueueList));
    q->front=q->rear=-1;
}
void DestroyQueue(QueueList *&q)
{
    free(q);
}
bool QueueEmpty(QueueList *&q)
{
    return q->front==q->rear;
}
bool EnQueue(QueueList *&q,Type_5 e)
{
    if(q->rear-q->front==MaxSize||q->front-q->rear==1)
    	return false;
    q->rear=(q->rear+1)%MaxSize;
    q->data[q->rear]=e;
    return true;
}
bool DeQueue(QueueList *&q,Type_5 &e)
{
    if(q->rear==q->front) return false;
    q->front=(q->front+1)%MaxSize;
    e=q->data[q->front];
    return true;
}
//#7:P96-S3.4#>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
typedef char Type_6;
typedef struct QueueData
{
    Type_6 data;
    QueueData *next;
};
typedef struct QueueHandle
{
    QueueData *front;
    QueueData *rear;
};
void InitQueue(QueueHandle *&q)
{
    q=(QueueHandle *)malloc(sizeof(QueueHandle));
    q->front=q->rear=NULL;
}
void DestroyQueue(QueueHandle *&q)
{
    QueueData *p=q->front,*s;
    while(p!=NULL)
    {
        s=p->next;
        free(p);
        p=s;
    }
    free(q);
}
bool QueueEmpty(QueueHandle *q)
{
    return q->front==NULL;
}
void EnQueue(QueueHandle *&q,Type_6 e)
{
    QueueData *tmp=(QueueData *)malloc(sizeof(QueueData));
    tmp->data=e;
    tmp->next=NULL;
    if(q->rear==NULL)
    {
        q->front=tmp;
        q->rear=tmp;
    }
    else
    {
        q->rear->next=tmp;
        q->rear=tmp;
    }
}
bool DeQueue(QueueHandle *&q,Type_6 &e)
{
    if(q->front==NULL) return false;
    QueueData *p=q->front;
    e=p->data;
    if(q->front==q->rear) q->front=q->rear=NULL;
    else q->front=q->front->next;
    free(p);
    return true;
}
int QueueLength(QueueHandle *&q)
{
    QueueData *p=q->front;
    int len=0;
    while(p!=NULL) {len++;p=p->next;}
    return len;
}
//>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
