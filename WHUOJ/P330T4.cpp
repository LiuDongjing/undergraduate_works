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
         printf("\t\t�������%d����¼��\n",iCount+1);
         printf("������");
         scanf("%s",&(book[iCount].cBook));
         printf("���ߣ�");
         scanf("%s",&(book[iCount].cAuthor));
         printf("�����̣�");
         scanf("%s",&(book[iCount].cPublisher));
         printf("���ۣ�");
         scanf("%f",&(book[iCount].fee));
         printf("�����Ŀ��");
         scanf("%u",&(book[iCount].uiNum));
         printf("���");
         scanf("%s",&(book[iCount].cClass));
         iCount++;
         printf("����'e'����¼�빤������������¼��...\n");
         fflush(stdin);
         scanf("%c",&cFlag);
         fflush(stdin);
     }
    fB=fopen("c:\\book.dat","a");
    if(fB==NULL)
     {
         printf("���ļ�ʧ�ܣ�\n");
         system("pause");
         exit(1);
     }
    while((!feof(fB))&&(i<iCount))
     {
         fprintf(fB,"������%s\t���ߣ�%s\t�����̣�%s\t���ۣ�%f\t�����Ŀ��%u\t���%s\n",book[i].cBook,book[i].cAuthor,book[i].cPublisher,book[i].fee,book[i].uiNum,book[i].cClass);
         i++;
     }
    fclose(fB);
    printf("������ϣ�\n");
    system("pause");
    return 0;
}
