#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "GroupBox.h"
#include "resource.h" 
#include <Windows.h>
#define MAX_WINDOW  10

hwWindow g_hwWindow;
hwWindow g_FrameTop[2];
hwWindow g_hwCamera;
hwWindow g_hwSetting[MAX_WINDOW];

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProcCamera(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

LRESULT CALLBACK wndProcFrame1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK wndProcFrame2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

void CreateButtonsTop(HWND hwnd, LPARAM lParam);
void CreateComponent(HWND hwnd);
void ResizeWindow(HWND hwnd);
void CreateButtonsBottom(HWND hwnd, LPARAM lParam);

HINSTANCE g_hInst;
HWND g_hwnd;
Buttons g_pButtonsTop[3];
Buttons g_pButtonsBottoms[7];
Buttons g_ButtonMiddle;
Buttons g_ButtonsSelect;
GroupBox g_GroupBoxTop;

RECT GetLocalCoordinates(HWND hWnd);
static RECT g_rectWindow = { CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT };
static RECT g_rectCoordinates;

int g_cxChar = LOWORD(GetDialogBaseUnits());
int g_cyChar = HIWORD(GetDialogBaseUnits());
int g_iAmountWindowSetting = 0;
float g_fxRateSize = 1;
float g_fyRateSize = 1;

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName = TEXT("Blive");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, NULL);
	winClass.registerClass();
	g_hwWindow.creatWindow(hInstance, lpszClassName, lpszMenuName);
	g_hwWindow.showWindow();
	hwnd = g_hwWindow.getHwnd();
	g_hInst = hInstance;

	g_rectWindow = g_hwWindow.getRect();
	
	CreateComponent(hwnd);
	MoveWindow(g_ButtonMiddle.getHwnd(), g_hwWindow.getRect().right / 2, g_hwWindow.getRect().bottom / 3, 90, 50, TRUE);
	int ixTemp;
	ixTemp = 5 * g_cxChar;
	for (int iCount = 0; iCount < 7; iCount++){
		MoveWindow(g_pButtonsBottoms[iCount].getHwnd(), ixTemp, g_rectWindow.bottom - 1 * g_cyChar, (lstrlen(g_pButtonsBottoms[iCount].getText()) + 1) * g_cxChar, 2 * g_cyChar, TRUE);
		ixTemp += g_pButtonsBottoms[iCount].getRect().right + 2 * g_cxChar;
	}

	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){

	switch (msg){
	case WM_CREATE:
		CreateButtonsTop(hwnd, lParam);
		CreateButtonsBottom(hwnd, lParam);
		return 0;
	case WM_SIZE:
		ResizeWindow(hwnd);
		POINT point;
		ClientToScreen(hwnd, &point);
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
LRESULT CALLBACK wndProcFrame1(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
		//MoveWindow(hwndFrame, 0, 50, float(g_rectFrame[0].right) * fxRateSize, float(g_rectFrame[0].bottom) *fyRateSize, FALSE);
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
LRESULT CALLBACK wndProcFrame2(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

RECT GetLocalCoordinates(HWND hWnd)
{
	RECT Rect;
	GetWindowRect(hWnd, &Rect);
	MapWindowPoints(HWND_DESKTOP, GetParent(hWnd), (LPPOINT)&Rect, 2);
	return Rect;
}

void CreateButtonsTop(HWND hwnd, LPARAM lParam){
	int g_cxChar = LOWORD(GetDialogBaseUnits());
	int g_cyChar = HIWORD(GetDialogBaseUnits());
	g_pButtonsTop[0].import(BS_DEFPUSHBUTTON, TEXT("Thiết lập"));
	g_pButtonsTop[1].import(BS_DEFPUSHBUTTON, TEXT("Phát hình"));
	g_pButtonsTop[2].import(BS_DEFPUSHBUTTON, TEXT("Ghi hình"));
	for (int nCount = 0; nCount < 3; nCount++){
		g_pButtonsTop[nCount].createButton(L"BUTTON", 20 + g_cxChar *(1 + 12 * nCount), g_cyChar, 10 * g_cxChar, 5 * g_cyChar / 4, hwnd, nCount, lParam);
	}
	g_ButtonMiddle.import(BS_DEFPUSHBUTTON, TEXT("Chuyển kênh"));
	g_ButtonMiddle.createButton(L"BUTTON", g_hwWindow.getRect().right / 2, g_hwWindow.getRect().bottom / 3, 90, 50, hwnd, 3, lParam);
}

void CreateComponent(HWND hwnd){
	g_GroupBoxTop.create(TEXT("Button"), L"Main Window", BS_CENTER,
		0, 0, g_rectWindow.right, g_pButtonsTop[2].getRect().bottom + 30, hwnd);
	g_FrameTop[0].CreateANewFrame(hwnd, L"Static", NULL, g_hInst, wndProcFrame1, 0, 50, g_rectWindow.right / 3, g_rectWindow.bottom / 3);
	g_FrameTop[1].CreateANewFrame(hwnd, L"Static", NULL, g_hInst, wndProcFrame2,
		g_hwWindow.getRect().right * 2 / 3, 50, g_hwWindow.getRect().right / 3, g_hwWindow.getRect().bottom / 3);
}

void ResizeWindow(HWND hwnd){
	RECT rectTemp;
	GetClientRect(hwnd, &rectTemp);
	g_fyRateSize = ((float)rectTemp.bottom / (float)g_rectWindow.bottom);
	g_fxRateSize = ((float)rectTemp.right / (float)g_rectWindow.right);
	MoveWindow(g_GroupBoxTop.getHwnd(), 0, 0, rectTemp.right, g_GroupBoxTop.getRect().bottom, FALSE);
	MoveWindow(g_FrameTop[0].getHwnd(), 0, 50, rectTemp.right / 3, rectTemp.bottom / 3, FALSE);
	MoveWindow(g_FrameTop[1].getHwnd(), rectTemp.right * 2 / 3, 50, rectTemp.right / 3, rectTemp.bottom / 3, FALSE);
	MoveWindow(g_ButtonMiddle.getHwnd(), rectTemp.right / 2, rectTemp.bottom / 4, g_ButtonMiddle.getRect().right * g_fxRateSize, g_ButtonMiddle.getRect().bottom * g_fyRateSize, TRUE);
	int ixTemp;
	ixTemp = 5 * g_cxChar;
	for (int iCount = 0; iCount < 7; iCount++){
		MoveWindow(g_pButtonsBottoms[iCount].getHwnd(), ixTemp * g_fxRateSize, (g_rectWindow.bottom - 4 * g_cyChar) * g_fyRateSize, (lstrlen(g_pButtonsBottoms[iCount].getText()) + 1) * g_cxChar * g_fxRateSize, 2 * g_cyChar * g_fyRateSize, TRUE);
		ixTemp += g_pButtonsBottoms[iCount].getRect().right + 2 * g_cxChar;
	}
}

void CreateButtonsBottom(HWND hwnd, LPARAM lParam){
	g_pButtonsBottoms[0].import(BS_DEFPUSHBUTTON, TEXT("Bộ trộn âm"));
	g_pButtonsBottoms[1].import(BS_DEFPUSHBUTTON, TEXT("Thiết lập thiết bị vào"));
	g_pButtonsBottoms[2].import(BS_DEFPUSHBUTTON, TEXT("Wifi Camera 1"));
	g_pButtonsBottoms[3].import(BS_DEFPUSHBUTTON, TEXT("Hình trộn 1"));
	g_pButtonsBottoms[4].import(BS_DEFPUSHBUTTON, TEXT("Media 1"));
	g_pButtonsBottoms[5].import(BS_DEFPUSHBUTTON, TEXT("Bảng màu 1"));
	g_pButtonsBottoms[6].import(BS_DEFPUSHBUTTON, TEXT("Hiệu ứng"));
	int ixTemp;
	ixTemp = 5 * g_cxChar;
	for (int iCount = 0; iCount < 7; iCount++){
		g_pButtonsBottoms[iCount].createButton(L"BUTTON", ixTemp, g_rectWindow.bottom - 1 * g_cyChar, (lstrlen(g_pButtonsBottoms[iCount].getText()) + 1) * g_cxChar, 2 * g_cyChar, hwnd, 3 + iCount, lParam);
		ixTemp += g_pButtonsBottoms[iCount].getRect().right + 2 * g_cxChar;
	}
}

LRESULT CALLBACK wndProcCamera(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
		//MoveWindow(hwndFrame, 0, 50, float(g_rectFrame[0].right) * fxRateSize, float(g_rectFrame[0].bottom) *fyRateSize, FALSE);

	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}
HWND CreateAWindowSetting(HWND hwnd){
	RECT rectTemp = {0, g_rectWindow.bottom * 2 / 3 - 4 * g_cyChar, g_rectWindow.right, g_rectWindow.bottom / 3};
	InvalidateRect(hwnd, &rectTemp, TRUE);
	float fDistance = 5 * g_cxChar / (++ g_iAmountWindowSetting);
	g_hwSetting[g_iAmountWindowSetting].CreateANewFrame(hwnd, L"Class", NULL, g_hInst, wndProcCamera, rectTemp.left + fDistance, rectTemp.top, (rectTemp.right - 5 * g_cxChar) / g_iAmountWindowSetting, rectTemp.bottom);
	if (g_iAmountWindowSetting > 1)
		for (int iCount = 0; iCount < g_iAmountWindowSetting - 1; iCount++){
			MoveWindow(g_hwSetting[iCount])
		}
}

