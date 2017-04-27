#include "VehChkMain.h"
#include "VehImg.h"
#include "time.h"  
bool ResSupply;
BufMan<VehImg>* VehChkMain::inDat;
BufMan<OutItem>* VehChkMain::outDat;
HANDLE VehChkMain::subThds[VehSize];
unsigned int VehChkMain::subID[VehSize];
int VehChkMain::subIndx[VehSize];
HANDLE VehChkMain::hMutFlag;
bool VehChkMain::flag;
IplImage* VehChkMain::data[VehSize];
Vehicle VehChkMain::vt;
extern bool Supply;
VehChkMain::VehChkMain(void)
{
}


VehChkMain::~VehChkMain(void)
{

}
VehChkMain::VehChkMain(HANDLE *h,BufMan<VehImg>* i,BufMan<OutItem>* o,string path)
{
	inDat=i;
	outDat=o;
	ResSupply=true;
	for(int k=0;k < VehSize;k++)
	{
		subIndx[k]=k;
		subThds[k]=NULL;
	}
	unsigned int sid;
	hMutFlag=CreateMutex(NULL,FALSE,NULL);
	flag=false;
	vt.init(path);
	*h=(HANDLE)_beginthreadex(NULL,0,mainThd,NULL,0,&sid);
}
UINT __stdcall VehChkMain::mainThd(LPVOID)
{
	VehImg *ind;
	ResSupply=true;
	while(!inDat->isEmpty() | Supply)
	{
		ind=inDat->get();
		if(NULL != ind)
		{
			for(int k=0;k < VehSize;k++)
				data[k]=ind->data[k];
			rebootSub();

			//等待所有子线程结束
			WaitForMultipleObjects(VehSize,subThds,TRUE,INFINITE);

			if(isFlag())
			{
				outDat->push(new OutItem(ind->id,true));
			}
			else
			{
				outDat->push(new OutItem(ind->id,false));
			}
			delete ind;
			flag=false;
		}
	}
	ResSupply=false;
	return 0;
}
void VehChkMain::setFlag()
{
	WaitForSingleObject(hMutFlag,INFINITE);
	if(!flag)
		flag=true;
	ReleaseMutex(hMutFlag);
}
bool VehChkMain::isFlag()
{
	bool ret;
	WaitForSingleObject(hMutFlag,INFINITE);
	ret=flag;
	ReleaseMutex(hMutFlag);
	return ret;
}
void VehChkMain::rebootSub()
{
	for(int k=0;k < VehSize;k++)
	{
		if(subThds[k] != NULL)
			CloseHandle(subThds[k]);
		subThds[k]=(HANDLE)_beginthreadex(NULL,0,subThd,&(subIndx[k]),0,&subID[k]);
	}
}
UINT  __stdcall VehChkMain::subThd(LPVOID p)
{
	int id=*((int *)p);
	if(data[id] != NULL && vt.judge(data[id]))
		setFlag();
	return 0;
}
