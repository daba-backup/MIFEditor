#include"RadioButton.h"

daxie::control::RadioButtonBase::RadioButtonBase(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent, DWORD style) :
	daxie::control::Control(text, TEXT("BUTTON"), x, y, width, height, hwnd_parent, NULL, style, 0) {

}
daxie::control::RadioButtonBase::~RadioButtonBase() {

}

BOOL daxie::control::RadioButtonBase::IsChecked() {
	HWND hcontrol = this->GetControlHandle();
	LRESULT ret = SendMessage(hcontrol, BM_GETCHECK, 0, 0);

	if (ret == BST_CHECKED)return TRUE;
	else return FALSE;
}

void daxie::control::RadioButtonBase::Check() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, BM_SETCHECK, BST_CHECKED, 0);
}
void daxie::control::RadioButtonBase::Uncheck() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, BM_SETCHECK, BST_UNCHECKED, 0);
}

daxie::control::HeadRadioButton::HeadRadioButton(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent)
	:daxie::control::RadioButtonBase(text, x, y, width, height, hwnd_parent, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON | WS_GROUP) {

}
daxie::control::HeadRadioButton::~HeadRadioButton() {

}

daxie::control::RadioButton::RadioButton(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent)
	:daxie::control::RadioButtonBase(text, x, y, width, height, hwnd_parent, WS_VISIBLE | WS_CHILD | BS_AUTORADIOBUTTON) {

}
daxie::control::RadioButton::~RadioButton() {

}