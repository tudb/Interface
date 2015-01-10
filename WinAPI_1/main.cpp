#include "ClassRegister.h"
#include "hwWindow.h"
#include "resource.h"
#include "Buttons.h"
#include <Windows.h>

/* void PaintTheBlock(HWND hCtrl, int iColor[], int iFigure);
void PaintWindow(HWND hwnd, int iColor[], int iFigure);
int hi, lo, hiWord, loWord;
HINSTANCE hInst;
HWND hwndEdit, hwndPaint, hEdit, hPaint;
HWND hButtons[9];
Buttons *pButtons = new Buttons[9];
int pColor[] = { 34, 45, 56 };
static RECT rect;
static TCHAR szTop[] = TEXT("message wParam lParam"),
szUnd[] = TEXT("_______ ______ ______"),
szFormat[] = TEXT("%-16s%04X-%04X %04X-%04X"),
szBuffer[50];
static int cxChar, cyChar;
HDC hdc;
PAINTSTRUCT ps;

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EditProc(HWND, UINT, WPARAM, LPARAM);

void CreateButtons(HWND, LPARAM);

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName   = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName	= TEXT("MENU NAME");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, MAKEINTRESOURCE(IDR_MENU1));
	hwWindow hWindow;
	winClass.registerClass();
	hwnd = hWindow.creatWindow(hInstance, lpszClassName, lpszMenuName);
	hWindow.showWindow();
	hwWindow hChild;
	hChild.creatWindow(hInstance, TEXT("CHILD CLASS"), TEXT("MENU CHILD"), hwnd);
	hChild.showWindow();
	while (GetMessage(&msg, NULL, 0, 0)){
		if ((hEdit == 0) || !IsDialogMessage(hEdit, &msg)){
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_CREATE:
		hInst = ((LPCREATESTRUCT)lParam)->hInstance;
		CreateButtons(hwnd, lParam);
			break;
	case WM_SIZE:
		rect.left = 24 * cxChar;
		rect.top = 2 * cyChar;
		rect.right = LOWORD(lParam);
		rect.bottom = HIWORD(lParam);
		return 0;
	case WM_PAINT:
		InvalidateRect(hwnd, &rect, TRUE);
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		SetBkMode(hdc, TRANSPARENT);
		TextOut(hdc, 24 * cxChar, cyChar, szTop, lstrlen(szTop)); TextOut(hdc, 24 * cxChar, cyChar, szUnd, lstrlen(szUnd));
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DRAWITEM:
	case WM_COMMAND:
		hiWord = HIWORD(wParam);
		loWord = LOWORD(wParam);
		ScrollWindow(hwnd, 0, -cyChar, &rect, &rect);
		hdc = GetDC(hwnd);
		SelectObject(hdc, GetStockObject(SYSTEM_FIXED_FONT));
		TextOut(hdc, 24 * cxChar, cyChar*(rect.bottom / cyChar - 1), szBuffer, wsprintf(szBuffer, szFormat, msg == WM_DRAWITEM ? TEXT("WM_DRAWITEM") : TEXT("WM_COMMAND"), HIWORD(wParam), LOWORD(wParam), HIWORD(lParam), LOWORD(lParam)));
		ReleaseDC(hwnd, hdc);
		ValidateRect(hwnd, &rect);
		switch (loWord){
		case ID_INFORMATION_INFOR:
			break;
		case ID_ABOUT_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutProc);
			break;
		case ID_FILE_EDIT:
			hEdit = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, EditProc);
			ShowWindow(hEdit, SW_SHOWNORMAL);
		case ID_INFORMATION_CGW:
			SetWindowText(hwnd, L"CHANGE");
		case ID_TEXT_EDIT:
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		return 0;

/*	case WM_COMMAND:
		hiWord = HIWORD(wParam);
		loWord = LOWORD(wParam);
		switch (loWord){
		case ID_ABOUT_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG1), hwnd, AboutProc);
			break;
		case ID_FILE_EDIT:
			hEdit = CreateDialog(hInst, MAKEINTRESOURCE(IDD_DIALOG2), hwnd, EditProc);
			ShowWindow(hEdit, SW_SHOWNORMAL);
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		HDC hdc;
		hdc = GetDC(hwnd);
		BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
		*/
	/*
	case WM_DESTROY:
		PostQuitMessage(WM_QUIT);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK AboutProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	switch (msg){
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL){
			EndDialog(hwnd, 0);
			return (INT_PTR)TRUE;
		}
	}
	return (INT_PTR)FALSE;
}

INT_PTR CALLBACK EditProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	lo = LOWORD(wParam);
	switch (msg){
	case WM_COMMAND:
		switch (lo){
		case IDOK:
		case IDCANCEL:
			DestroyWindow(hwnd);
			return (INT_PTR)TRUE;
		case ID_DIALOG2_RADIO1:
			SendMessage(hwnd, BM_SETCHECK, 1, 0);
			PaintTheBlock(GetParent(hwnd), pColor, 0);
			return (INT_PTR)TRUE;
		case ID_DIALOG2_PUSH:
			PaintTheBlock(GetParent(hwnd), pColor, 1);
			break;
		}
	case WM_DESTROY:
		DestroyWindow(hwnd);
		return (INT_PTR)TRUE;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return (INT_PTR)FALSE;
}

void PaintTheBlock(HWND hCtrl, int iColor[], int iFigure)
{
	InvalidateRect(hCtrl, NULL, TRUE);
	UpdateWindow(hCtrl);
	PaintWindow(hCtrl, iColor, iFigure);
}

void PaintWindow(HWND hwnd, int iColor[], int iFigure)
{
	HBRUSH hBrush;
	HDC hdc;
	RECT rect;
	hdc = GetDC(hwnd);
	GetClientRect(hwnd, &rect);
	hBrush = CreateSolidBrush(RGB(iColor[0], iColor[1], iColor[2]));
	hBrush = (HBRUSH)SelectObject(hdc, hBrush);
	if (iFigure == 0)
		Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
	else
		Ellipse(hdc, rect.left, rect.top, rect.right, rect.bottom);
	DeleteObject(SelectObject(hdc, hBrush));
	ReleaseDC(hwnd, hdc);
}


void CreateButtons(HWND hwnd, LPARAM lParam){
	cxChar = LOWORD(GetDialogBaseUnits());
	cyChar = HIWORD(GetDialogBaseUnits());
	pButtons[0].import(BS_PUSHBUTTON, TEXT("PUSHBUTTON"));
	pButtons[1].import(BS_DEFPUSHBUTTON, TEXT("DEFPUSHBUTTON"));
	pButtons[2].import(BS_CHECKBOX, TEXT("CHECKBOX"));
	pButtons[3].import(BS_AUTOCHECKBOX, TEXT("AUTOCHECKBOX"));
	pButtons[4].import(BS_RADIOBUTTON, TEXT("RADIOBUTTON"));
	pButtons[5].import(BS_3STATE, TEXT("3STATE"));
	pButtons[6].import(BS_AUTO3STATE, TEXT("AUTO3STATE"));
	pButtons[7].import(BS_GROUPBOX, TEXT("GROUPBOX"));
	pButtons[8].import(BS_AUTORADIOBUTTON, TEXT("AUTORADIO"));
	for (int nCount = 0; nCount < 9; nCount++){
		hButtons[nCount] = pButtons[nCount].createButton(L"BUTTON", cxChar, cyChar*(1 + 2 * nCount), 20 * cxChar, 7 * cyChar / 4, hwnd, nCount, lParam);
	}
}
*/