#include <stdio.h>
#include <stdlib.h>
int main(int argc,char *argc[])
{
    char pa,pb;
    unsigned long int i=0;
    FILE *fa,*fb;
    fa=fopen(*argc[0],"r");
    fb=fopen(*argc[1],"r");
    if((fa==NULL)||(fb==NULL))
     printf("���ļ�ʧ�ܣ�\n");
    while((!feof(fa))&&(!feof(fb)))
     {
         pa=fgetc(fa);
         pb=fgetc(fb);
         if(pa!=pb)
          i++;
     }
     if((i==0)&&feof(pa)&&feof(pb))
      printf("�����ļ���ȫһ����\n");
     else
      printf("�����ļ���ͬ��%ul",i);
     fclose(fa);
     fclose(fb);
     return 0;
} 
