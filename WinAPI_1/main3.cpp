#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <StrSafe.h>
#include <Windows.h>

/*
LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

static int a = 0;

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

	static COLORREF crPrim[3] = { RGB(255, 0, 0), RGB(0, 255, 0),
		RGB(0, 0, 255) };
	static HBRUSH hBrush[3], hBrushStatic;
	static HWND hwndScroll[3], hwndLabel[3], hwndValue[3], hwndRect;
	static int color[3], cyChar;
	static RECT rcColor;
	static TCHAR *szColorLabel[] = { TEXT("Red"),
		TEXT("Green"), TEXT("Blue") };
	HINSTANCE hInstance;
	int i, cxClient, cyClient;
	TCHAR szBuffer[10];
	switch (msg)
	{
	case WM_CREATE:
		hInstance = (HINSTANCE)GetWindowLong(hwnd, GWL_HINSTANCE);
		hwndRect = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | SS_WHITERECT, 0, 0, 0, 0, hwnd, (HMENU)9, hInstance, NULL);
		for (i = 0; i < 3; i++)
		{
			hwndScroll[i] = CreateWindow(TEXT("scrollbar"), NULL, WS_CHILD | WS_VISIBLE | WS_TABSTOP | SBS_VERT, 0, 0, 0, 0, hwnd, (HMENU)i, hInstance, NULL);
			SetScrollRange(hwndScroll[i], SB_CTL, 0, 255, FALSE);
			SetScrollPos(hwndScroll[i], SB_CTL, 0, FALSE);
			hwndLabel[i] = CreateWindow(TEXT("static"), szColorLabel[i], WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 0, 0, hwnd, (HMENU)(i + 3), hInstance, NULL);
			hwndValue[i] = CreateWindow(TEXT("static"), TEXT("0"), WS_CHILD | WS_VISIBLE | SS_CENTER, 0, 0, 0, 0, hwnd, (HMENU)(i + 6), hInstance, NULL);
			OldScroll[i] = (WNDPROC)SetWindowLong(hwndScroll[i], GWL_WNDPROC, (LONG)ScrollProc);
			hBrush[i] = CreateSolidBrush(crPrim[i]);
		}
		hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
		cyChar = HIWORD(GetDialogBaseUnits());
		return 0;
	case WM_SIZE:
		cxClient = LOWORD(lParam);
		cyClient = HIWORD(lParam);
		SetRect(&rcColor, 0, 0, cxClient / 1.5, cyClient);
		MoveWindow(hwndRect, cxClient / 1.5, 0, cxClient / 2, cyClient, TRUE);
		for (i = 0; i < 3; i++)
		{
			MoveWindow(hwndScroll[i], ((int)(1.2 * i + 1) * cxClient) / 13 + (int)cxClient / 1.5, 2 * cyChar, cxClient / 17, cyClient - 4 * cyChar, TRUE);
			MoveWindow(hwndLabel[i], (2.3 * i + 1) * cxClient / 28 + cxClient / 1.5, cyChar / 2, cxClient / 8, cyChar, TRUE);
			MoveWindow(hwndValue[i], (2.3 * i + 1) * cxClient / 28 + cxClient / 1.5, cyClient - 3 * cyChar / 2, cxClient / 8, cyChar, TRUE);
		}
		SetFocus(hwnd);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hwndScroll[idFocus]);
		return 0;
	case WM_VSCROLL:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		switch (LOWORD(wParam))
		{
		case SB_PAGEDOWN:
			color[i] += 15;
		case SB_LINEDOWN:
			color[i] = min(255, color[i] + 1);
			break;
		case SB_PAGEUP:
			color[i] -= 15;
		case SB_LINEUP:
			color[i] = max(0, color[i] - 1);
			break;
		case SB_TOP:
			color[i] = 0;
			break;
		case SB_BOTTOM:
			color[i] = 255;
			break;
		case SB_THUMBPOSITION:
		case SB_THUMBTRACK:
			color[i] = HIWORD(wParam);
			break;
		default:
			break;
		}
		SetScrollPos(hwndScroll[i], SB_CTL, color[i], TRUE);
		wsprintf(szBuffer, TEXT("%i"), color[i]);
		SetWindowText(hwndValue[i], szBuffer);
		DeleteObject((HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)CreateSolidBrush(RGB(color[0], color[1], color[2]))));
		InvalidateRect(hwnd, &rcColor, TRUE);
		return 0;
	case WM_CTLCOLORSCROLLBAR:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		return (LRESULT)hBrush[i];
	case WM_CTLCOLORSTATIC:
		i = GetWindowLong((HWND)lParam, GWL_ID);
		if (i >= 3 && i <= 8)
		{
			SetTextColor((HDC)wParam, crPrim[i % 3]);
			SetBkColor((HDC)wParam, GetSysColor(COLOR_BTNHIGHLIGHT));
			return (LRESULT)hBrushStatic;
		}
		break;

case WM_SYSCOLORCHANGE:
	DeleteObject(hBrushStatic);
	hBrushStatic = CreateSolidBrush(GetSysColor(COLOR_BTNHIGHLIGHT));
	return 0;
case WM_DESTROY:
	DeleteObject((HBRUSH)SetClassLong(hwnd, GCL_HBRBACKGROUND, (LONG)GetStockObject(WHITE_BRUSH)));
	for (i = 0; i < 3; i++)
		DeleteObject(hBrush[i]);
	DeleteObject(hBrushStatic);
	PostQuitMessage(0);
	return 0;
}
return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK ScrollProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int id = GetWindowLong(hwnd, GWL_ID);
	switch (message)
	{
	case WM_KEYDOWN:
		if (wParam == VK_TAB)
			SetFocus(GetDlgItem(GetParent(hwnd), (id + (GetKeyState(VK_SHIFT) < 0 ? 2 : 1)) % 3));
		break;
	case WM_SETFOCUS:
		idFocus = id;
		break;
	}
	return CallWindowProc(OldScroll[id], hwnd, message, wParam, lParam);
}


*/
