#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <StrSafe.h>
#include <stdio.h>
#include <Windows.h>

/*
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hwnd;
HINSTANCE hInst;
int idFocus;
WNDPROC OldScroll[3];
int iColor = 0;
static POINT pointNew, pointOld;
TCHAR buff[255];


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName = TEXT("Mouse Control");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, MAKEINTRESOURCE(IDR_MENU2));
	hwWindow hWindow;
	winClass.registerClass();
	hWindow.creatWindow(hInstance, lpszClassName, lpszMenuName);
	hWindow.showWindow();
	hwnd = hWindow.getHwnd();
	hInst = hInstance;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	HDC hdc;
	HPEN hPen, oPen;
	COLORREF clrArray[] = { RGB(255, 0, 0), RGB(0, 255, 0), RGB(0, 0, 255) };
	switch (msg){
	case WM_CREATE:
		return 0;
	case WM_LBUTTONDOWN:
		hdc = GetDC(hwnd);
		pointNew.x = LOWORD(lParam);
		pointNew.y = HIWORD(lParam);
		hPen = CreatePen(PS_SOLID, 5, clrArray[iColor]);
		oPen = (HPEN)SelectObject(hdc, hPen);
		MoveToEx(hdc, pointOld.x, pointOld.y, NULL);
		LineTo(hdc, pointNew.x, pointNew.y);
		pointOld = pointNew;
		SelectObject(hdc, oPen);
		DeleteObject(hPen);
		ReleaseDC(hwnd, hdc);
		break;
	case WM_RBUTTONDOWN:
		iColor = (iColor + 1) % 3;
		break;
	case WM_MOUSEMOVE:
		StringCbPrintf(buff, 255, TEXT("TOA DO CHUOT X = %d, Y = %d"), LOWORD(lParam), HIWORD(lParam));
		SetWindowText(hwnd, buff);
		if (wParam && (MK_LBUTTON)){
			hdc = GetDC(hwnd);
			pointNew.x = LOWORD(lParam);
			pointNew.y = HIWORD(lParam);
			hPen = CreatePen(PS_SOLID, 5, clrArray[iColor]);
			oPen = (HPEN)SelectObject(hdc, hPen);
			MoveToEx(hdc, pointNew.x, pointNew.y, NULL);
			LineTo(hdc, pointOld.x, pointOld.y);
			SelectObject(hdc, oPen);
			DeleteObject(hPen);
			pointOld = pointNew;
			ReleaseDC(hwnd, hdc);
			break;
		}
		break;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

*/