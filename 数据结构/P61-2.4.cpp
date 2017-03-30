#include "F:\\C\\C\\数据结构\\P61.cpp"
void Reverse(LNode *&L);
int main(void)
{
    LNode *chain;
    int w[10]={0,-1,0,-192,100,6,9999,19,9,-10};
    InitList(chain);
    CreateListByTail(chain,w,10);
    DispList(chain);
    //Reverse(chain);
    ListSort(chain);
    DispList(chain);
    system("echo OK!&pause>nul");
    DestroyList(chain);
    return 0;
}
void Reverse(LNode *&L)
{
    LNode *p=L->next,*q=p->next;
    L->next=NULL;
    while(q!=NULL)
    {
        p->next=L->next;
        L->next=p;
        p=q;
        q=p->next;
    }
    p->next=L->next;
    L->next=p;
}
