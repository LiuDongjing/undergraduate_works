#include <stdio.h>
#include <stdlib.h>
struct Byte{
		int a:1;
 		int b:1;
  		int c:1;
   		};
struct we{
    	int d:1;
     	}
union convey{
        	int i;
         	struct Byte wei;
          }iTob;
int main(void)
{
    iTob.i=1;
    struct we *p=&iTob.wei.a;
    printf("%d",*p);
    system("pause");
    return 0;
}
