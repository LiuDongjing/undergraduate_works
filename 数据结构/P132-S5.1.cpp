#include "stdlib.h"
#include "stdio.h"
typedef struct POINT
{
    int x;
    int y;
};
bool Judge(bool a[][5],POINT F,POINT L);
int main(void)
{
    bool map[5][5]={{true,true,false,true,false},{false,true,false,true,false},{true,false,false,true,false},{true,true,false,true,true},{true,true,false,true,false}};
    int i,j;
    POINT A,B;
    A.x=0;A.y=0;
    B.x=0;B.y=0;
    for(i=0;i<5;i++)
    {
        for(j=0;j<5;j++) printf("%d ",map[i][j]);
        printf("\n");
    }
    printf("%d",Judge(map,A,B));
    system("pause");
    return 0;
}       
bool Judge(bool a[][5],POINT F,POINT L)
{
    int k,i,max,min;
    if(F.x==L.x)
    {
        max=F.y>=L.y?F.y:L.y;
        min=F.y<=L.y?F.y:L.y;
        for(i=min;i<=max;i++)
        	if(a[i][F.x]==true) return false;
        return true;
    }
    k=(F.y-L.y)/(F.x-L.x);
    max=F.x>=L.x?F.x:L.x;
    min=F.x<=L.x?F.x:L.x;
    for(i=min;i<=max;i++)
   		if(a[k*(i-F.x)+F.y][i]==true) return false;
    return true;
}
