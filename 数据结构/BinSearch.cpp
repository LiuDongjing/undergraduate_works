#include "stdio.h"
#include "stdlib.h"
int BinSearch(int R[],int lengh,int mekey);
int main(void)
{
    int a[10]={-1,22,23,34,54,63,67,88,91,101};
    printf("%d",BinSearch(a,10,0));
    system("pause");
    return 0;
}
int BinSearch(int R[],int length,int mekey)
{
    int low=0,high=length-1,mid;
    while(low<high)
    {
        mid=(low+high)/2;
        if(R[mid]==mekey)
        	return mid;
        if(R[mid]>mekey)
        	high=mid-1;
        else low=mid+1;
    }
    if(R[low]==mekey)
    	return low;
    else return -1;
}
