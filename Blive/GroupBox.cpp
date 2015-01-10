#include "GroupBox.h"


GroupBox::GroupBox(){
	hwnd = (HWND)NULL;
	rect = { 0, 0, 0, 0 };
}


GroupBox::~GroupBox()
{
}

RECT GroupBox::getRect(){
	return rect;
}

HWND GroupBox::getHwnd(){
	return hwnd;
}

HWND GroupBox::create(LPWSTR lpButtons, LPWSTR lpszWindowName, int iStyle, int x, int y, int iWidth, int iHeight, HWND hwnd)
{
	HWND hwndTemp;
	RECT rect;
	hwndTemp = CreateWindow(lpButtons, lpszWindowName, WS_CHILD | WS_VISIBLE | BS_GROUPBOX | WS_OVERLAPPED | iStyle,
		x, y, iWidth, iHeight, hwnd, 0, GetModuleHandle(0), 0);
	if (!hwndTemp) {
		MessageBox(hwnd, L"Creat Groupbox error", L"ERROR", 0);
	}
	else {

		GetClientRect(hwnd, &rect);
		hwnd = hwndTemp;
	}
	return hwndTemp;
}