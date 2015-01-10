#pragma once
#include <tchar.h>
#include <Windows.h>

class Buttons{
protected:
	int iStyle;
	TCHAR *szText;
public:
	Buttons();
	void import(int, TCHAR*);
	HWND createButton(LPCTSTR, int, int, int, int, HWND, int, LPARAM);
	~Buttons();
};

