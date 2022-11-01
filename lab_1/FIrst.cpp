#include<windows.h>
#include"resource.h"
#include<windowsx.h>


LRESULT CALLBACK WndProc(HWND , UINT ,WPARAM , LPARAM);
void DrawCircle(HDC hDC, int x, int y, int r, COLORREF color);

int  WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInst, LPWSTR pCmdLine, int nCmdShow) {

	MSG Msg;
	//init
	WNDCLASSEX wndclass;
	WCHAR lpszClassName[] = L"�򵥴���";
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
	WCHAR lpszTitle[] = L"�ҵ�API����";
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
	//��ʾ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	

	//��ʼ����
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
	
	
	//��������
	HFONT hFONT = CreateFont(
		-15/*�߶�*/, -7.5/*���*/, 0/*���ù�*/, 0/*���ù�*/, 400 /*һ�����ֵ��Ϊ400*/,
		TRUE/*����б��*/, TRUE/*�����»���*/, FALSE/*����ɾ����*/,
		DEFAULT_CHARSET,  //��������ʹ��Ĭ���ַ��������������� _CHARSET ��β�ĳ�������
		OUT_CHARACTER_PRECIS, CLIP_CHARACTER_PRECIS,  //���в������ù�
		DEFAULT_QUALITY,  //Ĭ���������
		FF_DONTCARE,  //��ָ��������*/
		TEXT("΢���ź�")  //������
	);


	
	switch (message)
	{
	case(WM_DESTROY):
		PostQuitMessage(0);
		break;
		
	//�������������Բ
	case(WM_LBUTTONDOWN):
		pt.x = 0;
		pt.y = 0;
		pt.x = GET_X_LPARAM(lParam);
		pt.y = GET_Y_LPARAM(lParam);

		//get HDC (�������)
		hDC = GetDC(hwnd);
		DrawCircle(hDC, pt.x, pt.y, 100, RGB(255, 0, 0));
		ReleaseDC(hwnd,hDC);
		break;
		//�������Ҽ���д��
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
	// hdcm  ��ͼƬ�ڴ�����
	//	HDC hDCm = CreateCompatibleDC(hDC);
	//	HINSTANCE hInst = GetWindowInstance(hwnd);
	//	HBITMAP hBitmap = (HBITMAP)LoadImage(NULL, L"./bitmap1.bmp", IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//	SelectObject(hDCm, hBitmap);
	//	//��ͼ
	//	BitBlt(hDC, pt.x, pt.y, 200, 200, hDCm, 0, 0, SRCCOPY);
	//	ReleaseDC(hwnd, hDC); break;
	//}

		

	////Ĭ�ϻ�ͼ��ʽ
	//case WM_PAINT:
	//{
	//	//������λ��
	//	POINT pt;
	//	pt.x = 0;
	//	pt.y = 0;
	//	pt.x = GET_X_LPARAM(lParam);
	//	pt.y = GET_Y_LPARAM(lParam);
	//	//��ʼ��ͼ
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
	//��ʼ��ͼ 
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
