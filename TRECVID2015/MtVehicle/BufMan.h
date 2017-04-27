/*
 * 缓冲区模板，实现了生产者消费者算法
 * 多个线程可以向里面添加数据项，也可以取走数据项
 *
 * 联系邮箱：1422163219@qq.com
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
		buf=new queue<typ*>;	//存储数据的缓冲区

		//同步时使用的信号量
		hSmFull=CreateSemaphore(NULL,0,sz,NULL);
		hSmEmpty=CreateSemaphore(NULL,sz,sz,NULL);
		hMut=CreateMutex(NULL,FALSE,NULL);
	}

	//添加数据
	bool push(typ *e)
	{
		WaitForSingleObject(hSmEmpty,INFINITE);
		WaitForSingleObject(hMut,INFINITE);
		buf->push(e);
		ReleaseMutex(hMut);
		ReleaseSemaphore(hSmFull,1,NULL);
		return true;
	}

	//判断缓冲区是否为空
	bool isEmpty()
	{
		bool ret;
		WaitForSingleObject(hMut,INFINITE);
		ret=buf->empty();
		ReleaseMutex(hMut);
		return ret;
	}

	//取走数据
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