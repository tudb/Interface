#pragma once
#include <Windows.h>

class hwWindow{
protected:
	HWND hwnd;
public:
	hwWindow();
	~hwWindow();
	void creatWindow(HINSTANCE hInstance, LPCTSTR className, LPCTSTR windowName, HWND hwnd = NULL, 
					DWORD dStyle = WS_OVERLAPPEDWINDOW, DWORD dxStyle =0L, 
					int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int nWidth = CW_USEDEFAULT, 
					int nHeight = CW_USEDEFAULT);
	BOOL showWindow(int nCmdShow = SW_SHOWNORMAL);
	HWND getHwnd();
};

