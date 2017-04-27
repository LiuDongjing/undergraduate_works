/*
 * 检测车辆的关键算法
 *
 * 联系邮箱：1422163219@qq.com
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

	//含有车辆，返回true；否则，返回false
	bool judge(IplImage *img);
private:
	CvLatentSvmDetector *lsd;
};

