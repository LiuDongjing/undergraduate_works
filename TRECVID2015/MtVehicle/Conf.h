#pragma once
#define OPENCVDIR "F:\\Programs\\OPENCV\\opencv\\build\\"
#define PLATFORM "x64"	//"x86"��x64
#define ISDEBUG ""		//""��"d"

#define INBUFSZ 10		//һ�λ����ͼƬ����
#define OUTBUFSZ 10		//һ�λ���Ľ������
#define WATCHTIME 30	//���Ź��̵߳�˯��ʱ��(����)
#define VehSize 3		//ÿ����ͷ��ѡ��ؼ�֡�ĸ���
#define SCALE 0.5		//�²�������
#define WAITMS 50		//�߳�ͬ��ʱ�ȴ���ʱ��(����)
#define FRQ 10			//ÿFRQ������洢һ��

#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_core249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_highgui249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_objdetect249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_imgproc249"ISDEBUG".lib")
