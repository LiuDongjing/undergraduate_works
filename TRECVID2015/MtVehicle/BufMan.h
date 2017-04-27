/*
 * ������ģ�壬ʵ�����������������㷨
 * ����߳̿�����������������Ҳ����ȡ��������
 *
 * ��ϵ���䣺1422163219@qq.com
 *
*/
#pragma once
#include<queue>
#include<windows.h>
#include<process.h>
#include "Conf.h"
using namespace std;
template <class typ>class BufMan
{
public:
	BufMan(void){}
	BufMan(LONG sz)
	{
		buf=new queue<typ*>;	//�洢���ݵĻ�����

		//ͬ��ʱʹ�õ��ź���
		hSmFull=CreateSemaphore(NULL,0,sz,NULL);
		hSmEmpty=CreateSemaphore(NULL,sz,sz,NULL);
		hMut=CreateMutex(NULL,FALSE,NULL);
	}

	//�������
	bool push(typ *e)
	{
		WaitForSingleObject(hSmEmpty,INFINITE);
		WaitForSingleObject(hMut,INFINITE);
		buf->push(e);
		ReleaseMutex(hMut);
		ReleaseSemaphore(hSmFull,1,NULL);
		return true;
	}

	//�жϻ������Ƿ�Ϊ��
	bool isEmpty()
	{
		bool ret;
		WaitForSingleObject(hMut,INFINITE);
		ret=buf->empty();
		ReleaseMutex(hMut);
		return ret;
	}

	//ȡ������
	typ * get()
	{
		typ* ret=NULL;
		WaitForSingleObject(hSmFull,WAITMS);
		WaitForSingleObject(hMut,INFINITE);
		if(buf->empty())
			ret=NULL;
		else
		{
			ret=buf->front();
			buf->pop();
		}
		ReleaseMutex(hMut);
		ReleaseSemaphore(hSmEmpty,1,NULL);
		return ret;
	}
	~BufMan(void)
	{
		int i;
		typ *tmp;
		while(!buf->empty())
		{
			tmp=buf->front();
			delete tmp;
			buf->pop();
		}
		delete buf;
		CloseHandle(hSmFull);
		CloseHandle(hSmEmpty);
		CloseHandle(hMut);
	}

private:
	queue<typ*> *buf;
	HANDLE hSmFull;
	HANDLE hSmEmpty;
	HANDLE hMut;
};