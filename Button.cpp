#include"Button.h"

daxie::control::Button::Button(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent) :
	daxie::control::Control(text, TEXT("BUTTON"), x, y, width, height, hwnd_parent, 
		NULL, WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON, 0) {

}
daxie::control::Button::~Button() {

}