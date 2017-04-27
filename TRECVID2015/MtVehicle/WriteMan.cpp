#include "WriteMan.h"
extern bool ResSupply;
extern bool watch;
BufMan<OutItem>* WriteMan::indat;
string WriteMan::path;
ofstream* WriteMan::outFile;
WriteMan::WriteMan(void)
{
}


WriteMan::~WriteMan(void)
{
}
WriteMan::WriteMan(HANDLE *h,string pt,BufMan<OutItem>* dat)
{
	path=pt;
	indat=dat;
	unsigned int sid;
	outFile=new ofstream(pt,ios::out|ios::app);
	if(NULL == outFile)
	{
		cout<<pt.c_str()<<" ´ò¿ªÊ§°Ü!"<<endl;
		exit(1);
	}
	*h=(HANDLE)_beginthreadex(NULL,0,run,NULL,0,&sid);

}
UINT __stdcall WriteMan::run(LPVOID)
{
	OutItem* poi;
	int cnt=0;
	while(!indat->isEmpty() | ResSupply)
	{
		poi=indat->get();
		if(NULL != poi)
		{
			*outFile<<poi->id.c_str()<<"\t"<<poi->res<<endl;
			if(cnt >= FRQ)
			{
				outFile->flush();
				cnt=0;
			}
			watch=false;
		}
	}
	outFile->close();
	return 0;
}
