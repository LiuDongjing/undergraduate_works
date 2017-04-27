/*
 * 颜色过滤时一个镜头的数据信息
 *
 * 联系邮箱：1422163219@qq.com
*/
#pragma once
#include<iostream>
using namespace std;
class Item
{
public:
	string name;		//镜头关键帧目录的路径
	double area;		//该镜头的在topic下的面积
	bool flag;			//true，该镜头含有topic的颜色；否则，没有
	Item(void);
	~Item(void);
};

