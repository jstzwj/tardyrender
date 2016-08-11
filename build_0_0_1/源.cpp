#include <windows.h>
#include"tardyrender.h"

void WinFlush(HWND hwnd,ColorRGBAf * src, TRuint w,TRuint h)
{
	HDC hdc;
	HBRUSH NewBrush;
	PAINTSTRUCT ps;
	ColorRGBAf c;
	HDC hmemorydc, hmemorydc2;
	HBITMAP bimp, bimp2;

	static TRuint oldw = w;
	static TRuint oldh = h;
	static UINT * winbuffer = (UINT *)malloc(sizeof(UINT)*w*h);
	if (oldw!=w||oldh!=h)
	{
		free(winbuffer);
		winbuffer = (UINT *)malloc(sizeof(UINT)*w*h);
	}
	
	for (int i = 0; i < h; ++i)
	{
		for (int j = 0; j < w; ++j)
		{
			winbuffer[i*w + j] = (unsigned int)(src[i*w + j].alpha * 255)<<24;
			winbuffer[i*w + j] |= (unsigned int)(src[i*w + j].red * 255)<<16;
			winbuffer[i*w + j] |= (unsigned int)(src[i*w + j].green * 255)<<8;
			winbuffer[i*w + j] |= (unsigned int)(src[i*w + j].blue * 255);
		}
	}

	hdc = BeginPaint(hwnd, &ps);
	//�����ڴ��豸
	hmemorydc = CreateCompatibleDC(GetDC(hwnd));
	//���ڴ��豸�ϴ�������λͼ
	CreateCompatibleBitmap(hmemorydc, w, h);
	//����λͼ
	bimp=CreateBitmap(w,h,1,32,winbuffer);
	//����λͼ
	//bimp = (HBITMAP)LoadImage(NULL, L"C:\\aa.bmp", IMAGE_BITMAP, w, h, LR_LOADFROMFILE);
	//ѡ��λͼ���ڴ��豸
	SelectObject(hmemorydc, bimp);

	//��ͼ���Ȼ����ڴ��豸��
	BitBlt(hmemorydc, 0, 0, w, h, (HDC)bimp, 0, 0, SRCCOPY);
	//�ڴ��豸������Ļ�豸��
	BitBlt(hdc, 0, 0, w, h, hmemorydc, 0, 0, SRCCOPY);
	EndPaint(hwnd, &ps);

	hdc = GetDC(hwnd);
	
	ReleaseDC(hwnd, hdc);
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{

	//HDC hdc;
	//PAINTSTRUCT ps;
	static RECT rect;
	//HBRUSH NewBrush;

	switch (message)
	{
	case WM_CREATE:
		//PlaySound(TEXT("hellowin.wav"), NULL, SND_FILENAME | SND_ASYNC);
		//do something
		//����initialize
		trClearColor(0.0, 0.0, 0.0, 1.0);
		return 0;
	case WM_SIZE:
		GetWindowRect(hwnd,&rect);
		//�������
		trViewport(0, 0, (TRint)(rect.right - rect.left), (TRint)(rect.bottom - rect.top));//���õ�ǰ�ӿ�
		trMatrixMode(TR_PROJECTION);//ѡ��ͶӰ����
		trLoadIdentity();//����ѡ��õ�ͶӰ����


	case WM_PAINT:
		/*hdc = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &rect);
		DrawText(hdc, TEXT("Hello, Windows 98!"), -1, &rect, DT_SINGLELINE | DT_CENTER | DT_VCENTER);
		EndPaint(hwnd, &ps);*/
		//��ʼ��ͼ
		trClear(TR_COLOR_BUFFER_BIT | TR_DEPTH_BUFFER_BIT);
		trBegin(TR_POINTS);
		trVertex4d(0.5,0.5,0.0,1.0);
		trEnd();
		WinFlush(hwnd, frontBuffer, rect.right - rect.left, rect.bottom - rect.top);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd, message, wParam, lParam);
}
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	static TCHAR szAppName[] = TEXT("HelloWin");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style = CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	//wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.hbrBackground = NULL;
	wndclass.lpszMenuName = NULL;
	wndclass.lpszClassName = szAppName;
	if (!RegisterClass(&wndclass))
	{
		MessageBox(NULL, TEXT("This program requires Windows NT!"), szAppName, MB_ICONERROR);
		return 0;
	}
	hwnd = CreateWindow(szAppName, // window class name      
		TEXT("The Hello Program"), // window caption      
		WS_OVERLAPPEDWINDOW, // window style      
		CW_USEDEFAULT,// initial x position      
		CW_USEDEFAULT,// initial y position     
		CW_USEDEFAULT,// initial x size      
		CW_USEDEFAULT,// initial y size      
		NULL, // parent window handle      
		NULL, // window menu handle    
		hInstance, // program instance handle    
		NULL); // creation parameters    
	ShowWindow(hwnd, iCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}


