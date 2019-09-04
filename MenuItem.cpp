#include"MenuItem.h"
#include"UniqueIDGenerator.h"

daxie::menu::MenuItem::MenuItem(const daxie::tstring& text) {
	this->text = text;
	id = daxie::tool::UniqueIDGenerator::GetNextID();
}
daxie::menu::MenuItem::~MenuItem() {

}

BOOL daxie::menu::MenuItem::IsThisMenuItem(int id) {
	if (this->id == id)return TRUE;
	else return FALSE;
}

daxie::tstring daxie::menu::MenuItem::GetText() {
	return text;
}
