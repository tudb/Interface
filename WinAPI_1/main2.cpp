#include "Buttons.h"
#include "hwWindow.h"
#include "ClassRegister.h"
#include "resource.h" 
#include <StrSafe.h>
#include <Windows.h>

/* LRESULT CALLBACK WinProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
INT_PTR CALLBACK AboutProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK EditProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message,
	WPARAM wParam, LPARAM lParam);

void CreateListBox(HWND);
void FillListBox(HWND);
void CreateComboBox(HWND);

static HWND hwndProc, hwndButton, hwndComboBox;
static HWND hwndEdit, hwndListBox, hwndText, hwndTextCombo, hwndButtonCombo;
HINSTANCE hInst;
LPCTSTR szAppName = L"Notepad Fake";

static int iStart, iEnd, cxChar, cyChar, iIndex, iLength;
int iCount;
char* pVarName;
TCHAR szBuffer[30];
static TCHAR *list[] = { TEXT("Word 2003 Document"), TEXT("Text File"), TEXT("Rip Document"), TEXT("Pdf"), TEXT("Word 2007 Document"), TEXT("File Print"), TEXT("None") };


typedef struct
{
	TCHAR achName[MAX_PATH];
	TCHAR achPosition[12];
	int nGamesPlayed;
	int nGoalsScored;
} Player;

Player Roster[] =
{
	{ TEXT("Haas, Jonathan"), TEXT("Midfield"), 18, 4 },
	{ TEXT("Pai, Jyothi"), TEXT("Forward"), 36, 12 },
	{ TEXT("Hanif, Kerim"), TEXT("Back"), 26, 0 },
	{ TEXT("Anderberg, Michael"), TEXT("Back"), 24, 2 },
	{ TEXT("Jelitto, Jacek"), TEXT("Midfield"), 26, 3 },
	{ TEXT("Raposo, Rui"), TEXT("Back"), 24, 3 },
	{ TEXT("Joseph, Brad"), TEXT("Forward"), 13, 3 },
	{ TEXT("Bouchard, Thomas"), TEXT("Forward"), 28, 5 },
	{ TEXT("Salmre, Ivo "), TEXT("Midfield"), 27, 7 },
	{ TEXT("Camp, David"), TEXT("Midfield"), 22, 3 },
	{ TEXT("Kohl, Franz"), TEXT("Goalkeeper"), 17, 0 },
};
void FillListBox(HWND hwndFill){
	for (int iCount = 0; iCount < 7; iCount++){
		SendMessage(hwndFill, LB_ADDSTRING, 0, (LPARAM)list[iCount]);
	}
}

void FillComboBox(HWND hwndFillCombo){
	for (int iCount = 0; iCount < 11; iCount++){
		SendMessage(hwndFillCombo, CB_ADDSTRING, 0, (LPARAM)Roster[iCount].achName);
	}
}



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
		CreateListBox(hwnd);
		CreateComboBox(hwnd);
		return 0;
	case WM_SETFOCUS:
		SetFocus(hwndEdit);
		SetFocus(hwndComboBox);
		return 0;
	case WM_SIZE:
		MoveWindow(hwndEdit, 0, 0, LOWORD(lParam), HIWORD(lParam), TRUE);
		return 0;
	case WM_COMMAND:
		if (LOWORD(wParam) == ID_EDIT)
			if (HIWORD(wParam) == EN_ERRSPACE || HIWORD(wParam) == EN_MAXTEXT)
				MessageBox(hwnd, TEXT("Edit control out of space."), szAppName, MB_OK | MB_ICONSTOP);
		switch (LOWORD(wParam)){
		case ID_EDIT_REPLACE:
			SendMessage(hwndEdit, EM_REPLACESEL, 0, (LPARAM)(L"Replace Text"));
			break;
		case ID_EDIT_COPY:
			hwndEdit = CreateWindow(TEXT("edit"), NULL, WS_BORDER | WS_HSCROLL | WS_VSCROLL | WS_CHILD | WS_VISIBLE | WS_HSCROLL | WS_VSCROLL | WS_BORDER | ES_LEFT | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL, 0, 0, 0, 0, hwnd, (HMENU)ID_EDIT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
			//iCount = SendMessage(hwndEdit)
			SendMessage(hwndEdit, WM_COPY, iStart, iEnd);
			break;
		case ID_EDIT_CUT: 
			SendMessage(hwndEdit, WM_CUT, iStart, iEnd);
			break;
		case ID_EDIT_PASTE:
			SendMessage(hwndEdit, WM_PASTE, iStart, iEnd);
			break;
		case ID_EDIT_CLEAR:
			SendMessage(hwndEdit, WM_CLEAR, 0, 0);
		case ID_FILE_SAVE:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG3), hwnd, ListBoxExampleProc);
			break;
		case ID_LIST:
			iIndex = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
			iLength = SendMessage(hwndListBox, LB_GETTEXTLEN, iIndex, 0) + 1;
			pVarName = (char*)calloc(iLength, sizeof(TCHAR));
			SendMessage(hwndListBox, LB_GETTEXT, iIndex, (LPARAM)pVarName);
			HDC hdc;
			hdc = GetDC(hwndText);
			SetWindowText(hwndText, (LPCWSTR)pVarName);
			free(pVarName);
			break;
	case IDC_MAIN_BUTTON:
		int iIndext;
		iIndext = SendMessage(hwndListBox, LB_GETCURSEL, 0, 0);
		MessageBox(hwndListBox, list[iIndext], L"", 0);
		break;
	case ID_COMBO:
		iIndex = SendMessage(hwndComboBox, CB_GETCURSEL, 0, 0);
		int i = (int)SendMessage(hwndComboBox, CB_GETITEMDATA, iIndex, 0);
		TCHAR buff[MAX_PATH];
		StringCbPrintf(buff, ARRAYSIZE(buff),
			TEXT("Name: %s\nPosition: %s\nGames played: %d\nGoals: %d"), Roster[iIndex].achName,
			Roster[iIndex].achPosition, Roster[iIndex].nGamesPlayed,
			Roster[iIndex].nGoalsScored);
		SetWindowText(hwndTextCombo, buff);
		break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

void CreateListBox(HWND hwndProc){
	cxChar		= LOWORD(GetDialogBaseUnits());
	cyChar	    = HIWORD(GetDialogBaseUnits());
	hwndListBox = CreateWindow(TEXT("listbox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_STANDARD, cxChar, cyChar * 3, cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 5, hwndProc, (HMENU)ID_LIST, (HINSTANCE)GetWindowLong(hwndProc, GWL_HINSTANCE), NULL);
	hwndText	= CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, cxChar, cyChar, GetSystemMetrics(SM_CXSCREEN), cyChar, hwndProc, (HMENU)ID_TEXT, (HINSTANCE)GetWindowLong(hwndProc, GWL_HINSTANCE), NULL);
	hwndButton  = CreateWindowEx(NULL, L"BUTTON", L"OK", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON , 200, 50, 100, 24, hwndProc, (HMENU)IDC_MAIN_BUTTON, GetModuleHandle(NULL), NULL);
	FillListBox(hwndListBox);
}

void CreateComboBox(HWND hwndProc){
	cxChar = LOWORD(GetDialogBaseUnits());
	cyChar = HIWORD(GetDialogBaseUnits());
	hwndComboBox = CreateWindow(TEXT("combobox"), NULL, WS_CHILD | WS_VISIBLE | LBS_NOTIFY | LBS_STANDARD, cxChar + 400, cyChar * 3, cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 5, hwndProc, (HMENU)ID_COMBO, (HINSTANCE)GetWindowLong(hwndProc, GWL_HINSTANCE), NULL);
	hwndTextCombo = CreateWindow(TEXT("static"), NULL, WS_CHILD | WS_VISIBLE | SS_LEFT, cxChar + 400, cyChar * 6, cxChar * 16 + GetSystemMetrics(SM_CXVSCROLL), cyChar * 10, hwndProc, (HMENU)ID_TEXT_COMBO, (HINSTANCE)GetWindowLong(hwndProc, GWL_HINSTANCE), NULL);
	hwndButtonCombo = CreateWindowEx(NULL, L"COMBO", L"Information", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON, 250, 50, 100, 24, hwndProc, (HMENU)IDC_BUTTON_COMBO, GetModuleHandle(NULL), NULL);
	FillComboBox(hwndComboBox);
}

INT_PTR CALLBACK ListBoxExampleProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// Add items to list. 
		CreateListBox(hDlg);
		for (int i = 0; i < ARRAYSIZE(Roster); i++)
		{
			int pos = (int)SendMessage(hwndListBox, LB_ADDSTRING, 0,
				(LPARAM)Roster[i].achName);
			// Set the array index of the player as item data.
			// This enables us to retrieve the item from the array
			// even after the items are sorted by the list box.
			SendMessage(hwndListBox, LB_SETITEMDATA, pos, (LPARAM)i);
		}
		// Set input focus to the list box.
		SetFocus(hwndListBox);
		return TRUE;
	}

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
		case IDCANCEL:
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		case ID_LISTBOX_EXAMPLE:
		{
			switch (HIWORD(wParam))
			{
				case LBN_SELCHANGE:
				{
					HWND hwndList = GetDlgItem(hDlg, ID_LISTBOX_EXAMPLE);

					// Get selected index.
					int lbItem = (int)SendMessage(hwndList, LB_GETCURSEL, 0, 0);

					// Get item data.
					int i = (int)SendMessage(hwndList, LB_GETITEMDATA, lbItem, 0);

					// Do something with the data from Roster[i]
					TCHAR buff[MAX_PATH];
					StringCbPrintf(buff, ARRAYSIZE(buff),
						TEXT("Position: %s\nGames played: %d\nGoals: %d"),
						Roster[i].achPosition, Roster[i].nGamesPlayed,
						Roster[i].nGoalsScored);

					SetDlgItemText(hwndText, GetWindowLong(hwndText, GWL_ID), buff);
					return TRUE;
				}
			}
		}
		return TRUE;
		}
	}
	return FALSE;
}
*/