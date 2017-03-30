#include "stdio.h"
#include "stdlib.h"
#define SIZE 20
typedef struct ExpStack
{
    char data[SIZE];
    int top;
}; 
bool Match(char str[],ExpStack &s);
int main(void)
{
    char exp[]="{[()]}[()]()";
    ExpStack Es;
    Es.top=-1;
    Match(exp,Es)?printf("True\n"):printf("False\n");
    system("pause");
    return 0;
}
bool Match(char str[],ExpStack &s)
{
    int i=0;
    bool flag=false;
    for(;str[i]!='\0';i++)
    {
        switch(str[i])
        {
            case '{':
                if(s.top==-1&&str[i+1]=='[') 
                 {s.top++;s.data[s.top]='{';}
                else flag=true;break;
            case '[':
                if((s.top==-1||s.data[s.top]=='{')&&(str[i+1]=='(')) 
                 {s.top++;s.data[s.top]='[';}
                else flag=true;break;
            case '(':
                if(s.top==-1||s.data[s.top]=='[') 
                 {s.top++;s.data[s.top]='(';}
                else flag=true;break;
            case '}':
                if(s.data[s.top]=='{') s.top--;
                else flag=true;break;
            case ']':
                if(s.data[s.top]=='[') s.top--;
                else flag=true;break;
            case ')':
                if(s.data[s.top]=='(') s.top--;
                else flag=true;break;
        }
        if(flag) return false;
    }
    return s.top==-1;
}
