/*
 * �����д���ļ�
 *
 * ��ϵ���䣺1422163219@qq.com
 *
*/
#pragma once
#include<iostream>
#include <fstream>
#include "OutItem.h"
#include "BufMan.h"
using namespace std;
class WriteMan
{
public:
	WriteMan(void);
	WriteMan(HANDLE *h,string pt,BufMan<OutItem>* dat);
	~WriteMan(void);
private:
	static BufMan<OutItem>* indat;	//��Ž���Ļ�����
	static string path;		//�ļ�·��
	static ofstream* outFile;
	static UINT __stdcall run(LPVOID);
};

