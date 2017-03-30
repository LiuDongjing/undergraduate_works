#include "F:\\C\\C\\数据结构\\P61.cpp"
Poly * PolyAnd(Poly *&ha,Poly *&hb);
void ListSort(Poly *&L);
int main(void)
{
	Poly *pa,*pb,*pc;
 	pa=(Poly *)malloc(sizeof(Poly));
 	pa->next=NULL;
 	pb=(Poly *)malloc(sizeof(Poly));
 	pb->next=NULL;
	int a[10]={100,80,40,10,0,1,-10,-40,-80,-100};
	float a0[10]={1.2,-1.2,0.8,5.6,7.2,1,0,9,12,0.2};
	int b[10]={99,80,-9,0,2,21,-10,56,78,-100};
	float b0[10]={1.32,-41.2,10.8,-5.6,0.2,11,20,-9,-12,20.2};
	CreateListByTail(pa,a,a0,10);
	ListSort(pa);
	DispList(pa);
	CreateListByTail(pb,b,b0,10);
	ListSort(pb);
	DispList(pb);
	pc=PolyAnd(pa,pb);
	DispList(pc);
	DestroyList(pc);
	DestroyList(pa);
	DestroyList(pb);
 	system("pause");
    return 0;
}
Poly * PolyAnd(Poly *&ha,Poly *&hb)
{
    Poly *p=ha->next,*q=hb->next,*tmp,*hc=(Poly *)malloc(sizeof(Poly)),*tail=hc;
    hc->next=NULL;
    float c;
    int i;
    while(p!=NULL&&q!=NULL)
    {
        if(p->Index<q->Index) {c=p->Coef;i=p->Index;p=p->next;}
        else if(p->Index==q->Index) {c=p->Coef+q->Coef;i=p->Index;p=p->next;q=q->next;}
        	 else {c=q->Coef;i=q->Index;q=q->next;}
        tmp=(Poly *)malloc(sizeof(Poly));
        tmp->Coef=c;
        tmp->Index=i;
        tail->next=tmp;
        tail=tmp;
    }
    while(p!=NULL)
    {
        tmp=(Poly *)malloc(sizeof(Poly));
        tmp->Coef=p->Coef;
        tmp->Index=p->Index;
        tail->next=tmp;
        tail=tmp;
        p=p->next;
    }
    while(q!=NULL)
    {
        tmp=(Poly *)malloc(sizeof(Poly));
        tmp->Coef=q->Coef;
        tmp->Index=q->Index;
        tail->next=tmp;
        tail=tmp;
        q=q->next;
    }
    tail->next=NULL;
    return hc;
}
void ListSort(Poly *&L)
{
    Poly *q=L->next->next,*m,*p;
    L->next->next=NULL;
    while(q!=NULL)
    {
        m=q->next;
        p=L;
        while(p->next!=NULL&&p->next->Index<=q->Index) p=p->next;
        q->next=p->next;
        p->next=q;
        q=m;
    }
}
