/*
 * 车辆检测
 * 从起始视频的特定镜头段开始处理，处理到结束视频
 * 输出文件：镜头编号 1(有车)或0(无车)
 * 三级流水线，有两个缓冲区连接相邻部件
 * 读入数据线程rm将数据读入缓冲区din；处理线程vcm从din读数据，经处理后写入dout；存储数据线程wm将dout数据写入文件
 * 
 * 联系邮箱：1422163219@qq.com
 * 
*/
#include<windows.h>
#include<process.h>
#include<iostream>
#include<sstream>
#include "time.h"  
#include "VehChkMain.h"
#include "OutItem.h"
#include "ReadMan.h"
#include "highgui/highgui.hpp"
#include "imgproc/imgproc.hpp"
#include "imgproc/imgproc_c.h"
#include "objdetect/objdetect.hpp"
#include "WriteMan.h"
#include "Conf.h"
using namespace std;
using namespace cv;

VehChkMain *vcm;	//处理线程
ReadMan* rm;		//读入数据线程
WriteMan* wm;		//存储数据线程

BufMan<VehImg> *din;	//读入数据线程与处理线程间的缓冲区
BufMan<OutItem> *dout;	//处理线程与存储数据线程间的缓冲区

bool watch;				//存储数据线程将watch置为false，看门狗线程将其置为true；
						//当看门狗线程发现watch=true时，整个程序将退出
static string watLog;	//log文件
static ofstream *logx;

UINT __stdcall watchDog(LPVOID);	//看门狗线程

string& int2str(int n,string& str);	
int str2int(string str);

int main(int argc,char *argv[])
{
	/*
	 * 程序从fstVd视频的fstSd的镜头开始处理，到lstVd视频的lstSd的镜头结束
	*/
	if(argc < 8)
	{
		cout<<"MtVehicle fstVd lstVd fstSd lstSd model datPath outPath"<<endl;
		cout<<"\tfstVd:起始视频编号"<<endl;
		cout<<"\tlstVd:结束视频编号"<<endl;
		cout<<"\tfstSd:起始视频的起始镜头编号"<<endl;
		cout<<"\tlstSd:起始视频的结束镜头编号"<<endl;
		cout<<"\tmodel:模型文件路径"<<endl;
		cout<<"\tdatPath:关键帧路径"<<endl;
		cout<<"\toutPath:输出文件路径"<<endl;
		exit(1);
	}

	string stmp;
	HANDLE subHnds[3];

	int fstVd=str2int(string(argv[1])),lstVd=str2int(string(argv[2]));
	int fstSd=str2int(string(argv[3])),lstSd=str2int(string(argv[4]));
	string model=argv[5];
	string datPath=argv[6];
 	string outPath=argv[7];

	if(datPath.at(datPath.size()-1) != '\\')
		datPath.append("\\");
	if(outPath.at(outPath.size()-1) != '\\')
		outPath.append("\\");
	clock_t strt;
	strt=clock();
	watLog=outPath+"log.txt";
	logx=new ofstream(watLog,ios::out);

	din=new BufMan<VehImg>(INBUFSZ);
	dout=new BufMan<OutItem>(OUTBUFSZ);
	rm=new ReadMan(&subHnds[0],datPath,fstVd,fstSd,lstSd,lstVd,din);
	outPath+=int2str(fstVd,stmp)+"_";
	outPath+=int2str(fstSd,stmp)+"_";
	outPath+=int2str(lstSd,stmp)+"_";
	outPath+=int2str(lstVd,stmp)+".txt";

	vcm=new VehChkMain(&subHnds[1],din,dout,model);

	wm=new WriteMan(&subHnds[2],outPath,dout);
	
	watch=false;
	unsigned int sid;
	_beginthreadex(NULL,0,watchDog,NULL,0,&sid);
	WaitForMultipleObjects(3,subHnds,true,INFINITE);	//三个部件都结束时，程序退出
	*logx<<"总共用时:"<<(clock()-(double)strt)/CLOCKS_PER_SEC<<endl;
	logx->flush();
	logx->close();
	return 0;
}
UINT __stdcall watchDog(LPVOID)
{
	
	while(true)
	{
		Sleep(WATCHTIME*60*1000);
		if(watch)
		{
			*logx<<"出现死锁，程序退出！"<<endl;
			logx->flush();
			logx->close();
			exit(1);
		}
		watch=true;
	}
	return 0;
}
string& int2str(int n,string& str)
{
	stringstream cvt;
	cvt<<n;
	cvt>>str;
	return str;
}
int str2int(string str)
{
	stringstream cvt;
	int ret;
	cvt<<str;
	cvt>>ret;
	return ret;
}