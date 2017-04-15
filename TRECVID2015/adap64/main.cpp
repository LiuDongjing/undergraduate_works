/* 
 * Query adaptive 算法的C语言实现；导出后可由MATLAB调用，调用形式如下
 * dis=adap64(q,d)
 * q是M行2列的矩阵，是query的特征向量；
 * d是N行2列的矩阵，是document的特征向量；
 * dis返回两者之间的距离
 * 
 * 注：该算法有效的前提是q和d的第一列都是按从小到大的顺序排列；
 *		dis、q和d都必须是double类型
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
   double *adpdat;	//存储中间结果的临时变量
   double *dis;		//返回值
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
   lq=mxGetM(prhs[0]);	//获取query的行数
   ld=mxGetM(prhs[1]);	//获取document的行数
   qdat=mxGetPr(prhs[0]);
   ddat=mxGetPr(prhs[1]);
   iq=0,id=0;
   cq,cd;
   sum=0;
   adpdat=(double *)malloc(lq*sizeof(double));
   
   //该算法借鉴了合并两个有序表的思想
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
