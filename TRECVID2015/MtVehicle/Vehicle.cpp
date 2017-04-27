#include "Vehicle.h"
#define BASE_DIR "F:\\Programs\\OPENCV\\opencv\\build\\x86"
#ifndef _DEBUG
#pragma comment(lib, BASE_DIR"\\vc11\\lib\\opencv_core249.lib")
#pragma comment(lib, BASE_DIR"\\vc11\\lib\\opencv_highgui249.lib")
#pragma comment(lib, BASE_DIR"\\vc11\\lib\\opencv_objdetect249.lib")
#pragma comment(lib, BASE_DIR"\\vc11\\lib\\opencv_imgproc249.lib")
#else
#pragma comment(lib, "F:\\Programs\\OPENCV\\opencv\\build\\x86\\vc11\\lib\\opencv_core249d.lib")
#pragma comment(lib, "F:\\Programs\\OPENCV\\opencv\\build\\x86\\vc11\\lib\\opencv_highgui249d.lib")
#pragma comment(lib, "F:\\Programs\\OPENCV\\opencv\\build\\x86\\vc11\\lib\\opencv_objdetect249d.lib")
#pragma comment(lib, "F:\\Programs\\OPENCV\\opencv\\build\\x86\\vc11\\lib\\opencv_imgproc249d.lib")
#endif

Vehicle::Vehicle(void)
{
}


Vehicle::~Vehicle(void)
{
}


int Vehicle::init(string model)
{
	if(!(lsd=cvLoadLatentSvmDetector(model.c_str()))){ 
		printf("[error] 无法加载级联分类器文件！\n");
		return -1; 
	}
	return 0;
}


bool Vehicle::judge(IplImage *img)
{
	CvSize sz;
	sz.width = img->width*SCALE;
	sz.height = img->height*SCALE;
	IplImage *img_sz = cvCreateImage(sz,img->depth,img->nChannels);
	cvResize(img, img_sz, CV_INTER_AREA); 
	Mat mat_frame(img_sz);
	std::vector<Rect> v_vehicles;
	CvMemStorage* storage = cvCreateMemStorage(0);
	CvSeq* detections = 0;
	int i = 0;
	detections = cvLatentSvmDetectObjects(img_sz,lsd,storage,0.02);
	for( i = 0; i < detections->total; i++ )
	{
		CvObjectDetection detection = *(CvObjectDetection*)cvGetSeqElem( detections, i );
		if (detection.rect.height>=100&&detection.rect.width>=100)/*车辆过滤*/
		{
			v_vehicles.push_back(detection.rect);
		}
	}
	cvReleaseMemStorage( &storage );	
	cvReleaseImage(&img_sz);
	cvReleaseImage(&img);
	return v_vehicles.size() > 0;
}
