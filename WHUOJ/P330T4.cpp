#include <stdio.h>
#include <stdlib.h>
#define size 30
struct fbook
{
    char cBook[20];
    char cAuthor[20];
    char cPublisher[20];
    float fee;
    unsigned int uiNum;
    char cClass[20];
}book[size];
int main(void)
{
    FILE *fB;
    char cFlag='t';
    int iCount=0,i=0;
    while((cFlag!='e')&&(iCount<size))
     {
         printf("\t\t请输入第%d条记录：\n",iCount+1);
         printf("书名：");
         scanf("%s",&(book[iCount].cBook));
         printf("作者：");
         scanf("%s",&(book[iCount].cAuthor));
         printf("出版商：");
         scanf("%s",&(book[iCount].cPublisher));
         printf("单价：");
         scanf("%f",&(book[iCount].fee));
         printf("库存数目：");
         scanf("%u",&(book[iCount].uiNum));
         printf("类别：");
         scanf("%s",&(book[iCount].cClass));
         iCount++;
         printf("输入'e'结束录入工作，其他继续录入...\n");
         fflush(stdin);
         scanf("%c",&cFlag);
         fflush(stdin);
     }
    fB=fopen("c:\\book.dat","a");
    if(fB==NULL)
     {
         printf("打开文件失败！\n");
         system("pause");
         exit(1);
     }
    while((!feof(fB))&&(i<iCount))
     {
         fprintf(fB,"书名：%s\t作者：%s\t出版商：%s\t单价：%f\t库存数目：%u\t类别：%s\n",book[i].cBook,book[i].cAuthor,book[i].cPublisher,book[i].fee,book[i].uiNum,book[i].cClass);
         i++;
     }
    fclose(fB);
    printf("创建完毕！\n");
    system("pause");
    return 0;
}
