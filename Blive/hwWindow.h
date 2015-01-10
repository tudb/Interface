#pragma once
#include <Windows.h>
#include "ClassRegister.h"

class hwWindow{
protected:
	HWND hwnd;
	RECT rect;
public:
	hwWindow();
	~hwWindow();
	void creatWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName, HWND hwnd = NULL, 
					DWORD dStyle = WS_OVERLAPPEDWINDOW, DWORD dxStyle =0L, 
					int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, 
					int nHeight = CW_USEDEFAULT);
	HWND CreateANewFrame(HWND hwnd, LPCWSTR lpszClassName,
		LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndFrameProc, int x, int y, int iWidth, int iHeight, DWORD dxStyle = WS_EX_CLIENTEDGE | WS_EX_STATICEDGE | WS_CHILD | WS_OVERLAPPEDWINDOW);
	BOOL showWindow(int nCmdShow = SW_SHOWNORMAL);
	HWND getHwnd();
	RECT getRect();
};

