#include "F:\\C\\C\\数据结构\\P61.cpp"
bool Delete(SqList *&L,int x,int y);
int main(void)
{
	SqList *p;
 	InitList(p);
	int a[10]={-1,20,13,45,99,-109,-98,0,1999,1};
	int n=0;
	for(;n<10;n++)
		ListInsert(p,1,a[n]);
	DispList(p);
	Delete(p,-10,60);
	DispList(p);
	DestroyList(p);
 	system("pause");
    return 0;
}
bool Delete(SqList *&L,int x,int y)
{
    if(x>=y) return false;
    int i=0,j=L->Length-1,count=0,tmp;
    while(i<j)
    {
        while(L->data[i]<x||L->data[i]>y) i++;
        while(L->data[j]>=x&&L->data[j]<=y) j--;
        if(i<j)
        	{
             tmp=L->data[i];
             L->data[i]=L->data[j];
             L->data[j]=tmp;
             }
    }
    L->Length=i;//i是从0开始的 
    return true;
}
