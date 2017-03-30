#include <stdio.h>
#include <stdlib.h>
int main(void)
{
    printf("hhhh");
    //fseek(stdin,-4,SEEK_CUR);
    rewind(stdout);
    printf("xxx");
    system("pause");
    fflush(stdin);
    system("pause");
    return 0;
}
