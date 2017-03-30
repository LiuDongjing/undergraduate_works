#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#define SIZE 10
#define STRSIZE 40
#define TREE 20
typedef struct BTree
{
    char data;
    BTree *L_child;
    BTree *R_child;
};
typedef struct DIR
{char mydir[STRSIZE];};
BTree * createBtree(int n,char sq[]);
void toArray(int i,char sq[],BTree *p);
void CreatTree(BTree *&bt,char *str);
void ShowTree(BTree *b,DIR dir);
BTree *FindNode(BTree *b,char x);
void DispBTree(BTree *b);
bool IsParent(BTree *b,char x,char y);
BTree * CreateTree(char *str);
void PreOrder(BTree *b);
bool IsBST(BTree *b); 
int main(void)
{
	//int i=0;
    //char tmp[SIZE],tree[SIZE]={'A','B','C','D','#','E','F','#','G','#'};
    //for(;i<10;i++)
    //	tmp[i]='#';
    BTree *t=CreateTree("D(B(A(),C()),F(E(),G()))");
    DIR CMD={"md E:"};
    ShowTree(t,CMD);
    printf("\n%d",IsBST(t));
    //PreOrder(t);
    //DispBTree(t);
    //printf("\n");
    //printf("\n%d\n",IsParent(FindNode(t,'A'),'G','E'));
    //toArray(0,tmp,t);
    //BTree *s=createBtree(0,tmp);
    //CreatTree(s,"A(B(D(,G)),C(E,F))");
    //toArray(0,tmp,s);
    //DispBTree(s);
    /*for(i=0;i<10;i++)
    	printf("%c\t",tmp[i]);*/
    system("pause");
    return 0;
}
BTree * createBtree(int n,char sq[])
{
    if(sq[n]=='#'||n>=SIZE)
    	return NULL;
    BTree *p=(BTree *)malloc(sizeof(BTree));
    p->data=sq[n];
    p->L_child=createBtree(2*n+1,sq);
    p->R_child=createBtree(2*n+2,sq);
    return p;
}
void toArray(int i,char sq[],BTree *p)
{
    if(p==NULL)
    	sq[i]='#';
    else
    {
        sq[i]=p->data;
        toArray(2*i+1,sq,p->L_child);
        toArray(2*i+2,sq,p->R_child);
    }
}
void CreatTree(BTree *&bt,char *str)
{
    typedef struct status
    {
        BTree *position;
        int childs;
    };
    status stack[20];
    int top=-1;
    char *c=str;
    BTree *p=NULL;
    for(;*c!='\0';c++)
    {
        switch(*c)
        {
            case '(':stack[top].childs=1;break;
            case ')':top--;break;
            case ',':stack[top].childs=2;break;
            default:p=(BTree *)malloc(sizeof(BTree));
            		p->data=*c;
              		p->L_child=p->R_child=NULL;
                	if(bt==NULL) bt=p;
                 	else switch(stack[top].childs)
                  			{
                         		case 0:top--;break;
                           		case 1:stack[top].position->L_child=p;break;
                             	case 2:stack[top].position->R_child=p;break;
                             }
                    top++;stack[top].position=p;
                    stack[top].childs=0;break;
            }
    }
}
BTree *FindNode(BTree *b,char x)
{
    if(b==NULL) return NULL;
    if(b->data==x) return b;
    BTree *p=FindNode(b->L_child,x);
    if(p==NULL) return FindNode(b->R_child,x);
    return p;
}
void DispBTree(BTree *b)
{
    if(b!=NULL)
    {
        printf("%c",b->data);
        if(b->L_child!=NULL||b->R_child!=NULL)
        {
            printf("(");
            DispBTree(b->L_child);
            if(b->R_child!=NULL) 
            {
                printf(",");DispBTree(b->R_child);
            }
            printf(")");
        }
    }
}
bool IsParent(BTree *b,char x,char y)
{
    static int n=0;
    if(b==NULL) return false;
    if(b->data==x) n++;
    if(b->data==y) n++;
    IsParent(b->L_child,x,y);
    IsParent(b->R_child,x,y);
    if(n==2) return true;
    return false;
}
void ShowTree(BTree *b,DIR dir)
{
    if(b!=NULL)
    {
        char tmp[]={'\\','\\',b->data,'\0'};
        strcat(dir.mydir,tmp);
        system(dir.mydir);
        ShowTree(b->L_child,dir);
        ShowTree(b->R_child,dir);
    char root[]={'m','d',' ','E',':','\\','\\',b->data,'\0'};
    if(!strcmp(dir.mydir,root))
    {
        char cmd[STRSIZE];
        int i=5,j=3;
        strcpy(cmd,"tree ");
        for(;dir.mydir[j-1]!='\0';i++,j++)
        	cmd[i]=dir.mydir[j];
        system(cmd);
        strcpy(cmd,"rd /s /q ");
        for(i=9,j=3;dir.mydir[j-1]!='\0';i++,j++)
        	cmd[i]=dir.mydir[j];
       	system(cmd);
    }
    }
}
/*void ShowTree(BTree *b,DIR dir)
{
    char ch[]={'©À','©¸','©¦','©¤','','','',''}} */
BTree * CreateTree(char *str)
{
    struct {BTree *pointer;int status;}stack[TREE];
    char *cp=str;
    int top=-1;
    BTree *p,*back=NULL;
    for(;*cp!='\0';cp++)
    {
        switch(*cp)
        {
            case '(':stack[top].status=1;break;
            case ')':back=stack[top].pointer;top--;break;
            case ',':stack[top].status=2;break;
            default:p=(BTree*)malloc(sizeof(BTree));p->data=*cp;
            		p->L_child=p->R_child=NULL;top++;stack[top].pointer=p;
              		stack[top].status=0;break;
        }
        if(back!=NULL)
        if(top<0) return back;
        else
        {
            switch(stack[top].status)
            {
                case 1:stack[top].pointer->L_child=back;back=NULL;break;
                case 2:stack[top].pointer->R_child=back;back=NULL;break;
            }
        }
    }
}
void PreOrder(BTree *b)
{
    struct {BTree *pointer;int flag;bool yes;}stack[TREE];
    int top=0;stack[top].pointer=b;
    stack[top].flag=0;stack[top].yes=true;
    while(top>-1)
    {
        printf("%c\n",stack[top].pointer->data);
        if(stack[top].yes){printf("%c",stack[top].pointer->data);stack[top].yes=false;};
        switch(stack[top].flag)
        {
            case 0:if(stack[top].pointer->L_child!=NULL){top++;stack[top].pointer=stack[top-1].pointer->L_child;stack[top].flag=0;stack[top].yes=true;}
            		stack[top-1].flag=1;break;
            case 1:if(stack[top].pointer->R_child!=NULL){top++;stack[top].pointer=stack[top-1].pointer->R_child;stack[top].flag=0;stack[top].yes=true;}
            		stack[top-1].flag=2;break;
            case 2:top--;break;
        }
    }
}
bool IsBST(BTree *b)
{
    if(b==NULL)
    	return true;
    else
    	{
         bool flag=(b->L_child==NULL || b->L_child->data<b->data)
       		  && (b->R_child==NULL || b->R_child->data>b->data);
         return flag&&IsBST(b->L_child)&&IsBST(b->R_child);
         }
}
