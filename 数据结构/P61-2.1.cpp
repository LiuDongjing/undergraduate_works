#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
    SqList *Line;
    ElemType tmp;
    InitList(Line);
    ElemType array[5]={'a','b','c','d','e'};
    int i=0;
    for(;i<5;i++) ListInsert(Line,1,array[i]);
    for(i=0;i<Line->Length;i++) printf("%c\t",Line->data[i]);
    printf("\n");
    printf("Length:%d\n",Line->Length);
    printf("List is empty? %d\n",ListEmpty(Line));
    printf("Location 3:%c\n",Line->data[2]);
    tmp='a';
    printf("'a' is located in %d\n",LocateElem(Line,tmp));
    tmp='f';
    ListInsert(Line,4,tmp);
    DispList(Line);
    ListDelete(Line,3,tmp);
    DispList(Line);
    DestoryList(Line);
    system("pause");
    return 0;
}
