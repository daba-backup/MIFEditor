#include"MenuBar.h"

daxie::menu::MenuBar::MenuBar(HWND hwnd) {
	this->hwnd = hwnd;
	hmenu = CreateMenu();
}
daxie::menu::MenuBar::~MenuBar() {

}

void daxie::menu::MenuBar::Add(int index, std::unique_ptr<daxie::menu::Menu>& menu) {
	MENUITEMINFO mii;
	daxie::tstring text = menu->GetText();

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_SUBMENU;
	mii.fType = MFT_STRING;
	mii.hSubMenu = menu->hmenu;
	mii.dwTypeData = const_cast<LPTSTR>(text.c_str());

	InsertMenuItem(hmenu, index, TRUE, &mii);
}
void daxie::menu::MenuBar::Add(int index, std::unique_ptr<daxie::menu::MenuItem>& item) {
	MENUITEMINFO mii;
	daxie::tstring text = item->GetText();
	int id = item->id;

	mii.cbSize = sizeof(MENUITEMINFO);
	mii.fMask = MIIM_TYPE | MIIM_ID;
	mii.fType = MFT_STRING;
	mii.dwTypeData = const_cast<LPTSTR>(text.c_str());
	mii.wID = id;

	InsertMenuItem(hmenu, index, TRUE, &mii);
}

void daxie::menu::MenuBar::UpdateMenuBar() {
	SetMenu(hwnd, hmenu);
}