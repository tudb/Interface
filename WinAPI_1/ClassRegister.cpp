#include "ClassRegister.h"


ClassRegister::ClassRegister(HINSTANCE hInstance, LPCTSTR lpszClassName, WNDPROC wndProc, LPCTSTR lpszMenuName){
	winClass.cbSize = sizeof(WNDCLASSEX);
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hbrBackground = (HBRUSH)(GetStockObject(WHITE_BRUSH));
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	winClass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	winClass.style = CS_HREDRAW | CS_VREDRAW;
	winClass.hInstance = hInstance;
	winClass.lpszClassName = lpszClassName;
	winClass.lpszMenuName = lpszMenuName;
	winClass.lpfnWndProc = wndProc;
}


ClassRegister::~ClassRegister(){
}

void ClassRegister::registerClass(){
	RegisterClassEx(&winClass);
}
