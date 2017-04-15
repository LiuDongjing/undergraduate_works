/* 
 * Query adaptive �㷨��C����ʵ�֣����������MATLAB���ã�������ʽ����
 * dis=adap64(q,d)
 * q��M��2�еľ�����query������������
 * d��N��2�еľ�����document������������
 * dis��������֮��ľ���
 * 
 * ע�����㷨��Ч��ǰ����q��d�ĵ�һ�ж��ǰ���С�����˳�����У�
 *		dis��q��d��������double����
 * 
*/
#include <math.h>
#include <stdlib.h>
#include "mex.h"
void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
   int lq; 
   int ld;
   double *qdat,*ddat;
   int iq,id;
   int cq,cd;
   double sum;
   double *adpdat;	//�洢�м�������ʱ����
   double *dis;		//����ֵ
   double tmp;
   if(nrhs != 2)
   {
		mexPrintf("Two arguments needed!\n");
		return;
   }
   if(mxGetN(prhs[0]) != 2 || mxGetN(prhs[1]) != 2)
   {
		mexPrintf("Dimession error!!\n");
		return;
   }
   lq=mxGetM(prhs[0]);	//��ȡquery������
   ld=mxGetM(prhs[1]);	//��ȡdocument������
   qdat=mxGetPr(prhs[0]);
   ddat=mxGetPr(prhs[1]);
   iq=0,id=0;
   cq,cd;
   sum=0;
   adpdat=(double *)malloc(lq*sizeof(double));
   
   //���㷨����˺ϲ�����������˼��
   while(iq < lq && id < ld)
   {
		cq=*(qdat+iq);
		cd=*(ddat+id);
		if(cq == cd)
		{
			adpdat[iq]=ddat[ld+id];
			sum+=ddat[ld+id];
			iq++;
			id++;
			
		}
		else if(cq < cd)
		{
			adpdat[iq]=0;
			iq++;
		}
		else
		{
			id++;
		}
   }
   if(iq < lq)
   {
		for(;iq < lq;iq++)
			adpdat[iq]=0;
   }
   plhs[0]=mxCreateDoubleMatrix(1,1,mxREAL);
   dis=mxGetPr(plhs[0]);
   *dis=0;
   for(iq=0;iq < lq;iq++)
	{
		tmp=abs(qdat[lq+iq]-(adpdat[iq]/sum));
		*dis=*dis+tmp;
	}
	*dis=sqrt(*dis);
	free(adpdat);
}
