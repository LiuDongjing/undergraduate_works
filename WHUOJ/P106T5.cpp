#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main(void)
{
    float a,b,c,v;
    printf("������X^2��ϵ����a=");
    scanf("%f",&a);
    printf("������X��ϵ����b=");
    scanf("%f",&b);
    printf("�����볣ϵ����c=");
    scanf("%f",&c);
    v=sqrt(pow(b,2)-4*a*c);
    if(v<0)
    	printf("�˷����޽⣡");
    else
  		printf("����%fx^2+%fx+%f=0�Ľ��ǣ�x1=%f;x2=%f",a,b,c,(v-b)/(2*a),(-v-b)/(2*a));
    printf("\n");
    system("pause");
    return 0;
}
