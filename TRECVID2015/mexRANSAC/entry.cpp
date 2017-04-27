/*
 * ��opencv��findHomography����ʵ�ֵ�RANSAC�㷨
 * ����topic��sift��Ķ�ά����src(M��2�У�double����)��keyframe��sift��Ķ�ά
 * ����des(N��2�У�double����)�Լ���ֵtrh�����M��1�е�double������1����ƥ
 * ���ϵĵ㣬0����δƥ����
 *
 * ��ϵ���䣺1422163219@qq.com
*/

#include <stdio.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/features2d/features2d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include <math.h>
#include <stdlib.h>
#include "mex.h"

using namespace cv;
using namespace std;

//��������֮���ŷ�Ͼ���
double getDis(Point2f&a,Point2f&b);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs != 3)
	{
		mexPrintf("��Ҫ��������!\n");
		return;
	}
	double *src,*des,trh;
	int srcSz,desSz;

	srcSz=mxGetM(prhs[0]);
	desSz=mxGetM(prhs[1]);

	src=mxGetPr(prhs[0]);
	des=mxGetPr(prhs[1]);
	trh=*(mxGetPr(prhs[2]));

	vector<Point2f> obj(srcSz);
	vector<Point2f> scene(desSz);
	vector<Point2f> scene2(desSz);

	for(int i=0;i < srcSz;i++)
		obj[i]=Point2f(src[i],src[srcSz+i]);
	for(int i=0;i < desSz;i++)
		scene[i]=Point2f(des[i],des[desSz+i]);

	//��RANSAC����obj��scene�ķ���任H
	Mat H = findHomography( obj, scene, CV_RANSAC ,trh);
	
	//obj���任����H�任��scene���ڵĿռ䣬�õ�scene2
	perspectiveTransform( obj, scene2, H);

	double *res,dis;
	plhs[0]=mxCreateDoubleMatrix(srcSz,1,mxREAL);
	res=mxGetPr(plhs[0]);

	for(int i=0;i < srcSz;i++)
	{
		//��obj�任��ĵ���scene�ж�Ӧ��ľ���С����ֵtrhʱ���϶�����ƥ����
		if(getDis(scene[i],scene2[i]) <= trh)
			res[i]=1;
		else
			res[i]=0;
	}
}
double getDis(Point2f&a,Point2f&b)
{
	double ret,tmp;
	tmp=a.x-b.x;
	ret=tmp*tmp;
	tmp=a.y-b.y;
	ret+=tmp*tmp;
	return sqrt(ret);
}