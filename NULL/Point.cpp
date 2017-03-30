#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#define PI 3.141593
#define SIZE 20
typedef struct Point{
    float x;
    float y;
    };
float Distance(Point a,Point b);
Point NextPo(Point a,float dis,float arc);
int main(void)
{
    Point max,min,data[SIZE];
    FILE *f=fopen("C:\\data.txt","r");
    int i=0,j=1,flag=1;
    float k;
    if(f==NULL) {printf("Failed!\n");exit(1);}
    for(;!feof(f);i++) fscanf(f,"%f %f",&data[i].x,&data[i].y);
    //数据之间要有空格 
    max=min=data[0];
    k=(data[0].y-data[1].y)/(data[0].x-data[1].x);
    for(;j<i;j++)
    	{
         if(data[j].x>max.x) max=data[j];
         if(data[j].x<min.x) min=data[j];
         if(fabs((data[0].y-data[j].y)/(data[0].x-data[j].x)-k)>0.000001)
         	{
              printf("不是一条直线！\n");
              flag=0;
              break;
            }
          }
    if(flag) printf("距离：%f\n",Distance(max,min));
    fclose(f);
    system("echo OK!&pause>nul");
    return 0;
}
float Distance(Point a,Point b)
{
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
Point NextPo(Point a,float dis,float arc)
//arc为弧度制，且是直线与X轴正向的夹角 
{
    Point tmp;
    tmp.x=a.x+dis*cos(arc);
    tmp.y=a.y+dis*sin(arc);
    return tmp;
}
