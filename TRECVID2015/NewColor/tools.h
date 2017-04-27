#pragma once
#include <iostream>
#include <opencv2/opencv.hpp>
#include<vector>
#include "Conf.h"
#include "Item.h"

using namespace std;
using namespace cv;

//参数初始化
void initParam();	

//获取src的直方图，经bak返回
void getHist(Mat *src,Mat msk,Mat&bak,int bin,int range,double ratio);	

//hist反向投影到src上
Mat backProject(Mat *src,Mat hist,int range);

//a和b对应元素相与
Mat andMat(Mat a,Mat b);

//显示直方图
void showHist(string title,Mat& hist,int bin);

//字符串转int
int str2int(string str);

//字符串转double
double str2double(string str);

//hsv转rgb
Scalar HSVtoRGB(float h, float s, float v);

//读入图片并转到hsv空间
int readHSVImg(Mat& img,string path);

//获取img三个通道的直方图
void getHists(Mat& img,vector<Mat>& hists,Mat& msk);

//将hists反向投影到target的各个通道，得到过滤后的图像
Mat cutTarget(Mat& target,vector<Mat>& hists,bool debug=false);

//计算dat中所有镜头的面积
void calcArea(Item dat[],string topic,string mask);

//计算img在hists下的面积
double calcArea(string img,vector<Mat> &hists);

//统计path文件的个数
int countFiles(string path);

//整数转字符串
string int2str(int n);

//sort时用到的自定义函数
bool cmp(Item a,Item b);