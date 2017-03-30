#include "stdlib.h"
#include "stdio.h"
#include "time.h"
#define PRICE_P_MIN 5
#define PARK 5
#define WAIT_AREA 2
typedef struct Park_Area
{
    unsigned long int Car[PARK];
    int p_top;
};
typedef struct Wait_Area
{
    unsigned long int w_Car[WAIT_AREA];
    int w_front,w_count;
};
typedef struct Node
{
    tm Chec_In;
    tm Chec_Out;
    unsigned long int id;
    bool status;
    float charge;
    Node *next;
};
void showMenu(void);
void checkIn(Node *&h,Park_Area *&_p,Wait_Area *&_w);
void checkOut(Node *&h,Park_Area *&_p,Wait_Area *&_w);
void showLog(Node *l);
bool isInPark(unsigned long int n,Park_Area *_p);
int main(void)
{
    time_t now;
    tm *local;
    Park_Area *p=(Park_Area*)malloc(sizeof(Park_Area));
    Wait_Area *w=(Wait_Area*)malloc(sizeof(Wait_Area));
    p->p_top=-1;
    w->w_front=0;
    w->w_count=0;
    Node *head=NULL;
    int sel;
    while(1)
    {
        system("cls");
        showMenu();
        scanf("%d",&sel);
        switch(sel)
        {
            case 1:checkIn(head,p,w);break;
            case 2:checkOut(head,p,w);break;
            case 3:showLog(head);break;
            case 4:printf("��Ҫ�˳�?");system("pause");exit(0);
            default:break;
        }
    }
    return 0;
}
void showMenu(void)
{
    time_t n=time(NULL);
    tm *local=localtime(&n);
    printf("\t\t\t\t*ͣ��������*\n");
    printf("\t\t\t\t %d-%d-%d\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
    printf("\t\t\t\t %d:%d:%d\n",local->tm_hour,local->tm_min,local->tm_sec);
    printf("\t\t\t\t1.�Ǽ�;\n");
    printf("\t\t\t\t2.����;\n");
    printf("\t\t\t\t3.�鿴��¼;\n");
    printf("\t\t\t\t4.�˳�.\n");
    printf("\t\t\t\t-");
}
void checkIn(Node *&h,Park_Area *&_p,Wait_Area *&_w)
{
    time_t t=time(NULL);
    unsigned long int i;
    Node *temp;
    printf("\n�����복��ID:");
    scanf("%u",&i);
    printf("\n");
    if(isInPark(i,_p)){printf("\n�ó��ѵǼ�!\n");system("pause>nul");return;}
    if(_p->p_top<PARK-1)
    {
        //printf("%d\n",_p->p_top);system("pause>nul");
        _p->p_top++;_p->Car[_p->p_top]=i;
        temp=(Node *)malloc(sizeof(Node));
        temp->id=i;temp->Chec_In=*localtime(&t);
        temp->charge=0;
        temp->status=true;
        if(h==NULL)
          {h=(Node *)malloc(sizeof(Node));h->next=NULL;}
        temp->next=h->next;
        h->next=temp;
    }
    else if(_w->w_count<WAIT_AREA)
    {
        printf("\nͣ��������,���ں򳵳��Ⱥ�...\n");
        _w->w_count++;
        _w->w_Car[(_w->w_front+_w->w_count)%WAIT_AREA]=i;
        system("pause>nul");
    }
    else 
    {printf("\n404 ��Ǹ����λ������\n");system("pause>nul");}
}
void checkOut(Node *&h,Park_Area *&_p,Wait_Area *&_w)
{
    Node *p=h->next;
    time_t t=time(NULL);
    unsigned long int i;
    printf("\n�����복��ID:");
    scanf("%u",&i);
    printf("\n");
    while(p!=NULL&&(p->id!=i||!p->status)) p=p->next;
    if(p==NULL) {printf("\n��%u�ų����ѽ���!\n",i);system("pause>nul");return;}
    else
    {
        p->status=false;p->Chec_Out=*localtime(&t);
        p->charge=((p->Chec_Out.tm_yday-p->Chec_In.tm_yday)*24*60
        +(p->Chec_Out.tm_hour-p->Chec_In.tm_hour)*60
        +(p->Chec_Out.tm_min-p->Chec_In.tm_min))*(float)PRICE_P_MIN;
    }
    int j;bool f=false;
    for(j=0;j<=_p->p_top;j++)
    {
        if(_p->Car[j]==i) f=true;
        if(f) _p->Car[j-1]=_p->Car[j];
    }
    _p->p_top--;
    if(_w->w_count>0)
    {
        _w->w_front=(_w->w_front+1)%WAIT_AREA;
        _w->w_count--;
        time_t t1=time(NULL);
        Node *temp;
        _p->p_top++;_p->Car[_p->p_top]=_w->w_Car[_w->w_front];
        temp=(Node *)malloc(sizeof(Node));
        temp->id=_w->w_Car[_w->w_front];temp->Chec_In=*localtime(&t1);
        /*temp->Chec_Out=NULL;*/temp->charge=0;
        temp->status=true;
        if(h==NULL)
          {h=(Node *)malloc(sizeof(Node));h->next=NULL;}
        temp->next=h->next;
        h->next=temp;
    }
}
void showLog(Node *l)
{
    Node *p=l->next;
    float sum=0;
    time_t n=time(NULL);
    tm *local=localtime(&n);
    printf("\n\t\t\t\t*ͣ��������ϵͳ��־*\n");
    printf("\t\t\t\t   %d-%d-%d\n",local->tm_year+1900,local->tm_mon+1,local->tm_mday);
    printf("\t\t\t\t   %d:%d:%d\n",local->tm_hour,local->tm_min,local->tm_sec);
    printf("ID\tCheckIn\t\t\tCheckOut\t\t\tCharge($)\n");
    while(p!=NULL)
    {
    if(p->status)
    {
    printf("%u\t%d-%d %d:%d\t\t--\t\t\t\t--\n",
    p->id,p->Chec_In.tm_mon+1,p->Chec_In.tm_mday,p->Chec_In.tm_hour,
    p->Chec_In.tm_min);
    }
    else
    {
    //printf("hi");
    printf("%u\t%d-%d %d:%d\t\t%d-%d %d:%d\t\t\t%f\n",
    p->id,p->Chec_In.tm_mon+1,p->Chec_In.tm_mday,p->Chec_In.tm_hour,
    p->Chec_In.tm_min,p->Chec_Out.tm_mon+1,p->Chec_Out.tm_mday,
    p->Chec_Out.tm_hour,p->Chec_Out.tm_min,p->charge);
    sum+=p->charge;
    }
    p=p->next;
    }
    printf("�ܼ�:%f($)\n",sum);
    system("pause>nul");
}
bool isInPark(unsigned long int n,Park_Area *_p)
{
    int i=0;
    for(;i<=_p->p_top;i++)
    if(_p->Car[i]==n) return true;
    return false;
}
