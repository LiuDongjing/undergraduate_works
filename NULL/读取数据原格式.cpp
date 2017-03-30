//读取常用数据在计算机内部二进制的存储形式 
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
    printf("i:显示int类型;\nc:显示char类型\nf:显示float类型；\nd:显示double类型;\ne:退出;\n");
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
    printf("请输入int类型数据：\n");
    scanf("%d",&data);
    toBit((long long int)data,sizeof(data)*8);
}
void CtoB(void)
{
    char data;
    printf("请输入char类型数据：\n");
    scanf("%c",&data);
    scanf("%c",&data);//只有写两个输入语句才能正常运行，不明原因。。。 
    toBit((long long int)data,sizeof(data)*8);
}
void FtoB(void)
{
    float data;
    printf("请输入float类型数据：\n");
    scanf("%f",&data);
    FtoI.data=data;
    toBit((long long int)FtoI.trans,sizeof(FtoI.trans)*8);
}
void DtoB(void)
{
    double data;
    printf("请输入double类型数据：\n");
    scanf("%lf",&data);
    DtoL.data=data;
    toBit(DtoL.trans,sizeof(DtoL.trans)*8);
}
