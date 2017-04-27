/*
 * ��⳵���Ĺؼ��㷨
 *
 * ��ϵ���䣺1422163219@qq.com
 *
*/
#pragma once
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "imgproc/imgproc_c.h"
#include "objdetect/objdetect.hpp"
#include "Conf.h"
using namespace cv;
class Vehicle
{
public:
	Vehicle(void);
	~Vehicle(void);
	int init(string model);

	//���г���������true�����򣬷���false
	bool judge(IplImage *img);
private:
	CvLatentSvmDetector *lsd;
};

