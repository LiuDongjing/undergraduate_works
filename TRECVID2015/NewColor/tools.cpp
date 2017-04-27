#include "tools.h"
#include<omp.h>
#include <io.h>
#include<fstream>
extern int hBin,sBin,vBin;
extern double area;
extern double hRatio,sRatio,vRatio;

//src是HSV,mask是GRAY
void getHist(Mat *src,Mat msk,Mat&bak,int bin,int range,double ratio)
{
	int histSize[] = {bin};
	float histRange[] = { 0, range };
	int ch[]={0};
	const float* ranges[] = {histRange};

	calcHist(src,1,ch,msk,bak, 1, histSize, ranges, true, false );
  
	double maxVal = 0;
	minMaxLoc(bak, 0, &maxVal);
	threshold(bak,bak,maxVal*ratio,maxVal,THRESH_TOZERO);
}

Mat backProject(Mat *src,Mat hist,int range)
{
	Mat back;
	int ch[]={0};
	float histRange[] = { 0, range };
	const float* ranges[] = {histRange};
	calcBackProject(src,1, ch, hist,back, ranges, 1, true );
	return back;
}
Mat andMat(Mat a,Mat b)
{
	Mat ret;
	ret.create(a.size(),a.type());
	Mat_<uchar> des=ret,aa=a,bb=b;
	for(int i=0;i < a.rows;i++)
		for(int j=0;j < a.cols;j++)
		{
			if(aa(i,j) && bb(i,j))
				des(i,j)=255;
			else
				des(i,j)=0;
		}
	return ret;
}
void initParam()
{
	hBin=90;
	sBin=10;
	vBin=10;
	area=0.1;

	hRatio=0.1;
	sRatio=0.1;
	vRatio=0.1;
}
void showHist(string title,Mat& srcHist,int hBins)
{
	Mat show_hist = Mat::zeros(400, 400, CV_32FC3);

	int bin_w = show_hist.cols / hBins;	//直方图中一个bin占的宽度
	int maxVal = 0;	//最大值
	for(int i = 0; i < hBins; i++ )
	{
		float data = srcHist.at<float>(i, 0);
		if (maxVal < data)
		{
			maxVal = data;
		}
	}

	float rate = 400.f / maxVal;

	double total_pixs=0; //

	for(int i = 0; i < hBins; i++ )
	{
		//求第i个bin的高度
		float val = srcHist.at<float>(i, 0);

		total_pixs += val;
		Scalar color = HSVtoRGB(i*180.f/hBins*0.03333,0.0,0.8);//画色调直方图，彩色

		//画直方图各个bin
		rectangle( show_hist, cvPoint(i*bin_w, show_hist.cols), cvPoint((i+1)*bin_w, show_hist.rows - val * rate), color, -1, 8, 0 );
	}
	imshow(title, show_hist);
	waitKey(1);
}
int str2int(string str)
{
	stringstream ss;
	int ret;
	ss<<str;
	ss>>ret;
	return ret;
}
string int2str(int n)
{
	stringstream ss;
	string ret;
	ss<<n;
	ss>>ret;
	return ret;
}
double str2double(string str)
{
	stringstream ss;
	double ret;
	ss<<str;
	ss>>ret;
	return ret;
}
Scalar HSVtoRGB(float h, float s, float v)
{
	// H is given on [0->6] or -1. S and V are given on [0->1].
	// RGB are each returned on [0->1].
	float m, n, f;
	int i;

	float *hsv = new float[3];
	float *rgb = new float[3];

	hsv[0] = h;
	hsv[1] = s;
	hsv[2] = v;

	if (hsv[0] == -1)
	{
		rgb[0] = rgb[1] = rgb[2] = hsv[2];
		return Scalar(rgb[2], rgb[1], rgb[0],0);
	}
	i = (int) (floor(hsv[0]));
	f = hsv[0] - i;
	if (i % 2 == 0)
	{
		f = 1 - f; // if i is even
	}
	m = hsv[2] * (1 - hsv[1]);
	n = hsv[2] * (1 - hsv[1] * f);
	switch (i)
	{
	case 6:
	case 0:
		rgb[0] = hsv[2];
		rgb[1] = n;
		rgb[2] = m;
		break;
	case 1:
		rgb[0] = n;
		rgb[1] = hsv[2];
		rgb[2] = m;
		break;
	case 2:
		rgb[0] = m;
		rgb[1] = hsv[2];
		rgb[2] = n;
		break;
	case 3:
		rgb[0] = m;
		rgb[1] = n;
		rgb[2] = hsv[2];
		break;
	case 4:
		rgb[0] = n;
		rgb[1] = m;
		rgb[2] = hsv[2];
		break;
	case 5:
		rgb[0] = hsv[2];
		rgb[1] = m;
		rgb[2] = n;
		break;
	}

	return Scalar(rgb[2], rgb[1], rgb[0],0);
}

