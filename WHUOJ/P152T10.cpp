#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int time(int,int,int);
int main(void)
{
    int hour1,hour2,min1,min2,sec1,sec2;
    printf("�������һ��ʱ�䣨ʱ���֡��룩:\n");
    scanf("%d %d %d",&hour1,&min1,&sec1);
    printf("������ڶ���ʱ�䣨ʱ���֡��룩:\n");
    scanf("%d %d %d",&hour2,&min2,&sec2);
    printf("���%d�룡\n",abs(time(hour1,min1,sec1)-time(hour2,min2,sec2)));
    system("pause");
    return 0;
}
int time(int hour,int min,int sec)
{
    return hour*3600+min*60+sec;
} 
