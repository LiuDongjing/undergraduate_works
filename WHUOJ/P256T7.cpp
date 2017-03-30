#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
void sums(float a[],int len,float *p_sum,float *n_sum,int *p_count,int *n_count);
int main(void)
{
    float n[SIZE];
    float P_sum=0,N_sum=0;
    int P_count=0,N_count=0,i=0;
    for(;i<SIZE;i++)
    	scanf("%f",&n[i]);
   	sums(n,SIZE,&P_sum,&N_sum,&P_count,&N_count);
   	printf("%f %f %d %d",P_sum,N_sum,P_count,N_count);
    system("pause");
    return 0;
}
void sums(float a[],int len,float *p_sum,float *n_sum,int *p_count,int *n_count)
{
    for(;len>=0;len--)
    	{
         if(a[len-1]>0)
    		{*p_sum=*p_sum+a[len-1];*p_count=*p_count+1;}
   		 if(a[len-1]<0)
    		{*n_sum=*n_sum+a[len-1];*n_count=*n_count+1;}
   		}
}
