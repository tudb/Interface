#pragma once
#include <Windows.h>

class GroupBox{
	HWND hwnd;
	RECT rect;
public:
	GroupBox();
	HWND create(LPWSTR lpButtons, LPWSTR lpszWindowName, int iStyle, int x, int y, int iWidth, int iHeight, HWND hwnd);
	~GroupBox();
	RECT getRect();
	HWND getHwnd();
};

