# 车辆检测
## 说明
使用[Latent SVM][0]做车辆检测，多线程用windows API实现，
可作为参考程序，建议改用OpenMP实现如果要改车辆检测
算法，请重写Vehicle类的bool judge(IplImage *img)方
法阅读源码时，建议先看main.cpp文件，了解程序的大体
框架后，再有针对性地看头文件

## 开发环境
- vs2012
- opencv 2.4.9

[0]: http://docs.opencv.org/2.4/modules/objdetect/doc/latent_svm.html
