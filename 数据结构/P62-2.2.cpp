#include "F:\\C\\C\\数据结构\\P61.cpp"
int main(void)
{
    LNode *head;
    ElemType array[5]={'a','b','c','d','e'},tmp;
    InitList(head);
    CreateListByTail(head,array,5);
    DispList(head);
    GetElem(head,3,tmp);
    printf("L:%d Epy:%d @3:%c\n",ListLength(head),ListEmpty(head),tmp);
    tmp='a';
    printf("a:%d\n",LocateElem(head,tmp));
    tmp='f';
    ListInsert(head,4,tmp);
    DispList(head);
    ListDelete(head,3,tmp);
    DispList(head);
    DestroyList(head);
    system("pause");
    return 0;
}
