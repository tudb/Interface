#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <Windows.h>

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProcFrame1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
void CreateButtons(HWND hwnd, LPARAM lParam);
HWND CreateAGroupBox(HWND hwnd, LPARAM lParam);
HWND CreateANewWindow(HWND hwnd, LPCWSTR lpszClassName, LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndFrameProc);

HWND hwnd, hwndChild, hwndButtonsTop[3], hwndGroupBox, hwndFrame;
HINSTANCE hInst;

Buttons g_pButtonsTop[3];

static RECT g_rectWindow;

double g_fxRateSize = 1, g_fyRateSize = 1;
int g_cxChar, g_cyChar;
static RECT g_rectFrame[2];

RECT rectTemp;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName = TEXT("Blive");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, NULL);
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
		CreateButtons(hwnd, lParam);
		hwndGroupBox = CreateAGroupBox(hwnd, lParam);
		hwndFrame = CreateANewWindow(hwnd, L"Static", NULL, hInst, wndProcFrame1);
		return 0;
	case WM_SIZE:
		break;
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

void CreateButtons(HWND hwnd, LPARAM lParam){
	g_cxChar = LOWORD(GetDialogBaseUnits());
	g_cyChar = HIWORD(GetDialogBaseUnits());
	g_pButtonsTop[0].import(BS_DEFPUSHBUTTON, TEXT("Thiết lập"));
	g_pButtonsTop[1].import(BS_DEFPUSHBUTTON, TEXT("Phát hình"));
	g_pButtonsTop[2].import(BS_DEFPUSHBUTTON, TEXT("Ghi hình"));
	for (int nCount = 0; nCount < 3; nCount++){
		hwndButtonsTop[nCount] = g_pButtonsTop[nCount].createButton(L"BUTTON", 20 + g_cxChar *(1 + 12 * nCount), g_cyChar, 10 * g_cxChar, 5 * g_cyChar / 4, hwnd, nCount, lParam);
	}
}

HWND CreateAGroupBox(HWND hwnd, LPARAM lParam){
	HWND hwndTemp;
	g_cxChar = LOWORD(GetDialogBaseUnits());
	g_cyChar = HIWORD(GetDialogBaseUnits());
	RECT rect, rectSave;

	GetClientRect(hwnd, &rect);

	hwndTemp = CreateWindow(TEXT("Button"), L"GroupBox Control", WS_CHILD | WS_VISIBLE | BS_GROUPBOX | BS_CENTER,
		0, 0, rect.right - rect.left, 30 + 5 * g_cyChar / 4, hwnd, 0, GetModuleHandle(0), 0);
	if (!hwndTemp) {
		MessageBox(hwnd, L"Creat Groupbox error", L"ERROR", 0);
		return (HWND)NULL;
	}
	return hwndTemp;
}

HWND CreateANewWindow(HWND hwnd, LPCWSTR lpszClassName, LPCWSTR lpszMenuName, HINSTANCE hInstance, WNDPROC wndProcFrame){
	HWND hwndChild;
	ClassRegister winClassChild(hInstance, lpszClassName, wndProcFrame, NULL);
	hwWindow hWindowChild;
	winClassChild.registerClass();
	hWindowChild.creatWindow(hInstance, lpszClassName, lpszMenuName, hwnd, WS_BORDER | WS_VISIBLE | WS_CHILD, 0L, 0, 60, 200, 200);
	hWindowChild.showWindow();
	hwndChild = hWindowChild.getHwnd();
	LONG lStyle = GetWindowLong(hwnd, GWL_STYLE);
	lStyle &= ~(WS_CAPTION | WS_THICKFRAME | WS_MINIMIZE | WS_MAXIMIZE | WS_SYSMENU);
	SetWindowLong(hwndChild, GWL_STYLE, lStyle);
	GetClientRect(hwndChild, &g_rectFrame[0]);

	if (!hwndChild){
		MessageBox(hwnd, L"ERROR CREATE WINDOWCHILD", L"ERROR", 0);
		return (HWND)NULL;
	}
	ShowWindow(hwndFrame, SW_NORMAL);
	UpdateWindow(hwndFrame);
	return hwndChild;
}

LRESULT CALLBACK wndProcFrame1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_MOVE:
		//MoveWindow(hwndFrame, 0, 50, float(g_rectFrame[0].right) * fxRateSize, float(g_rectFrame[0].bottom) *fyRateSize, FALSE);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}