#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    int iMar,i;
    float fNum,fVal=0;
    printf("�����������Ʒ�ź�ÿ�����������:\n");
    for(i=1;i<=5;i++)
     {
         printf("\n��Ʒ�ţ�");
         scanf("%d",&iMar);
         printf("����������");
         scanf("%f",&fNum);
         switch(iMar)
          {
              case 1:
                  printf("\n1�Ų�Ʒ�ĵ�����2.98Ԫ��");
                  fVal=fVal+2.98*fNum;
                  break;
              case 2:
                  printf("\n2�Ų�Ʒ�ĵ�����4.50Ԫ��");
                  fVal=fVal+4.50*fNum;
                  break;
              case 3:
                  printf("\n3�Ų�Ʒ�ĵ�����9.98Ԫ��");
                  fVal=fVal+9.98*fNum;
                  break;
              case 4:
                  printf("\n4�Ų�Ʒ�ĵ�����4.49Ԫ��");
                  fVal=fVal+4.49*fNum;
                  break;
              case 5:
                  printf("\n5�Ų�Ʒ�ĵ�����6.87Ԫ��");
                  fVal=fVal+6.87*fNum;
                  break;
          }
    }
    printf("\n���ܵ������۶��ǣ�%f\n",fVal*7);
    system("pause");
    return 0;
}
