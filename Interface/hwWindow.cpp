#include "hwWindow.h"


hwWindow::hwWindow(){
}


hwWindow::~hwWindow(){
}

void hwWindow::creatWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName, HWND hwnd, DWORD dStyle, DWORD dxStyle, int x, int y, int nWidth, int nHeight){
	(*this).hwnd = CreateWindowEx(dxStyle, className, windowName, dStyle, x, y, nWidth, nHeight, hwnd, NULL, hInstance, NULL);
}

BOOL hwWindow::showWindow(int nCmdShow){
	if ((ShowWindow(hwnd, nCmdShow)) && UpdateWindow(hwnd)) return TRUE;
	else {
		return FALSE;
	}
}

HWND hwWindow::getHwnd(){
	return hwnd;
}

HWND hwWindow::CreateANewWindow(HWND hwnd, LPCWSTR lpszClassName,
	LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndFrameProc, int x, int y, int iWidth, int iHeight){
	HWND CreateANewWindow(HWND hwnd, LPCWSTR lpszClassName, LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndProcFrame, int x, int y, int iWidth, int iHeight){
		HWND hwndChild;
		ClassRegister winClassChild(hInstance, lpszClassName, wndProcFrame, NULL);
		hwWindow hWindowChild;
		winClassChild.registerClass();
		hWindowChild.creatWindow(hInstance, lpszClassName, lpszMenuName, hwnd, WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CHILD | WS_OVERLAPPEDWINDOW, 0L, x, y, iWidth, iHeight);
		hWindowChild.showWindow();
		hwndChild = hWindowChild.getHwnd();

		if (!hwndChild){
			MessageBox(hwnd, L"ERROR CREATE WINDOWCHILD", L"ERROR", 0);
			return (HWND)NULL;
		}
		ShowWindow(hwndFrame, SW_NORMAL);
		UpdateWindow(hwndFrame);
		return hwndChild;
	}
}