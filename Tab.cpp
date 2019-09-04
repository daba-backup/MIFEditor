#include"Tab.h"
#include<CommCtrl.h>

daxie::control::Tab::Tab(int x, int y, int width, int height, HWND hwnd_parent):
	daxie::control::Control(TEXT(""), WC_TABCONTROL, x, y, width, height, hwnd_parent, 
		NULL, WS_VISIBLE | WS_CHILD | WS_CLIPSIBLINGS, 0) {

}
daxie::control::Tab::~Tab() {

}

void daxie::control::Tab::InsertItem(int index, const daxie::tstring& text) {
	TCITEM tcitem;

	tcitem.mask = TCIF_TEXT;
	tcitem.pszText = const_cast<LPTSTR>(text.c_str());

	TabCtrl_InsertItem(this->GetControlHandle(), index, &tcitem);
}
void daxie::control::Tab::SetCurrentSelection(int index) {
	HWND hcontrol = this->GetControlHandle();
	TabCtrl_SetCurSel(hcontrol, index);
}

int daxie::control::Tab::GetCurrentSelection() {
	HWND hcontrol = this->GetControlHandle();
	int ret = TabCtrl_GetCurSel(hcontrol);

	return ret;
}