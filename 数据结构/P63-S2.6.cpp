#include "F:\\C\\C\\数据结构\\P61.cpp"
LNode * ColAnd(LNode *&ha,LNode *&hb);
LNode * IntersecSet(LNode *&ha,LNode *&hb);
LNode * DifSet(LNode *&ha,LNode *&hb);
int main(void)
{
	LNode *pa,*pb,*pc;
 	InitList(pa);
 	InitList(pb);
	int a[10]={100,80,40,10,0,1,-10,-40,-80,-100};
	int b[10]={99,80,-9,0,2,21,-10,56,78,-100};
	CreateListByTail(pa,a,10);
	ListSort(pa);
	DispList(pa);
	CreateListByTail(pb,b,10);
	ListSort(pb);
	DispList(pb);
	pc=ColAnd(pa,pb);
	DispList(pc);
	DestroyList(pc);
	pc=IntersecSet(pa,pb);
	DispList(pc);
	DestroyList(pc);
	pc=DifSet(pa,pb);
	DispList(pc);
	DestroyList(pc);
	DestroyList(pa);
	DestroyList(pb);
 	system("pause");
    return 0;
}
LNode * ColAnd(LNode *&ha,LNode *&hb)
{
    LNode *p=ha->next,*q=hb->next,*tmp,*hc=(LNode *)malloc(sizeof(LNode)),*tail=hc;
    hc->next=NULL;
    ElemType t;
    while(p!=NULL&&q!=NULL)
    {
        if(p->data<q->data) {t=p->data;p=p->next;}
        else if(p->data==q->data) {t=p->data;p=p->next;q=q->next;}
        	 else {t=q->data;q=q->next;}
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=t;
        tail->next=tmp;
        tail=tmp;
    }
    while(p!=NULL)
    {
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=p->data;
        tail->next=tmp;
        tail=tmp;
        p=p->next;
    }
    while(q!=NULL)
    {
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=q->data;
        tail->next=tmp;
        tail=tmp;
        q=q->next;
    }
    tail->next=NULL;
    return hc;
}    
LNode * IntersecSet(LNode *&ha,LNode *&hb)
{
    LNode *p=ha->next,*q=hb->next,*tmp,*hc=(LNode *)malloc(sizeof(LNode)),*tail=hc;
    hc->next=NULL;
    ElemType t;
    while(p!=NULL&&q!=NULL)
    {
        if(p->data<q->data) {p=p->next;continue;}
        else if(p->data==q->data) {t=p->data;p=p->next;q=q->next;}
        	 else {q=q->next;continue;}
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=t;
        tail->next=tmp;
        tail=tmp;
    }
    tail->next=NULL;
    return hc;
} 
LNode * DifSet(LNode *&ha,LNode *&hb)
{
    LNode *p=ha->next,*q=hb->next,*tmp,*hc=(LNode *)malloc(sizeof(LNode)),*tail=hc;
    hc->next=NULL;
    ElemType t;
    while(p!=NULL&&q!=NULL)
    {
        if(p->data<q->data) {t=p->data;p=p->next;}
        else if(p->data==q->data) {p=p->next;q=q->next;continue;}
        	 else {q=q->next;continue;}
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=t;
        tail->next=tmp;
        tail=tmp;
    }
    while(p!=NULL)
    {
        tmp=(LNode *)malloc(sizeof(LNode));
        tmp->data=p->data;
        tail->next=tmp;
        tail=tmp;
        p=p->next;
    }
    tail->next=NULL;
    return hc;
}    
