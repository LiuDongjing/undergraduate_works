/*
 * �������
 * ����ʼ��Ƶ���ض���ͷ�ο�ʼ��������������Ƶ
 * ����ļ�����ͷ��� 1(�г�)��0(�޳�)
 * ������ˮ�ߣ��������������������ڲ���
 * ���������߳�rm�����ݶ��뻺����din�������߳�vcm��din�����ݣ��������д��dout���洢�����߳�wm��dout����д���ļ�
 * 
 * ��ϵ���䣺1422163219@qq.com
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

VehChkMain *vcm;	//�����߳�
ReadMan* rm;		//���������߳�
WriteMan* wm;		//�洢�����߳�

BufMan<VehImg> *din;	//���������߳��봦���̼߳�Ļ�����
BufMan<OutItem> *dout;	//�����߳���洢�����̼߳�Ļ�����

bool watch;				//�洢�����߳̽�watch��Ϊfalse�����Ź��߳̽�����Ϊtrue��
						//�����Ź��̷߳���watch=trueʱ�����������˳�
static string watLog;	//log�ļ�
static ofstream *logx;

UINT __stdcall watchDog(LPVOID);	//���Ź��߳�

string& int2str(int n,string& str);	
int str2int(string str);

int main(int argc,char *argv[])
{
	/*
	 * �����fstVd��Ƶ��fstSd�ľ�ͷ��ʼ������lstVd��Ƶ��lstSd�ľ�ͷ����
	*/
	if(argc < 8)
	{
		cout<<"MtVehicle fstVd lstVd fstSd lstSd model datPath outPath"<<endl;
		cout<<"\tfstVd:��ʼ��Ƶ���"<<endl;
		cout<<"\tlstVd:������Ƶ���"<<endl;
		cout<<"\tfstSd:��ʼ��Ƶ����ʼ��ͷ���"<<endl;
		cout<<"\tlstSd:��ʼ��Ƶ�Ľ�����ͷ���"<<endl;
		cout<<"\tmodel:ģ���ļ�·��"<<endl;
		cout<<"\tdatPath:�ؼ�֡·��"<<endl;
		cout<<"\toutPath:����ļ�·��"<<endl;
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
	WaitForMultipleObjects(3,subHnds,true,INFINITE);	//��������������ʱ�������˳�
	*logx<<"�ܹ���ʱ:"<<(clock()-(double)strt)/CLOCKS_PER_SEC<<endl;
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
			*logx<<"���������������˳���"<<endl;
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