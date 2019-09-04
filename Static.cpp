#include"Static.h"

daxie::control::Static::Static(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent):
	daxie::control::Control(text, TEXT("STATIC"), x, y, width, height, hwnd_parent, 
		NULL, WS_VISIBLE | WS_CHILD | SS_CENTER, 0) {

}
daxie::control::Static::~Static() {

}