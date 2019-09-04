#include"ListView.h"
#include"TStringFunctions.h"
#include<CommCtrl.h>

daxie::control::ListView::ListView(int x, int y, int width, int height, HWND hwnd_parent):
	daxie::control::Control(TEXT(""), WC_LISTVIEW, x, y, width, height, hwnd_parent, 
		NULL, WS_CHILD | WS_VISIBLE | LVS_REPORT, 0) {

}
daxie::control::ListView::~ListView() {

}

void daxie::control::ListView::SetExtendedStyle(DWORD dw_style) {
	HWND hcontrol = this->GetControlHandle();
	ListView_SetExtendedListViewStyle(hcontrol, dw_style);
}

void daxie::control::ListView::AddColumn(int column, int width, const daxie::tstring& text) {
	LVCOLUMN lv_col;

	lv_col.mask = LVCF_FMT | LVCF_TEXT | LVCF_WIDTH;
	lv_col.fmt = LVCFMT_LEFT;
	lv_col.cx = width;
	lv_col.pszText = const_cast<LPTSTR>(text.c_str());

	ListView_InsertColumn(this->GetControlHandle(), column, &lv_col);
}
void daxie::control::ListView::AddItem(int row, int column, const daxie::tstring& value) {
	LVITEM lv_item = { 0 };

	lv_item.mask = LVIF_TEXT;
	lv_item.pszText = const_cast<LPTSTR>(value.c_str());
	lv_item.iItem = row;
	lv_item.iSubItem = column;

	if (column == 0)ListView_InsertItem(this->GetControlHandle(), &lv_item);
	else ListView_SetItem(this->GetControlHandle(), &lv_item);
}
void daxie::control::ListView::AddItem(int row, int column, int value) {
	tstring str = TStringFunctions::to_string(value);
	this->AddItem(row, column, str);
}
void daxie::control::ListView::AddItem(int row, int column, float value, int digits) {
	tstring str = TStringFunctions::to_string(value, digits);
	this->AddItem(row, column, str);
}
