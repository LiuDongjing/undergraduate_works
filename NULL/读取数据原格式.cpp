//��ȡ���������ڼ�����ڲ������ƵĴ洢��ʽ 
#include <stdio.h>
#include <stdlib.h>
union {
    	long long int x;
    	struct{
     	unsigned int a:63;
     	unsigned int y:1;
       	}bit;   	
      }bit_64;
union {
    	long int trans;
     	float data;
      }FtoI;
union {
    	long long int trans;
     	double data;
      }DtoL;
void toBit(long long int,int);
void ItoB(void);
void CtoB(void);
void FtoB(void);
void DtoB(void);
int main(void)
{
    char choose;
    printf("i:��ʾint����;\nc:��ʾchar����\nf:��ʾfloat���ͣ�\nd:��ʾdouble����;\ne:�˳�;\n");
    scanf("%c",&choose);
    while(choose!='e')
    	{
         switch(choose)
         	{
              case 'i':
                  ItoB();break;
              case 'c':
                  CtoB();break;
              case 'f':
                  FtoB();break;
              case 'd':
                  DtoB();break;
              }
          scanf("%c",&choose);
         }
    system("pause");
    return 0;
}
void toBit(long long int num,int size)
{
    num=num<<(64-size);
    for(int i=0;i<size;i++)
     {
         bit_64.x=num;
         printf("%u",bit_64.bit.y);
         num=num<<1;
     }
    printf("\n");
}
void ItoB(void)
{
    int data;
    printf("������int�������ݣ�\n");
    scanf("%d",&data);
    toBit((long long int)data,sizeof(data)*8);
}
void CtoB(void)
{
    char data;
    printf("������char�������ݣ�\n");
    scanf("%c",&data);
    scanf("%c",&data);//ֻ��д���������������������У�����ԭ�򡣡��� 
    toBit((long long int)data,sizeof(data)*8);
}
void FtoB(void)
{
    float data;
    printf("������float�������ݣ�\n");
    scanf("%f",&data);
    FtoI.data=data;
    toBit((long long int)FtoI.trans,sizeof(FtoI.trans)*8);
}
void DtoB(void)
{
    double data;
    printf("������double�������ݣ�\n");
    scanf("%lf",&data);
    DtoL.data=data;
    toBit(DtoL.trans,sizeof(DtoL.trans)*8);
}
