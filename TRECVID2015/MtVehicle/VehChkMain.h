/*
 * 检测镜头是否含有车辆
 * 对每个关键帧，开一个线程处理
 *
 * 联系邮箱：1422163219@qq.com
 *
*/
#pragma once
#include<windows.h>
#include<process.h>
#include<iostream>
#include "VehImg.h"
#include "BufMan.h"
#include "Vehicle.h"
#include "OutItem.h"
using namespace std;
class VehChkMain
{
public:
	VehChkMain(void);
	VehChkMain(HANDLE *h,BufMan<VehImg>* i,BufMan<OutItem>* o,string path);
	
	static UINT __stdcall mainThd(LPVOID);	//主线程
	static UINT __stdcall subThd(LPVOID);	//每个子线程检测一个关键帧
	
	//处理flag变量
	static void setFlag();
	static bool isFlag();

	static void rebootSub();	//重启所有子线程
	~VehChkMain(void);
private:
	static BufMan<VehImg>* inDat;		//输入镜头的关键帧数据
	static BufMan<OutItem>* outDat;		//输出结果数据
	static HANDLE subThds[VehSize];
	static unsigned int subID[VehSize];
	static int subIndx[VehSize];
	
	/*
	 * 子线程之间的同步
	 * 当一个子线程检测到车辆时，就将flag置为true
	 *
	*/
	static HANDLE hMutFlag;
	static bool flag;

	static IplImage* data[VehSize];
	static Vehicle vt;
};

