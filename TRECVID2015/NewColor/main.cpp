/*
 * ��topic��HSV�ռ�����ɫ���ˣ�����������ʹ��
 * openMP�Ĵ�����tools.cpp��void calcArea(Item dat[],string topic,string mask)��
 * ��ϵ���䣺1422163219@qq.com
*/
#include<iostream>
#include <opencv2/opencv.hpp>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm> 
#include<time.h>
#include "Conf.h"		//��������
#include "tools.h"		//�����˹��ߺ���
#include "Item.h"

using namespace std;
using namespace cv;

int hBin,sBin,vBin;
double area;
double hRatio,sRatio,vRatio;

int main(int argc,char* argv[])
{
	string srcPt(""),mskPt(""),tarPt(""),fileLst("");
	if(argc < 2)
	{
		cout<<"��������!"<<endl;
		return 1;
	}
	int debug=1;		//��������˵��ԣ��Ὣ�м��������ս����ͼƬ����ʽ��ʾ����
	string outFile("result.txt");		//���ս���浵
	initParam();	//��ʼ��ʹ�õĲ���
	ifstream conf(argv[1],ios::in);	//���������ļ�
	string para,val;
	while(!conf.eof())
	{
		conf>>para;
		conf>>val;
		if(para =="hBin")				//H������bin����
			hBin=str2int(val);
		else if(para == "sBin")		//S������bin����
			sBin=str2int(val);
		else if(para == "vBin")		//V������bin����
			vBin=str2int(val);
		else if(para == "hRatio")	//��H������bin�У�Ƶ�����������Ƶ��ΪNM��������Ƶ��С��hRatio*NM�����䶼�����˵�
			hRatio=str2double(val);
		else if(para == "sRatio")	//ͬH
			sRatio=str2double(val);
		else if(para == "vRatio")	//ͬH
			vRatio=str2double(val);
		else if(para == "area")		//�������area��keyframe����Ϊ����topic����ɫ
			area=str2double(val);
		else if(para == "src")		//topicͼƬ
			srcPt=val;
		else if(para == "mask")		//topic��maskͼƬ
			mskPt=val;
		else if(para == "target")	//����ʱʹ�õ�keyframeͼƬ
			tarPt=val;
		else if(para == "debug")	//debug=0�������ԣ����򣬵���
			debug=str2int(val);
		else if(para == "fileLst")	//������ľ�ͷ�б�ÿһ���Ǿ�ͷ�ؼ�֡�ļ��е�·��
			fileLst=val;
		else if(para == "outFile")	//�������ļ�
			outFile=val;
		else
			cout<<para<<" ��ʶ��Ĳ���!"<<endl;
	}
	conf.close();
	if(srcPt == "" || 
		mskPt == "")
	{
		cout<<"��Ҫָ��Topic��Mask!"<<endl;
		return 1;
	}
	if(debug && tarPt == "" )
	{
		cout<<"����ģʽ����ָ����ѯͼƬ!"<<endl;
		return 1;
	}
	if(!debug && fileLst == "")
	{
		cout<<"�ǵ���ģʽ����ָ���ļ��б�!"<<endl;
		return 1;
	}
	if(argc > 2)
		fileLst=argv[2];
	//��ʾ����
	cout<<"�����б�:"<<endl;
	cout<<"\tBins\tRatio"<<endl;
	cout<<"H\t"<<hBin<<"\t"<<hRatio<<endl;
	cout<<"S\t"<<sBin<<"\t"<<sRatio<<endl;
	cout<<"V\t"<<vBin<<"\t"<<vRatio<<endl;
	cout<<"Area:"<<area<<endl;

	if(debug)
	{
		//����ģʽ
		Mat src;
		readHSVImg(src,srcPt);
		Mat msk=imread(mskPt,CV_LOAD_IMAGE_GRAYSCALE);
		Mat target;
		readHSVImg(target,tarPt);

		vector<Mat> hists;
		getHists(src,hists,msk);

		showHist("H",hists[0],hBin);
		showHist("S",hists[1],sBin);
		showHist("V",hists[2],vBin);
		
		//hists����ͶӰ��target��
		Mat final=cutTarget(target,hists,true);
		imshow("����ͼ��",final);
		cout<<"\n���:"<<countNonZero(final)/(double)(final.rows*final.cols)<<endl;
		waitKey();
		return 0;
	}
	
	clock_t st=clock();
	ifstream lst(fileLst,ios::in);
	string line;
	Item dat[ITEM_SIZE];
	for(int i=0;i < ITEM_SIZE && !lst.eof();i++)
	{
		lst>>line;
		dat[i].name=line;
	}
	lst.close();
	calcArea(dat,srcPt,mskPt);		//���м������
	sort(dat,dat+ITEM_SIZE,cmp);	//������Ӵ�С����
	ofstream otf(outFile,ios::out);
	for(int i=0;i < ITEM_SIZE;i++)
		otf<<dat[i].name<<"\t"<<dat[i].area<<"\t"<<dat[i].flag<<endl;	//������
	otf.close();
	cout<<"�ܺ�ʱ:"<<((double)clock()-st)/CLOCKS_PER_SEC<<endl;
	//cin.get();
	return 0;
}

