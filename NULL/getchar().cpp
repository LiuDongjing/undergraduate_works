#include <stdio.h>
#include <stdlib.h>
int main ()
{
    char str;
    printf("please enter a text\n");
    str=getchar();
    printf("%c",str);
    system("pause");
    str=getchar();
    printf("%c\n",str);
    printf("%p\n",&str);
    system("pause");
    return 0;
}
