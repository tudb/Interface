#pragma once
#include <Windows.h>
class ClassRegister{
protected:
	WNDCLASSEX winClass;
public:
	ClassRegister(HINSTANCE hInstance, LPCTSTR ClsName, WNDPROC wndProc, LPCTSTR MenuName);
	~ClassRegister();
	void registerClass();
};

