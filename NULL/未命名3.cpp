#include <stdio.h>
#include <stdlib.h>
#define size 20
int main(void)
{
    char fName[size],c;
    int iCount=0;
    FILE *fp;
    printf("�������ļ���:");
    scanf("%s",fName);
    fp=fopen(fName,"r");
    if(fp==NULL)
     {
         printf("���ļ�ʧ��!");
         exit(1);
     }
    while(!feof(fp))
     {
         fscanf(fp,"%c",&c);
         if(c=='\n')
          iCount++;
     }
    printf("����%d��.",iCount);
    system("pause");
    return 0;
}
