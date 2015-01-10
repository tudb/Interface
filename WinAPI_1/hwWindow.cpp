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