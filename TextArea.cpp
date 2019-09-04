#include"TextArea.h"

daxie::control::TextArea::TextArea(int x, int y, int width, int height, HWND hwnd_parent)
	:daxie::control::Control(TEXT(""), TEXT("EDIT"), x, y, width, height, hwnd_parent, NULL,
		WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL | ES_MULTILINE, 0) {

}
daxie::control::TextArea::~TextArea() {

}