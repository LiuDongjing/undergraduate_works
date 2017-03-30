//限于整数的加减乘除 
#include "stdlib.h"
#include "stdio.h"
#define SIZE 20
typedef struct OpRank
{
    char op;
    int rank;
};
typedef struct stack
{
    char data[SIZE];
    int top;
};
OpRank Lp[5]={'+',2,'-',2,'*',4,'/',4,'(',6},
	Rp[6]={'+',3,'-',3,'*',5,'/',5,'(',1,'=',0};
bool Comp(char lc,char rc);
void Trans(char Exp[],char PostExp[]);
int Cal(char PostExp[]);
int main(void)
{
    char exp[20]="1+((2-7)*3-10)",postexp[40];
    Trans(exp,postexp);
    printf("\n%s\n",postexp);
    printf("\n%d\n",Cal(postexp));
    system("pause");
    return 0;
}
bool Comp(char lc,char rc)
{
    int l,r,i;
    for(i=0;i<5;i++)
    	if(Lp[i].op==lc){l=Lp[i].rank;break;}
    for(i=0;i<6;i++)
    	if(Rp[i].op==rc){r=Rp[i].rank;break;}
    return l>r;
}
void Trans(char Exp[],char PostExp[])
{
    stack Ops;
    Ops.top=0;
    Ops.data[Ops.top]='=';
    char tmp;
    int i=0,j=0;
    for(;Exp[i];i++)
    	if(Exp[i]>='0'&&Exp[i]<='9')
     		{
           		while(Exp[i]>='0'&&Exp[i]<='9')
       			{
         		    PostExp[j]=Exp[i];
           			i++;
           			j++;
              	}
               	PostExp[j]='#';
                j++;i--;
           }
       else if(Exp[i]==')')while(true)
       		{
             tmp=Ops.data[Ops.top];Ops.top--;
             if(tmp=='(')break;
             else{PostExp[j]=tmp;j++;}
             }
       else if(Comp(Exp[i],Ops.data[Ops.top])){Ops.top++;Ops.data[Ops.top]=Exp[i];}
       else {
           	while(!Comp(Exp[i],Ops.data[Ops.top]))
       		{
             PostExp[j]=Ops.data[Ops.top];Ops.top--;
             j++;
             }
             Ops.top++;Ops.data[Ops.top]=Exp[i];
             } 	    	
   	while(Ops.top!=-1)
   	{
        PostExp[j]=Ops.data[Ops.top];Ops.top--;
        j++;
    }
    PostExp[j]='\0';
}
int Cal(char PostExp[])
{
    struct {int data[SIZE/2];int top;}Num;
    Num.top=-1;
    int i=0,tmp=0;
    while(PostExp[i]!='=')
    {
        if(PostExp[i]>='0'&&PostExp[i]<='9')
        {
            tmp=0;
            while(PostExp[i]!='#')
            {
                tmp=tmp*10+(PostExp[i]-'0');
                i++;
            }
            i++;
            Num.top++;Num.data[Num.top]=tmp;
        }
        else {
            switch(PostExp[i])
        	{
             case '+':Num.data[Num.top-1]+=Num.data[Num.top];Num.top--;break;
             case '-':Num.data[Num.top-1]-=Num.data[Num.top];Num.top--;break;
             case '*':Num.data[Num.top-1]*=Num.data[Num.top];Num.top--;break;
             case '/':Num.data[Num.top-1]/=Num.data[Num.top];Num.top--;break;
             }
             i++;
             }
         }
        return Num.data[Num.top];
}    
