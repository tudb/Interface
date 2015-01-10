#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <StrSafe.h>
#include <stdio.h>
#include <Windows.h>
#include <Commctrl.h>

#pragma comment(lib, "comctl32.lib")

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
VOID CreateText(HWND hwnd, LPWSTR lpString, int x, int y, int iMenu, HINSTANCE hInstance);
HFONT FAR PASCAL MyCreateFont();
HWND CreateSimpleToolbar(HWND hWndParent);

HWND g_hwnd;
HINSTANCE hInst;
HWND hwndStaticText;
HWND hToolBar;

static HIMAGELIST g_hImageList;
int xChar, yChar;
static HFONT hFontNew;
HGDIOBJ hdgiFontOld;
LPWSTR lpszString = TEXT("UseFont.exe' (Win32) : Loaded Cannot find or open the PDB file.");

INT WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow){
	HWND hwnd;
	MSG msg;
	LPCTSTR lpszClassName = TEXT("CLASS NAME");
	LPCTSTR lpszMenuName = TEXT("Use Font");
	ClassRegister winClass(hInstance, lpszClassName, WinProc, MAKEINTRESOURCE(IDR_MENU1));
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
	g_hwnd = hwnd;
	return 0;
}

LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam){
	
	HDC hdc;
	RECT rect;
	switch (msg){
	case WM_CREATE:
		hToolBar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL, WS_CHILD | WS_VISIBLE, 0, 0, 0, 0,
			hwnd, (HMENU)IDC_MAIN_TOOL, GetModuleHandle(NULL), NULL);
		CreateSimpleToolbar(hwnd);
		return 0;
	case WM_COMMAND:
		switch (LOWORD(wParam)){
		case ID_MENU_CHANGEFONT:
			RECT rect;
			GetClientRect(hwnd, &rect);
			InvalidateRect(hwnd, &rect, TRUE);
			break;
		case ID_MENU_EXIT:
			break;
		}
		break;
	case WM_PAINT:
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

VOID CreateText(HWND hwnd, LPWSTR lpString, int x, int y, int iMenu, HINSTANCE hInstance){
	xChar = LOWORD(GetDialogBaseUnits());
	yChar = HIWORD(GetDialogBaseUnits());
	hwndStaticText = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | WS_HSCROLL, x, y, 100 * xChar, 100* yChar, hwnd, (HMENU)iMenu, hInstance, NULL);
}

HFONT FAR PASCAL MyCreateFont(void)
{
	CHOOSEFONT cf;
	LOGFONT lf;
	HFONT hfont; 
	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.hwndOwner = (HWND)NULL;
	cf.hDC = (HDC)NULL;
	cf.lpLogFont = &lf;
	cf.iPointSize = 0;
	cf.Flags = CF_SCREENFONTS;
	cf.rgbColors = RGB(0, 0, 0);
	cf.lCustData = 0L;
	cf.lpfnHook = (LPCFHOOKPROC)NULL;
	cf.lpTemplateName = (LPCWSTR)NULL;
	cf.hInstance = (HINSTANCE)NULL;
	cf.lpszStyle = (LPWSTR)NULL;
	cf.nFontType = SCREEN_FONTTYPE;
	cf.nSizeMin = 0;
	cf.nSizeMax = 0;
	if (!ChooseFont(&cf)) MessageBox(g_hwnd, L"NO ERROR", L"", 0);
	hfont = CreateFontIndirect(cf.lpLogFont);
	return (hfont);
}


HWND CreateSimpleToolbar(HWND hWndParent)
{
	// Declare and initialize local constants.
	const int ImageListID = 0;
	const int numButtons = 3;
	const int bitmapSize = 16;

	const DWORD buttonStyles = BTNS_AUTOSIZE;

	// Create the toolbar.
	HWND hWndToolbar = CreateWindowEx(0, TOOLBARCLASSNAME, NULL,
		WS_CHILD | TBSTYLE_WRAPABLE, 0, 0, 0, 0,
		hWndParent, NULL, hInst, NULL);

	if (hWndToolbar == NULL)
		return NULL;

	// Create the image list.
	g_hImageList = ImageList_Create(bitmapSize, bitmapSize,   // Dimensions of individual bitmaps.
		ILC_COLOR16 | ILC_MASK,   // Ensures transparent background.
		numButtons, 0);

	// Set the image list.
	SendMessage(hWndToolbar, TB_SETIMAGELIST,
		(WPARAM)ImageListID,
		(LPARAM)g_hImageList);

	// Load the button images.
	SendMessage(hWndToolbar, TB_LOADIMAGES,
		(WPARAM)IDB_STD_SMALL_COLOR,
		(LPARAM)HINST_COMMCTRL);

	// Initialize button info.
	// IDM_NEW, IDM_OPEN, and IDM_SAVE are application-defined command constants.

	TBBUTTON tbButtons[numButtons] =
	{
		{ MAKELONG(STD_FILENEW, ImageListID), ID_FILE_NEW, TBSTATE_ENABLED, buttonStyles, { 0 }, 0, (INT_PTR)L"New" },
		{ MAKELONG(STD_FILEOPEN, ImageListID), ID_FILE_OPEN, TBSTATE_ENABLED, buttonStyles, { 0 }, 0, (INT_PTR)L"Open" },
		{ MAKELONG(STD_FILESAVE, ImageListID), ID_FILE_SAVEAS, 0, buttonStyles, { 0 }, 0, (INT_PTR)L"Save" }
	};

	// Add buttons.
	SendMessage(hWndToolbar, TB_BUTTONSTRUCTSIZE, (WPARAM)sizeof(TBBUTTON), 0);
	SendMessage(hWndToolbar, TB_ADDBUTTONS, (WPARAM)numButtons, (LPARAM)&tbButtons);

	// Resize the toolbar, and then show it.
	SendMessage(hWndToolbar, TB_AUTOSIZE, 0, 0);
	ShowWindow(hWndToolbar, TRUE);

	return hWndToolbar;
}