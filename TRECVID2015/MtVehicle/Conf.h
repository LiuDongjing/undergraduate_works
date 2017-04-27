#pragma once
#define OPENCVDIR "F:\\Programs\\OPENCV\\opencv\\build\\"
#define PLATFORM "x64"	//"x86"或x64
#define ISDEBUG ""		//""或"d"

#define INBUFSZ 10		//一次缓冲的图片个数
#define OUTBUFSZ 10		//一次缓冲的结果个数
#define WATCHTIME 30	//看门狗线程的睡眠时间(分钟)
#define VehSize 3		//每个镜头下选择关键帧的个数
#define SCALE 0.5		//下采样比率
#define WAITMS 50		//线程同步时等待的时间(毫秒)
#define FRQ 10			//每FRQ个结果存储一次

#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_core249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_highgui249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_objdetect249"ISDEBUG".lib")
#pragma comment(lib, OPENCVDIR PLATFORM"\\vc11\\lib\\opencv_imgproc249"ISDEBUG".lib")
