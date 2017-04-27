/*
 * 将结果写入文件
 *
 * 联系邮箱：1422163219@qq.com
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
	static BufMan<OutItem>* indat;	//存放结果的缓冲区
	static string path;		//文件路径
	static ofstream* outFile;
	static UINT __stdcall run(LPVOID);
};

