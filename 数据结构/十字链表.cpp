#include "stdio.h"
#include "stdlib.h"
#define M 5                  	//������
#define N 10                  	//������
#define Max ((M)>(N)?(M):(N)) //�������нϴ���
typedef int ElemType;
typedef struct MatNode 
{  
	int row;			      //�к�
   	int col;				//�к�
    MatNode *right,*down;	//���Һ����µ�ָ��
    union 
    {  
       int value;
       MatNode *link;
    } tag;
 };
void CreateMat(MatNode *&mh,ElemType a[M][N]); 
void DispMat(MatNode *mh);
int main(void)
{    
    ElemType Mat[M][N]=
    {
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,-99,0,0,0,0,0},
    {0,0,0,0,0,0,0,12,0,0},
    {0,0,0,0,0,0,0,0,0,0}
    };
    MatNode *head;
    CreateMat(head,Mat);
    DispMat(head);
    system("pause");
    return 0;
}
void CreateMat(MatNode *&mh,ElemType a[M][N])
{
    int i,j;
    MatNode *h[Max],*p,*q,*r;
    mh=(MatNode *)malloc(sizeof(MatNode));
    mh->row=M;
    mh->col=N;
    r=mh;
    for(i=0;i<Max;i++)
    {
        h[i]=(MatNode *)malloc(sizeof(MatNode));
        h[i]->down=h[i]->right=h[i];
        r->tag.link=h[i];
        r=h[i];
    }
    r->tag.link=mh;
    for(i=0;i<M;i++)
    {
        for(j=0;j<N;j++)
        {
            if(a[i][j]!=0)
            {
            p=(MatNode *)malloc(sizeof(MatNode));
            p->row=i;
            p->col=j;
            p->tag.value=a[i][j];
            q=h[i];
            while(q->right!=h[i]&&q->right->col<j)
            	q=q->right;
            p->right=q->right;
            q->right=p;
            q=h[j];
            while(q->down!=h[j]&&q->down->row<i)
            	q=q->down;
            p->down=q->down;
            q->down=p;
            }    
        }
    }
} 
void DispMat(MatNode *mh)
{
    MatNode *p,*q;
    printf("ROWS:%d\tCOLS:%d\n",mh->row,mh->col);
    p=mh->tag.link;
    while(p!=mh)
    {
        q=p->right;
        while(p!=q)
        {
            printf("%d\t%d\t%d\n",q->row,q->col,q->tag.value);
            q=q->right;
        }
        p=p->tag.link;
    }
}
