/*
 * ������ݵ����Ͷ���
 *
 * ��ϵ���䣺1422163219@qq.com
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
	string id;		//��ͷID
	bool res;		//true���þ�ͷ���г�����false���þ�ͷ����������
};

