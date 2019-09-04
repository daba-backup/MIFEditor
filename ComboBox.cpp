#include"ComboBox.h"

daxie::control::ComboBoxBase::ComboBoxBase(int x, int y, int width, int height, HWND hwnd_parent,DWORD style)
	:daxie::control::Control(TEXT(""), TEXT("COMBOBOX"), x, y, width, height, hwnd_parent, NULL, style, 0) {

}
daxie::control::ComboBoxBase::~ComboBoxBase() {

}

void daxie::control::ComboBoxBase::AddItem(const daxie::tstring& item) {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, CB_ADDSTRING, 0, reinterpret_cast<LPARAM>(item.c_str()));
}
void daxie::control::ComboBoxBase::RemoveItem(int index) {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, CB_DELETESTRING, index, 0);
}
void daxie::control::ComboBoxBase::SetCurrentSelection(int index) {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, CB_SETCURSEL, index, 0);
}

int daxie::control::ComboBoxBase::GetCurrentSelection() {
	HWND hcontrol = this->GetControlHandle();
	LRESULT ret = SendMessage(hcontrol, CB_GETCURSEL, 0, 0);

	return static_cast<int>(ret);
}
int daxie::control::ComboBoxBase::GetItemNum() {
	HWND hcontrol = this->GetControlHandle();
	LRESULT ret = SendMessage(hcontrol, CB_GETCOUNT, 0, 0);

	return static_cast<int>(ret);
}

daxie::control::SimpleComboBox::SimpleComboBox(int x, int y, int width, int height, HWND hwnd_parent)
	:daxie::control::ComboBoxBase(x, y, width, height, hwnd_parent, WS_VISIBLE | WS_CHILD | CBS_SIMPLE) {

}
daxie::control::SimpleComboBox::~SimpleComboBox() {

}

daxie::control::DropdownList::DropdownList(int x, int y, int width, int height, HWND hwnd_parent)
	:daxie::control::ComboBoxBase(x, y, width, height, hwnd_parent, WS_VISIBLE | WS_CHILD | CBS_DROPDOWNLIST) {
	
}
daxie::control::DropdownList::~DropdownList() {

}

void daxie::control::DropdownList::ShowDropdown() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, CB_SHOWDROPDOWN, TRUE, 0);
}
void daxie::control::DropdownList::HideDropdown() {
	HWND hcontrol = this->GetControlHandle();
	SendMessage(hcontrol, CB_SHOWDROPDOWN, FALSE, 0);
}
BOOL daxie::control::DropdownList::IsDropped() {
	BOOL ret;

	HWND hcontrol = this->GetControlHandle();
	if (SendMessage(hcontrol, CB_GETDROPPEDSTATE, 0, 0) == TRUE)ret = TRUE;
	else ret = FALSE;

	return ret;
}