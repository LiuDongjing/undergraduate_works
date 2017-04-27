/*
 * ��⾵ͷ�Ƿ��г���
 * ��ÿ���ؼ�֡����һ���̴߳���
 *
 * ��ϵ���䣺1422163219@qq.com
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
	
	static UINT __stdcall mainThd(LPVOID);	//���߳�
	static UINT __stdcall subThd(LPVOID);	//ÿ�����̼߳��һ���ؼ�֡
	
	//����flag����
	static void setFlag();
	static bool isFlag();

	static void rebootSub();	//�����������߳�
	~VehChkMain(void);
private:
	static BufMan<VehImg>* inDat;		//���뾵ͷ�Ĺؼ�֡����
	static BufMan<OutItem>* outDat;		//����������
	static HANDLE subThds[VehSize];
	static unsigned int subID[VehSize];
	static int subIndx[VehSize];
	
	/*
	 * ���߳�֮���ͬ��
	 * ��һ�����̼߳�⵽����ʱ���ͽ�flag��Ϊtrue
	 *
	*/
	static HANDLE hMutFlag;
	static bool flag;

	static IplImage* data[VehSize];
	static Vehicle vt;
};

