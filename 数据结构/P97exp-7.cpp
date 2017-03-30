#include "stdio.h"
#include "stdlib.h"
typedef struct Patient
{
    int num;
    Patient *next;
};
void enQueue(Patient *&r,int n);
bool deQueue(Patient *&r,int &n);
void showQueue(Patient *&r);
void quitQueue(Patient *&r);
void showMenu(int n,bool f);
int main(void)
{
    Patient *rear=NULL;
    int chioce,c,now=-1;
    bool flag=true;
    while(1)
    {
    system("cls");
    showMenu(now,flag);
    scanf("%d",&chioce);
    switch(chioce)
    {
        case 1:printf("\n请输入排队号...");
                scanf("%d",&c);enQueue(rear,c);break;
        case 2:flag=deQueue(rear,now);break;
        case 3:showQueue(rear);break;
        case 4:quitQueue(rear);exit(0);
        case 5:exit(0);
        default:printf("Wrong!\n");system("pause>nul");}
    }
}
void enQueue(Patient *&r,int n)
{
    Patient *temp=(Patient *)malloc(sizeof(Patient));
    temp->num=n;
    if(r==NULL)
    {
        r=temp;
        r->next=r;
    }
    else
    {
        temp->next=r->next;
        r->next=temp;
        r=temp;
    }
}
bool deQueue(Patient *&r,int &n)
{
    if(r!=NULL)
    {
        Patient *temp;
        if(r->next==r)
        {
            n=r->num;
            free(r);
            r=NULL;
            return true;
        }
        else
        {
            temp=r->next;
            r->next=temp->next;
            n=temp->num;
            free(temp);
            return true;
        }
    }
    else return false;
}
void showQueue(Patient *&r)
{
    Patient *p;
    if(r!=NULL)
    {
        p=r->next;
        while(p!=r)
        {
            printf("%d\t",p->num);
            p=p->next;
        }
        printf("%d\n",p->num);
    }
    system("pause");
}
void quitQueue(Patient *&r)
{
    Patient *temp,*p;
    if(r!=NULL)
    {
        p=r->next;
        r->next=NULL;
        while(p!=NULL)
        {
            temp=p->next;
            printf("\t%d",p->num);
            free(p);
            p=temp;
        }
    }
}
void showMenu(int n,bool f)
{
    printf("\t\t\t***MENU***\n");
    printf("\t\t\t1:排队;\n");
    printf("\t\t\t2:就诊;\n");
    printf("\t\t\t3:查看排队;\n");
    printf("\t\t\t4:余下依次就诊;\n");
    printf("\t\t\t5:下班。\n");
    if(n!=-1&&f) printf("\t\t\t当前就诊：%d ...\n",n);
    else printf("\t\t\t当前无人就诊...\n");
    printf("\t\t\t**********\n");
}
