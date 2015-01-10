#include "hwWindow.h"


hwWindow::hwWindow(){
}


hwWindow::~hwWindow(){
}

void hwWindow::creatWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName, HWND hwnd, DWORD dStyle, DWORD dxStyle, int x, int y, int nWidth, int nHeight){
	(*this).hwnd = CreateWindowEx(dxStyle, className, windowName, dStyle, x, y, nWidth, nHeight, hwnd, NULL, hInstance, NULL);
}

BOOL hwWindow::showWindow(int nCmdShow){
	if (!ShowWindow(hwnd, nCmdShow)) {
		UpdateWindow(hwnd);
		GetClientRect(hwnd, &rect);
		return TRUE;
	}
	else {
		return FALSE;
	}
}

HWND hwWindow::getHwnd(){
	return hwnd;
}

HWND hwWindow::CreateANewFrame(HWND hwnd, LPCWSTR lpszClassName,
	LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndFrameProc, int x, int y, int iWidth, int iHeight, DWORD dxStyle){
		HWND hwndChild;
		ClassRegister winClassChild(hInstance, lpszClassName, wndFrameProc, NULL);
		hwWindow hWindowChild;
		winClassChild.registerClass();
		hWindowChild.creatWindow(hInstance, lpszClassName, lpszMenuName, hwnd, dxStyle , 0L, x, y, iWidth, iHeight);
		hWindowChild.showWindow();
		hwndChild = hWindowChild.getHwnd();
		(*this).hwnd = hwndChild;
		if (!hwndChild){
			MessageBox(hwnd, L"ERROR CREATE WINDOWCHILD", L"ERROR", 0);
			return (HWND)NULL;
		}
		GetClientRect(hwndChild, &rect);
		return hwndChild;
}

RECT hwWindow::getRect(){
	return rect;
}