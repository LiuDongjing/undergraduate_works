#include "VehImg.h"


VehImg::VehImg(void)
{

}

VehImg::VehImg(IplImage* d[],string x)
{
	id=x;
	for(int i=0;i < VehSize;i++)
		data[i]=d[i];
}
VehImg::~VehImg(void)
{

}
