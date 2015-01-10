
#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <StrSafe.h>
#include <Windows.h>

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

HWND hwnd;
HINSTANCE hInst;
int idFocus;
WNDPROC OldScroll[3];


INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName = TEXT("NOTEPAD FAKE");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, MAKEINTRESOURCE(IDR_MENU2));
	hwWindow hWindow;
	winClass.registerClass();
	hWindow.creatWindow(hInstance, lpszClassName, lpszMenuName);
	hWindow.showWindow();
	hwnd = hWindow.getHwnd();
	hInst = hInstance;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch (msg){
	case WM_CREATE:
		return 0;
	case WM_COMMAND:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
