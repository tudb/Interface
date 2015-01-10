#include "Buttons.h"


Buttons::Buttons(){
	iStyle = 0;
	szText = NULL;
}

void Buttons::import(int iStyle, TCHAR *szText){
	(*this).iStyle = iStyle;
	(*this).szText = szText;
}


Buttons::~Buttons(){
}

HWND Buttons::createButton(LPCTSTR lpszName, int cxChar1, int cyChar1,int cxChar2, int cyChar2, HWND hwnd, int i, LPARAM lParam){
	HWND hTemp;
	hTemp = CreateWindow(lpszName, (*this).szText, WS_CHILD | WS_VISIBLE | (*this).iStyle, cxChar1, cyChar1, cxChar2, cyChar2, hwnd, (HMENU)i, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
	if (!hTemp) {
		MessageBox(hwnd, L"ERROR CREATE BUTTON", L"NONE CAPTION", 0);
		return NULL;
	}
	return hTemp;
}
