#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    float YL,GL,d;
    d=1.609344;
    printf("������Ӣ�");
    scanf("%f",&YL);
    while(YL<0)
    {
        printf("��������ݲ���ʵ�ʣ����������룡\nӢ�");
        scanf("%f",&YL);
    }
    GL=d*YL;
    printf("ת������%f���\n",GL);
    system("pause");
    return 0;
}
