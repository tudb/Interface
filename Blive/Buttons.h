#pragma once
#include <tchar.h>
#include <Windows.h>

class Buttons{
protected:
	HWND hwnd;
	int iStyle;
	TCHAR *szText;
	RECT rect;
public:
	Buttons();
	void import(int, TCHAR*);
	HWND createButton(LPCTSTR, int, int, int, int, HWND, int, LPARAM);
	RECT getRect();
	TCHAR* getText();
	HWND getHwnd();
	~Buttons();
};

