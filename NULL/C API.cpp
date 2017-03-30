#include<windows.h>

//窗口函数说明
LRESULTCALLBACKWndProc(HWND,UINT,WPARAM,LPARAM);

//初始化窗口类
//WinMain函数说明
intWINAPIWinMain(HINSTANCEhInstance,HINSTANCEhPrevInst,LPSTRlpszCmdLine,intnCmdShow)
{
HWNDhwnd;
MSGMsg;
WNDCLASSwndclass;
charlpszClassName[]="窗口";//窗口类名
charlpszTitle[]="My_Windows";//窗口标题名

//窗口类的定义
wndclass.style=0;//窗口类型为缺省类型
wndclass.lpfnWndProc=WndProc;//窗口处理函数为WndProc
wndclass.cbClsExtra=0;//窗口类无扩展
wndclass.cbWndExtra=0;//窗口实例无扩展
wndclass.hInstance=hInstance;//当前实例句柄
wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
//窗口的最小化图标为缺省图标
wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
//窗口采用箭头光标
wndclass.hbrBackground=GetStockObject(WHITE_BRUSH);
//窗口背景为白色
wndclass.lpszMenuName=NULL;//窗口中无菜单
wndclass.lpszClassName=lpszClassName;//窗口类名为"窗口示例"

//窗口类注册
if(!RegisterClass(&wndclass))//如果注册失败则发出警告声音
{
MessageBeep(0);
returnFALSE;
}

//创建窗口
hwnd=CreateWindow(lpszClassName,//窗口类名
lpszTitle,//窗口实例的标题名
WS_OVERLAPPEDWINDOW,//窗口的风格
CW_USEDEFAULT,
CW_USEDEFAULT,//窗口左上角坐标为缺省值
CW_USEDEFAULT,
CW_USEDEFAULT,,//窗口的高和宽为缺省值
NULL,//此窗口无父窗口
NULL,//此窗口无主菜单
hInstance,//创建此窗口的应用程序的当前句柄
NULL);//不使用该值

//显示窗口
ShowWindow(hwnd,nCmdShow);
//绘制用户区
UpdateWindow(hwnd);
//消息循环
while(GetMessage(&Msg,NULL,0,0))
{
TranslateMessage(&Msg);
DispatchMessage(&Msg);
}

returnMsg.wParam;//消息循环结束即程序终止时将信息返回系统
}

//窗口函数
LRESULTCALLBACKWndProc(HWNDhwnd,UINTmessage,WPARAMwParam,LPARAMlParam)
{
switch(message)
{
caseWM_DESTROY:
PostQuitMessage(0);//调用PostQuitMessage发出WM_QUIT消息

default://默认时采用系统消息默认处理函数
returnDefWindowProc(hwnd,message,wParam,lParam);
}
return0;
}

