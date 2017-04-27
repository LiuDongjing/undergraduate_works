/*
 * 读入关键帧数据以及前期的处理
 *
 * 联系邮箱：1422163219@qq.com
 *
*/
#pragma once
#include<iostream>
#include "BufMan.h"
#include "VehImg.h"
using namespace std;
class ReadMan
{
public:
	ReadMan(void);
	ReadMan(HANDLE *h,string b,int fv,int fs,int ls,int lv,BufMan<VehImg>* o);
	~ReadMan(void);
private :
	static int countFiles(string path);
	static void selectID(int vec[],int sz);
private:
	static string base;		//关键帧的根目录
	
	//从fstVid号视频的fstSid镜头开始处理
	static int fstVid;		
	static int fstSid;

	//处理到lstVid号视频的lstSid镜头结束
	static int lstSid;
	static int lstVid;

	//将读入的文件放到同步缓冲区
	static BufMan<VehImg>* out;

	//主体线程
	static UINT __stdcall run(LPVOID);
};

