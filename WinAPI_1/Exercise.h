
#pragma once

#include "ClassRegister.h"
#include "hwWindow.h"
//---------------------------------------------------------------------------
class Exercise
{
public:
	Exercise();
	ClassRegister Wnd;
	HINSTANCE hInst;
	hwWindow WinApp;
	HWND CreateStandardToolbar(HWND hParent, HINSTANCE hInst);
	HWND hWndToolbar;

public:
	void ChangeCurrentCursor(HWND hWnd, LPCTSTR cursor);
};
//---------------------------------------------------------------------------
LRESULT CALLBACK MainWndProc(HWND hWnd, UINT Msg,
	WPARAM wParam, LPARAM lParam);
INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInst,
	LPSTR lpCmdLine, int nCmdShow);
//---------------------------------------------------------------------------
