/*
 * �洢һ����ͷ��Ϣ������
 *
 * ��ϵ���䣺1422163219@qq.com
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
	string id;	//��ͷ�ı��
	IplImage* data[VehSize];	//�þ�ͷ�¹ؼ�֡������
};

