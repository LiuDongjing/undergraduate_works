#include <stdio.h>
#include <stdlib.h>
#define size 20
int main(void)
{
    char fName[size],c;
    int iCount=0;
    FILE *fp;
    printf("请输入文件名:");
    scanf("%s",fName);
    fp=fopen(fName,"r");
    if(fp==NULL)
     {
         printf("打开文件失败!");
         exit(1);
     }
    while(!feof(fp))
     {
         fscanf(fp,"%c",&c);
         if(c=='\n')
          iCount++;
     }
    printf("共有%d行.",iCount);
    system("pause");
    return 0;
}
