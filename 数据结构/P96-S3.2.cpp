#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
    Type_5 a[5]={'a','b','c','d','e'},tmp;
    int i=0;
    LiStack *ST;
    InitStack(ST);
    LiStack *p=ST;
    printf("%d\n",EmptyStack(ST));
    for(;i<5;i++) Push(ST,a[i]);
    printf("%d\n",EmptyStack(ST));
    printf("%d\n",GetSize(ST));
    while(p->next!=NULL) {printf("%c\t",p->next->data);p=p->next;}
    while(GetTop(ST,tmp)) {Pop(ST,tmp);printf("%c\t",tmp);}
    printf("%d\n",EmptyStack(ST));
    DestroyStack(ST);
    system("pause");
    return 0;
}