int readHSVImg(Mat& img,string path)
{
	img=imread(path);
	if(!img.data)
	{
		cout<<path<<"读取失败!"<<endl;
		return 1;
	}
	cvtColor(img,img,CV_BGR2HSV);
	return 0;
}
void getHists(Mat& img,vector<Mat>& hists,Mat& msk)
{
	Mat chann[3],hMat,sMat,vMat;
	split(img,chann);
	getHist(&chann[0],msk,hMat,hBin,HRANGE,hRatio);
	getHist(&chann[1],msk,sMat,sBin,SRANGE,sRatio);
	getHist(&chann[2],msk,vMat,vBin,VRANGE,vRatio);
	hists.push_back(hMat);
	hists.push_back(sMat);
	hists.push_back(vMat);
}
Mat cutTarget(Mat& target,vector<Mat>& hists,bool debug)
{
	Mat mask;
	Mat chann[3];
	Mat hBP,sBP,vBP;

	split(target,chann);
	hBP=backProject(&chann[0],hists[0],HRANGE);
	sBP=backProject(&chann[1],hists[1],SRANGE);
	vBP=backProject(&chann[2],hists[2],VRANGE);

	if(debug)
	{
		imshow("hBP",hBP);
		imshow("sBP",sBP);
		imshow("vBP",vBP);
		waitKey();
	}

	hBP.copyTo(mask,sBP);
	vBP.copyTo(mask,mask);
	threshold(mask,mask,BINARY_THRESHOLD,255,THRESH_BINARY);

	return mask;
}

//使用openMP并行计算
void calcArea(Item dat[],string topic,string mask)
{
	Mat src;
	readHSVImg(src,topic);
	Mat msk=imread(mask,CV_LOAD_IMAGE_GRAYSCALE);
	vector<Mat> hists;
	getHists(src,hists,msk);
	ofstream backup("backup.txt",ios::out);
	for(int k=0;k < ITEM_SIZE;k++)	//每次并行处理ITEM_SIZE个镜头数据
	{
		#pragma omp parallel for
		for(int m=0;m < THREADS_NUM;m++)
		{
			int ind=k*THREADS_NUM+m;
			if(ind >= ITEM_SIZE)
				continue;
			dat[ind].area=calcArea(dat[ind].name,hists);
			if(dat[ind].area >= area)
				dat[ind].flag=true;
			else
				dat[ind].flag=false;
		}
		for(int h=k*THREADS_NUM;h < (k+1)*THREADS_NUM;h++)
		{
			if(h >= ITEM_SIZE)
				break;
			backup<<dat[h].name<<"\t"<<dat[h].area<<"\t"<<dat[h].flag<<endl;
		}
		backup.flush();
	}
	backup.close();
}
double calcArea(string img,vector<Mat> &hists)
{
	int cnt=countFiles(img+"\\*.jpg");
	if(cnt < 1)
	{
		cout<<img<<" 是空镜头或不存在!"<<endl;
		return 0;
	}
	double marea[3]={0};

	//格式:shot"vid"_"sid"
	string id=img.substr(img.rfind('\\')+1);
	cout<<id<<":processing..."<<endl;
	string vid=id.substr(4);
	int rid[3]={-1};
	Mat target,final;
	if(cnt <= 3)
		for(int p=0;p < cnt;p++)
		{
			rid[p]=p;
		}
	else
	{
		rid[0]=0;
		rid[1]=cnt/2;
		rid[3]=cnt-1;
	}
	for(int p=0;p < 3;p++)
	{
		if(rid[p] == -1 || readHSVImg(target,img+"\\"+vid+"_"+int2str(rid[p])+".jpg"))
		{
			marea[p]=0;
			continue;
		}
		final=cutTarget(target,hists);
		marea[p]=countNonZero(final)/(double)(final.rows*final.cols);
	}
	return MAX(MAX(marea[0],marea[1]),marea[2]);
}
int countFiles(string path)
{
	int cnt=0;
	_finddata_t info;
	long hnd=_findfirst(path.c_str(),&info);
	if(-1 == hnd)
		return cnt;
	for(cnt++; !_findnext(hnd,&info);cnt++);
	_findclose(hnd);
	return cnt;
}
bool cmp(Item a,Item b)
{
	return a.area > b.area;
}