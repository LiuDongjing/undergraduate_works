/*
 * 在topic的HSV空间做颜色过滤，三个分量均使用
 * openMP的代码在tools.cpp的void calcArea(Item dat[],string topic,string mask)；
 * 联系邮箱：1422163219@qq.com
*/
#include<iostream>
#include <opencv2/opencv.hpp>
#include<vector>
#include<sstream>
#include<fstream>
#include<algorithm> 
#include<time.h>
#include "Conf.h"		//定义宏参数
#include "tools.h"		//定义了工具函数
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
		cout<<"参数不够!"<<endl;
		return 1;
	}
	int debug=1;		//如果配置了调试，会将中间结果和最终结果以图片的形式显示出来
	string outFile("result.txt");		//最终结果存档
	initParam();	//初始化使用的参数
	ifstream conf(argv[1],ios::in);	//读入配置文件
	string para,val;
	while(!conf.eof())
	{
		conf>>para;
		conf>>val;
		if(para =="hBin")				//H分量的bin个数
			hBin=str2int(val);
		else if(para == "sBin")		//S分量的bin个数
			sBin=str2int(val);
		else if(para == "vBin")		//V分量的bin个数
			vBin=str2int(val);
		else if(para == "hRatio")	//在H分量的bin中，频数最大的区间的频数为NM，则所有频数小于hRatio*NM的区间都被过滤掉
			hRatio=str2double(val);
		else if(para == "sRatio")	//同H
			sRatio=str2double(val);
		else if(para == "vRatio")	//同H
			vRatio=str2double(val);
		else if(para == "area")		//面积大于area的keyframe才认为函数topic的颜色
			area=str2double(val);
		else if(para == "src")		//topic图片
			srcPt=val;
		else if(para == "mask")		//topic的mask图片
			mskPt=val;
		else if(para == "target")	//调试时使用的keyframe图片
			tarPt=val;
		else if(para == "debug")	//debug=0，不调试；否则，调试
			debug=str2int(val);
		else if(para == "fileLst")	//待处理的镜头列表；每一行是镜头关键帧文件夹的路径
			fileLst=val;
		else if(para == "outFile")	//结果输出文件
			outFile=val;
		else
			cout<<para<<" 不识别的参数!"<<endl;
	}
	conf.close();
	if(srcPt == "" || 
		mskPt == "")
	{
		cout<<"需要指定Topic和Mask!"<<endl;
		return 1;
	}
	if(debug && tarPt == "" )
	{
		cout<<"调试模式下需指定查询图片!"<<endl;
		return 1;
	}
	if(!debug && fileLst == "")
	{
		cout<<"非调试模式下需指定文件列表!"<<endl;
		return 1;
	}
	if(argc > 2)
		fileLst=argv[2];
	//显示参数
	cout<<"参数列表:"<<endl;
	cout<<"\tBins\tRatio"<<endl;
	cout<<"H\t"<<hBin<<"\t"<<hRatio<<endl;
	cout<<"S\t"<<sBin<<"\t"<<sRatio<<endl;
	cout<<"V\t"<<vBin<<"\t"<<vRatio<<endl;
	cout<<"Area:"<<area<<endl;

	if(debug)
	{
		//调试模式
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
		
		//hists反向投影到target上
		Mat final=cutTarget(target,hists,true);
		imshow("最终图像",final);
		cout<<"\n面积:"<<countNonZero(final)/(double)(final.rows*final.cols)<<endl;
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
	calcArea(dat,srcPt,mskPt);		//并行计算面积
	sort(dat,dat+ITEM_SIZE,cmp);	//按面积从大到小排序
	ofstream otf(outFile,ios::out);
	for(int i=0;i < ITEM_SIZE;i++)
		otf<<dat[i].name<<"\t"<<dat[i].area<<"\t"<<dat[i].flag<<endl;	//保存结果
	otf.close();
	cout<<"总耗时:"<<((double)clock()-st)/CLOCKS_PER_SEC<<endl;
	//cin.get();
	return 0;
}

