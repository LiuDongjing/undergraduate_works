#include "ReadMan.h"
#include<windows.h>
#include<process.h>
#include <iostream>
#include <fstream>
#include <io.h>
string ReadMan::base;
int ReadMan::fstVid;
int ReadMan::fstSid;
int ReadMan::lstSid;
int ReadMan::lstVid;
BufMan<VehImg>* ReadMan::out;

/*
 * ����ͬ���ı���
 * ��Supply=falseʱ����ʾ���������Ѿ�����
*/
bool Supply;

UINT __stdcall ReadMan::run(LPVOID)
{
	int pvd=fstVid,bngSd=fstSid,endSd=lstSid,psd;
	char ctmp[128];
	string vidPt,shotPt,shotID,shotPtt;
	VehImg *vp;
	IplImage* dat[VehSize];
	int seld[VehSize];
	int njpg,nvid,pjpg;
	Supply=true;

	//ƴ���ؼ�֡��·���������뻺����out��
	do
	{
		for(psd=bngSd;psd <= endSd;psd++)
		{
			sprintf_s(ctmp,"%d",pvd);
			shotPt=base;
			shotPt.append(ctmp);
			shotPt.append("\\shot");
			shotPt.append(ctmp);
			shotPt.append("_");
			sprintf_s(ctmp,"%d",psd);
			shotPt.append(ctmp);
			shotPt.append("\\");
			njpg=countFiles(shotPt+"*");
			if(njpg)
			{
				shotID="shot";
				sprintf_s(ctmp,"%d",pvd);
				shotID.append(ctmp);
				shotID.append("_");
				sprintf_s(ctmp,"%d",psd);
				shotID.append(ctmp);
				selectID(seld,njpg);
				for(pjpg=0;pjpg < VehSize;pjpg++)
				{
					if(seld[pjpg] != -1)
					{
						shotPtt=shotPt;
						sprintf_s(ctmp,"%d",pvd);
						shotPtt.append(ctmp);
						shotPtt.append("_");
						sprintf_s(ctmp,"%d",psd);
						shotPtt.append(ctmp);
						shotPtt.append("_");
						sprintf_s(ctmp,"%d",seld[pjpg]);
						shotPtt.append(ctmp);
						shotPtt.append(".jpg");
						dat[pjpg]=cvLoadImage(shotPtt.c_str());
						if(dat[pjpg] == NULL)
							cout<<shotPtt<<" ������!"<<endl;
					}
					else
						dat[pjpg]=NULL;
				}
				vp=new VehImg(dat,shotID);
				out->push(vp);
			}
			else
			{
				cout<<shotPt<<" û�йؼ�֡!"<<endl;
			}
		}
		pvd++;
		sprintf_s(ctmp,"%d",pvd);
		vidPt=base;
		vidPt.append(ctmp);
		vidPt.append("\\");
		nvid=countFiles(vidPt+"*");
		bngSd=1;
		endSd=nvid;
	}while(pvd <= lstVid);
	Supply=false;
	return 0;
}

/*
 * ѡȡһ����ͷ�µ����ɸ��ؼ�֡
 * ���ؼ�֡�ĸ���С������ѡȡ�Ĺؼ�֡����ʱ��ѡ�����е�
 * ���򣬰�VehSize�ȼ��ѡȡ
 *
*/
void ReadMan::selectID(int vec[],int sz)
{
	int k,d,cnt;
	if(sz <= VehSize)
	{
		for(k=0;k < sz;k++)
			vec[k]=k;
		for(;k < VehSize;k++)
			vec[k]=-1;
	}
	else
	{
		d=(sz-1)/(VehSize-1);
		for(k=0,cnt=0;cnt < VehSize;k+=d,cnt++)
		{
			vec[cnt]=k;
		}
	}

}
ReadMan::ReadMan(void)
{
	
}


ReadMan::~ReadMan(void)
{
}
ReadMan::ReadMan(HANDLE* h,string b,int fv,int fs,int ls,int lv,BufMan<VehImg>* o)
{
	base=b;
	fstVid=fv;
	fstSid=fs;
	lstSid=ls;
	lstVid=lv;
	out=o;
	unsigned int sid;
	Supply=true;
	*h=(HANDLE)_beginthreadex(NULL,0,run,NULL,0,&sid);
}

//ͳ��һ����ͷ���ж��ٹؼ�֡
int ReadMan::countFiles(string path)
{
	int cnt=0;
	_finddata_t info;
	long hnd=_findfirst(path.c_str(),&info);
	if(-1 == hnd)
		return cnt;
	cnt=-2;
	for(cnt++; !_findnext(hnd,&info);cnt++);
	_findclose(hnd);
	return cnt;
}
