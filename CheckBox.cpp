#include"CheckBox.h"

daxie::control::CheckBox::CheckBox(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent) :
	daxie::control::Control(text, TEXT("BUTTON"), x, y, width, height, hwnd_parent,
		NULL, WS_VISIBLE | WS_CHILD | BS_AUTOCHECKBOX, 0) {

}
daxie::control::CheckBox::~CheckBox() {

}

BOOL daxie::control::CheckBox::IsChecked() {
	HWND hcontrol = this->GetControlHandle();
	LRESULT ret=SendMessage(hcontrol, BM_GETCHECK, 0, 0);

	if (ret == BST_CHECKED)return TRUE;
	else return FALSE;
}

void daxie::control::CheckBox::Check() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, BM_SETCHECK, BST_CHECKED, 0);
}
void daxie::control::CheckBox::Uncheck() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, BM_SETCHECK, BST_UNCHECKED, 0);
}
