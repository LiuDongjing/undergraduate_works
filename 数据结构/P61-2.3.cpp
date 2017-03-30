#include "F:\\C\\C\\数据结构\\P61.cpp"
void Delete(SqList *&L);
int main(void)
{
	SqList *p;
 	InitList(p);
	int a[10]={100,80,40,10,0,0,-10,-40,-80,-100};
	int n=0;
	for(;n<10;n++)
		ListInsert(p,1,a[n]);
	DispList(p);
	Delete(p);
	DispList(p);
	DestroyList(p);
 	system("pause");
    return 0;
}
void Delete(SqList *&L)
{
    int i=0,j=L->Length-1,count=0,tmp;
    while(i<j)
    {
        while(L->data[i]<0) i++;
        while(L->data[j]>=0) j--;
        if(i<j)
        	{
             tmp=L->data[i];
             L->data[i]=L->data[j];
             L->data[j]=tmp;
             }
    }
}
