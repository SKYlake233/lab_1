#include<windows.h>
#include"resource.h"
#include<windowsx.h>


LRESULT CALLBACK WndProc(HWND , UINT ,WPARAM , LPARAM);
void DrawCircle(HDC hDC, int x, int y, int r, COLORREF color);

int  WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPWSTR pCmdLine, int nCmdShow) {

	MSG Msg;
	//init
	WNDCLASSEX wndclass;
	WCHAR lpszClassName[] = L"简单窗口";
	wndclass.style = 0;
	wndclass.lpfnWndProc = WndProc;
	wndclass.cbClsExtra = 0;
	wndclass.cbWndExtra = 0;
	wndclass.hInstance = hInstance;
	wndclass.hIcon = LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wndclass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName = nullptr;
	wndclass.lpszClassName = lpszClassName;
	wndclass.hIconSm = LoadIcon(nullptr, IDI_APPLICATION);
	wndclass.cbSize = sizeof(WNDCLASSEX);

	//regis
	if (!RegisterClassExW(&wndclass)) {
		return false;
	}

	// handler of windows
	HWND hwnd;
	WCHAR lpszTitle[] = L"我的API函数";
	hwnd = CreateWindow(
		lpszClassName,
		lpszTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	//显示窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	

	//开始监听
	while (GetMessage(&Msg, NULL, 0, 0)) {
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}

	return 0;
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
	HDC hDC;
	POINT pt;
	PAINTSTRUCT ps;
	
	
	//设置字体
	HFONT hFONT = CreateFont(
		-15/*高度*/, -7.5/*宽度*/, 0/*不用管*/, 0/*不用管*/, 400 /*一般这个值设为400*/,
		TRUE/*不带斜体*/, TRUE/*不带下划线*/, FALSE/*不带删除线*/,
		DEFAULT_CHARSET,  //这里我们使用默认字符集，还有其他以 _CHARSET 结尾的常量可用
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //这行参数不用管
		DEFAULT_QUALITY,  //默认输出质量
		FF_DONTCARE,  //不指定字体族*/
		TEXT("微软雅黑")  //字体名
	);


	
	switch (message)
	{
	case(WM_DESTROY):
		PostQuitMessage(0);
		break;
		
	//点击鼠标左键，画圆
	case(WM_LBUTTONDOWN):
		pt.x = 0;
		pt.y = 0;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		//get HDC (环境句柄)
		hDC = GetDC(hwnd);
		DrawCircle(hDC, pt.x, pt.y, 100, RGB(255, 0, 0));
		ReleaseDC(hwnd,hDC);
		break;
		//点击鼠标右键，写字
	case(WM_RBUTTONDOWN):
		pt.x = 0;
		pt.y = 0;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);
		hDC = GetDC(hwnd);
		SelectObject(hDC, hFONT);
		TextOut(hDC, pt.x, pt.y, L"hello world!", 12);
		break;

	//case(WM_LBUTTONDOWN):
	//{
	//	pt.x = 0;
	//	pt.y = 0;
	//	pt.x = GET_X_LPARAM(lParam);
	//	pt.y = GET_Y_LPARAM(lParam);
	//	hDC = GetDC(hwnd);
	// hdcm  （图片内存句柄）
	//	HDC hDCm = CreateCompatibleDC(hDC);
	//	HINSTANCE hInst = GetWindowInstance(hwnd);
	//	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"./bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//	SelectObject(hDCm, hBitmap);
	//	//绘图
	//	BitBlt(hDC, pt.x, pt.y, 200, 200, hDCm, 0, 0, SRCCOPY);
	//	ReleaseDC(hwnd, hDC); break;
	//}

		

	////默认绘图方式
	//case WM_PAINT:
	//{
	//	//获得鼠标位置
	//	POINT pt;
	//	pt.x = 0;
	//	pt.y = 0;
	//	pt.x = GET_X_LPARAM(lParam);
	//	pt.y = GET_Y_LPARAM(lParam);
	//	//开始绘图
	//	hDC = BeginPaint(hwnd, &ps);
	//	DrawCircle(hDC, (int)pt.x, (int)pt.y, 300, RGB(255, 0, 0));
	//	EndPaint(hwnd, &ps);
	//}
	//	break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

void DrawCircle(HDC hDC, int x, int y, int r, COLORREF color) {
	//开始画图 
	HBRUSH hBrush = CreateSolidBrush(color);
	HBRUSH hOldBrush = (HBRUSH)SelectObject(hDC, hBrush);

	HPEN hPen = CreatePen(PS_SOLID, 1, color);
	HPEN hOldPen = (HPEN)SelectObject(hDC, hPen);

	//draw circle
	Ellipse(hDC, x - r , y - r , x + r , y + r);

	SelectObject(hDC, hOldBrush);
	DeleteObject(hPen);

	SelectObject(hDC, hOldPen);
	DeleteObject(hOldBrush);
}
