#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define size 30
#define amount 5
int seek(char tar[],char key[]);
int main(void)
{
    char target[size];
    char keyword[amount][size]={"you","are","a","smart","you"};
    int i;
    printf("string:\n");
    gets(target);
    for(i=0;i<amount;i++)
     printf("关键字%s出现的次数是：%d\n",keyword[i],seek(target,keyword[i]));
    system("pause");
    return 0;
}
int seek(char tar[],char key[])
{
    int iCount=0,j=0,num=0;
    char temp[size];
    while(iCount+strlen(key)<=strlen(tar))
     {
         for(j=0;j<strlen(key);j++)
          temp[j]=tar[j+iCount];
         temp[j+1]='\0';
         printf("%s",temp);
         if(!strcmp(key,temp))
              num++;
         iCount++;
     }
     return num;
}
