#include <stdio.h>
#include <stdlib.h>
#define size 20
int main(void)
{
    char str[size];
    int i,left=0,right=0,flag=1;
    printf("请输入一个字符串.\n");
    scanf("%19s",str);
    for(i=0;str[i]!='\0';i++)
     {
         switch(str[i])
          {
              case '(':
                  left++;break;
              case ')':
                  right++;break;
          }
         if(right>left)
          {
              flag=0;
              break;
          }
     }
    if(left==right&&flag)
     printf("满足条件。\n");
    else
     printf("不满足条件。\n");
    system("pause");
    return 0;
}
