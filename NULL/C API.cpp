#include<windows.h>

//���ں���˵��
LRESULTCALLBACKWndProc(HWND,UINT,WPARAM,LPARAM);

//��ʼ��������
//WinMain����˵��
intWINAPIWinMain(HINSTANCEhInstance,HINSTANCEhPrevInst,LPSTRlpszCmdLine,intnCmdShow)
{
HWNDhwnd;
MSGMsg;
WNDCLASSwndclass;
charlpszClassName[]="����";//��������
charlpszTitle[]="My_Windows";//���ڱ�����

//������Ķ���
wndclass.style=0;//��������Ϊȱʡ����
wndclass.lpfnWndProc=WndProc;//���ڴ�����ΪWndProc
wndclass.cbClsExtra=0;//����������չ
wndclass.cbWndExtra=0;//����ʵ������չ
wndclass.hInstance=hInstance;//��ǰʵ�����
wndclass.hIcon=LoadIcon(NULL,IDI_APPLICATION);
//���ڵ���С��ͼ��Ϊȱʡͼ��
wndclass.hCursor=LoadCursor(NULL,IDC_ARROW);
//���ڲ��ü�ͷ���
wndclass.hbrBackground=GetStockObject(WHITE_BRUSH);
//���ڱ���Ϊ��ɫ
wndclass.lpszMenuName=NULL;//�������޲˵�
wndclass.lpszClassName=lpszClassName;//��������Ϊ"����ʾ��"

//������ע��
if(!RegisterClass(&wndclass))//���ע��ʧ���򷢳���������
{
MessageBeep(0);
returnFALSE;
}

//��������
hwnd=CreateWindow(lpszClassName,//��������
lpszTitle,//����ʵ���ı�����
WS_OVERLAPPEDWINDOW,//���ڵķ��
CW_USEDEFAULT,
CW_USEDEFAULT,//�������Ͻ�����Ϊȱʡֵ
CW_USEDEFAULT,
CW_USEDEFAULT,,//���ڵĸߺͿ�Ϊȱʡֵ
NULL,//�˴����޸�����
NULL,//�˴��������˵�
hInstance,//�����˴��ڵ�Ӧ�ó���ĵ�ǰ���
NULL);//��ʹ�ø�ֵ

//��ʾ����
ShowWindow(hwnd,nCmdShow);
//�����û���
UpdateWindow(hwnd);
//��Ϣѭ��
while(GetMessage(&Msg,NULL,0,0))
{
TranslateMessage(&Msg);
DispatchMessage(&Msg);
}

returnMsg.wParam;//��Ϣѭ��������������ֹʱ����Ϣ����ϵͳ
}

//���ں���
LRESULTCALLBACKWndProc(HWNDhwnd,UINTmessage,WPARAMwParam,LPARAMlParam)
{
switch(message)
{
caseWM_DESTROY:
PostQuitMessage(0);//����PostQuitMessage����WM_QUIT��Ϣ

default://Ĭ��ʱ����ϵͳ��ϢĬ�ϴ�����
returnDefWindowProc(hwnd,message,wParam,lParam);
}
return0;
}

