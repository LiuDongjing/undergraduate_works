/*
 * 输出数据的类型定义
 *
 * 联系邮箱：1422163219@qq.com
 *
*/
#pragma once
#include<iostream>
using namespace std;
class OutItem
{
public:
	OutItem(void);
	OutItem(string d,bool r);
	~OutItem(void);
	string id;		//镜头ID
	bool res;		//true，该镜头含有车辆；false，该镜头不含车辆。
};

