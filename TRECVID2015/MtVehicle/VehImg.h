/*
 * 存储一个镜头信息的类型
 *
 * 联系邮箱：1422163219@qq.com
 *
*/
#pragma once
#include "Conf.h"
#include<iostream>
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "imgproc/imgproc_c.h"
using namespace std;
class VehImg
{
public:
	VehImg(void);
	VehImg(IplImage* d[],string i);
	~VehImg(void);
public:
	string id;	//镜头的编号
	IplImage* data[VehSize];	//该镜头下关键帧的数据
};

