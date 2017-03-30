#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
    ElemTypeD a[5]={'a','b','c','d','e'},tmp;
    int i=0;
    SqStack *ST;
    InitStack(ST);
    printf("%d\n",EmptyStack(ST));
    for(;i<5;i++) Push(ST,a[i]);
    printf("%d\n",EmptyStack(ST));
    printf("%d\n",ST->top+1);
    for(i=ST->top;i>=0;i--) printf("%c\t",ST->data[i]);
    for(;ST->top!=-1;) {Pop(ST,tmp);printf("%c\t",tmp);}
    printf("%d\n",EmptyStack(ST));
    DestroyStack(ST);
    system("pause");
    return 0;
}
