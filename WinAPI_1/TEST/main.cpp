#include <Windows.h>
#include <StrSafe.h>
#include <stdio.h>
#include "resource.h"
#include <time.h>
#include <stdio.h>

#define MAX_POINT 10000
#define IDT_TIMER1 1

#define IDC_MAIN_BUTTON	101			// Button identifier
#define IDC_MAIN_EDIT	102			// Edit box identifier

VOID CALLBACK TimerProc(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

HWND hEdit;
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);


HFONT hFontNew, hFontOld;
HGDIOBJ hgdiOld;
RECT rect;
POINT point[MAX_POINT];
TCHAR random[255];
int iCount = 0;
TEXTMETRIC *textMetric;

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nShowCmd)
{
	WNDCLASSEX wClass;
	ZeroMemory(&wClass, sizeof(WNDCLASSEX));
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wClass.hIcon = NULL;
	wClass.hIconSm = NULL;
	wClass.hInstance = hInst;
	wClass.lpfnWndProc = (WNDPROC)WndProc;
	wClass.lpszClassName = TEXT("Window Class");
	wClass.lpszMenuName = NULL;
	wClass.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&wClass))
	{
		int nResult = GetLastError();
		MessageBox(NULL,
			L"Window class creation failed\r\n",
			L"Window Class Failed",
			MB_ICONERROR);
	}

	HWND hWnd = CreateWindowEx(NULL,
		L"Window Class",
		L"Windows application",
		WS_OVERLAPPEDWINDOW,
		200,
		200,
		640,
		480,
		NULL,
		NULL,
		hInst,
		NULL);

	if (!hWnd)
	{
		int nResult = GetLastError();

		MessageBox(NULL,
			L"Window creation failed\r\n",
			L"Window Creation Failed",
			MB_ICONERROR);
	}

	ShowWindow(hWnd, nShowCmd);

	MSG msg;
	ZeroMemory(&msg, sizeof(MSG));

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;
	switch (msg){
	case WM_CREATE:
		SetTimer(hwnd, IDT_TIMER, 1000, TimerProc);
		break;
	case WM_PAINT:
	{
		RECT rc;
		int angle;
		HFONT hfnt;
		HGDIOBJ hfntPrev;
		LPCWSTR lpszRotate = L"String to be rotated.";
		hdc = GetDC(hwnd);
		// C?p phát vùng nh? cho c?u trúc LOGFONT. 
		PLOGFONT plf = (PLOGFONT)LocalAlloc(LPTR, sizeof(LOGFONT));
		textMetric = (TEXTMETRIC*)LocalAlloc(LPTR, sizeof(TEXTMETRIC));
		// Xác ??nh tên và ?? ??m nh?t c?a font. 
		StringCchCopy(plf->lfFaceName,32, L"Arial");
		plf->lfWeight = FW_NORMAL;
		// Thu nh?n kích th??c c?a vùng làm vi?c c?a s? ?ng d?ng . 
		GetClientRect(hwnd, &rc);
		// Thi?t l?p ch? ?? n?n TRANSPARENT cho thao tác xu?t v?n b?n.
		SetBkMode(hdc, TRANSPARENT);
		// V? chu?i quay quanh tâm vùng làm vi?c t?ng 10 ?? (36 l?n).
		plf->lfHeight	    	= 10;
		plf->lfWidth		    = 20;
		plf->lfEscapement       = 0;
		plf->lfOrientation      = 0;
		plf->lfWeight           = FW_THIN;
		plf->lfItalic           = TRUE;
		plf->lfUnderline	    = TRUE;
		plf->lfStrikeOut	    = TRUE;
		plf->lfCharSet		    = DEFAULT_CHARSET;
		hFontNew = CreateFontIndirect(plf);
		StringCchCopy(plf->lfFaceName, 32,L"Tahedfoma");
		hgdiOld = SelectObject(hdc, hFontNew);
		SetTextColor(hdc, RGB(255, 0, 255));
		SetBkColor(hdc, RGB(0, 255, 0));
		SetBkMode(hdc, OPAQUE);
		TextOut(hdc, 100, 100, L"NOTHING IS IMPOSSIBLE", 50);
		GetTextMetrics(hdc, textMetric);
		// Chuy?n ch? ?? hi?n th? v? l?i d?ng OPAQUE. 
		SelectObject(hdc, hgdiOld);
		// Gi?i phóng vùng nh? ?ã c?p phát cho c?u trúc LOGFONT. 
		DeleteObject(hgdiOld);
		LocalFree((LOCALHANDLE)plf);
	}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

VOID CALLBACK TimerProc(HWND hwnd, UINT msg, UINT_PTR idEvent, DWORD dwTime){
	iCount++;
	GetClientRect(hwnd, &rect);
	InvalidateRect(hwnd, &rect, TRUE);
}