#include"WCC.h"
#include"Window.h"
#include<CommCtrl.h>

#pragma comment(lib,"comctl32")

BOOL daxie::system::WCC::Initialize(){
	SetProcessDPIAware();

	//Intialize common controls.
	INITCOMMONCONTROLSEX iccs;

	iccs.dwSize = sizeof(INITCOMMONCONTROLSEX);
	iccs.dwICC = ICC_WIN95_CLASSES;

	if (InitCommonControlsEx(&iccs) == FALSE)return FALSE;

	//Register a window class.
	if (daxie::window::Window::DHRegisterWindowClass() == FALSE)return FALSE;
	
	return TRUE;
}
void daxie::system::WCC::MsgLoop() {
	MSG msg;

	while (GetMessage(&msg, NULL, 0, 0) > 0) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}
