#include "stdio.h"
#include "stdlib.h"
#include "time.h"
int main(void)
{ 
    time_t end=time(NULL);
    tm *local;
    local=localtime(&end);
    printf("%d/%d/%d\t%d:%d:%d\n",1900+local->tm_year,local->tm_mon+1,local->tm_mday,local->tm_hour,local->tm_min,local->tm_sec);
    system("pause");
    return 0;
}
