/*
 * ����ؼ�֡�����Լ�ǰ�ڵĴ���
 *
 * ��ϵ���䣺1422163219@qq.com
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
	static string base;		//�ؼ�֡�ĸ�Ŀ¼
	
	//��fstVid����Ƶ��fstSid��ͷ��ʼ����
	static int fstVid;		
	static int fstSid;

	//����lstVid����Ƶ��lstSid��ͷ����
	static int lstSid;
	static int lstVid;

	//��������ļ��ŵ�ͬ��������
	static BufMan<VehImg>* out;

	//�����߳�
	static UINT __stdcall run(LPVOID);
};

