/*
 * 用opencv的findHomography函数实现的RANSAC算法
 * 输入topic的sift点的二维坐标src(M行2列，double类型)、keyframe的sift点的二维
 * 坐标des(N行2列，double类型)以及阈值trh；输出M行1列的double向量，1代表匹
 * 配上的点，0代表未匹配上
 *
 * 联系邮箱：1422163219@qq.com
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

//计算两点之间的欧氏距离
double getDis(Point2f&a,Point2f&b);

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
	if(nrhs != 3)
	{
		mexPrintf("需要三个参数!\n");
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

	//用RANSAC计算obj到scene的仿射变换H
	Mat H = findHomography( obj, scene, CV_RANSAC ,trh);
	
	//obj经变换矩阵H变换到scene所在的空间，得到scene2
	perspectiveTransform( obj, scene2, H);

	double *res,dis;
	plhs[0]=mxCreateDoubleMatrix(srcSz,1,mxREAL);
	res=mxGetPr(plhs[0]);

	for(int i=0;i < srcSz;i++)
	{
		//当obj变换后的点与scene中对应点的距离小于阈值trh时，认定两者匹配上
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