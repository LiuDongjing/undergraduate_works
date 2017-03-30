#include "stdio.h"
#include "stdlib.h"
void mergesort(int a[],int i,int j);
void merge(int b[],int i,int j,int m);
int main(void)
{
    int num[10],i=0;
    for(i;i<10;i++)
    	scanf("%d",&num[i]);
    mergesort(num,0,9);
//	merge(num,0,9,5);
    for(i=0;i<10;i++)
    	printf("%d\t",num[i]);
   	system("pause");
    return 0;
}
void mergesort(int a[],int i,int j)
{
    int m;
    if(i!=j)
    {
        m=(i+j)/2;
        mergesort(a,i,m);
        mergesort(a,m+1,j);
        merge(a,i,j,m);
    }
}
void merge(int b[],int i,int j,int m)
{
    int tmp[j-i+1],pf=i,pe=m+1,n=0;
    while(pf<=m&&(pe<=j))
    	{
         if(b[pf]<b[pe])
         	tmp[n++]=b[pf++];
         else
         	tmp[n++]=b[pe++];
         }
    if(pf>m)
    	for(;pe<=j;pe++)
    		tmp[n++]=b[pe];
    else
    	for(;pf<=m;pf++)
    		tmp[n++]=b[pf];
    for(n=0;i<=j;)
    	b[i++]=tmp[n++];
}
