#include"CommonDialog.h"

daxie::dialog::CommonDialog::CommonDialog() {

}
daxie::dialog::CommonDialog::~CommonDialog() {

}

daxie::dialog::ChooseColorDialog::ChooseColorDialog() {
	memset(&cc, 0, sizeof(cc));

	cc.lStructSize = sizeof(CHOOSECOLOR);
	cc.lpCustColors = &cust_colors[0];
	cc.Flags = CC_FULLOPEN | CC_RGBINIT;
}
daxie::dialog::ChooseColorDialog::~ChooseColorDialog() {

}

void daxie::dialog::ChooseColorDialog::SetHwndOwner(HWND hwnd) {
	cc.hwndOwner = hwnd;
}
void daxie::dialog::ChooseColorDialog::SetInitialColor(COLORREF color) {
	cc.rgbResult = color;
}
void daxie::dialog::ChooseColorDialog::SetFlags(DWORD flags) {
	cc.Flags = flags;
}

BOOL daxie::dialog::ChooseColorDialog::Show() {
	BOOL ret = ChooseColor(&cc);
	return ret;
}

COLORREF daxie::dialog::ChooseColorDialog::GetSelectedColor() {
	return cc.rgbResult;
}

daxie::dialog::ChooseFontDialog::ChooseFontDialog() {
	memset(&cf, 0, sizeof(CHOOSEFONT));
	memset(&lf, 0, sizeof(LOGFONT));

	cf.lStructSize = sizeof(CHOOSEFONT);
	cf.lpLogFont = &lf;
	cf.Flags = CF_EFFECTS | CF_SCREENFONTS;
}
daxie::dialog::ChooseFontDialog::~ChooseFontDialog() {

}

void daxie::dialog::ChooseFontDialog::SetHwndOwner(HWND hwnd) {
	cf.hwndOwner = hwnd;
}
void daxie::dialog::ChooseFontDialog::SetFlags(DWORD flags) {
	cf.Flags = flags;
}

BOOL daxie::dialog::ChooseFontDialog::Show() {
	BOOL ret = ChooseFont(&cf);
	return ret;
}

LOGFONT daxie::dialog::ChooseFontDialog::GetSelectedFont() {
	return lf;
}

daxie::dialog::FileChooser::FileChooser() {
	memset(&ofn, 0, sizeof(OPENFILENAME));
	
	for (int i = 0; i < MAX_PATH; i++)filename[i] = 0;
	for (int i = 0; i < 256; i++)custom_filter[i] = 0;

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.lpstrFile = &filename[0];
	ofn.nMaxFile = MAX_PATH;
	ofn.lpstrCustomFilter = &custom_filter[0];
	ofn.nMaxCustFilter = 256;
	ofn.nFilterIndex = 0;
}
daxie::dialog::FileChooser::~FileChooser() {

}

OPENFILENAME& daxie::dialog::FileChooser::GetOfn() {
	return ofn;
}

void daxie::dialog::FileChooser::SetHwndOwner(HWND hwnd) {
	ofn.hwndOwner = hwnd;
}
void daxie::dialog::FileChooser::SetFilter(LPCTSTR filter) {
	ofn.lpstrFilter = filter;
}
void daxie::dialog::FileChooser::SetFlags(DWORD flags) {
	ofn.Flags = flags;
}
void daxie::dialog::FileChooser::SetDefaultExtension(const daxie::tstring& extension) {
	ofn.lpstrDefExt = extension.c_str();
}

BOOL daxie::dialog::FileChooser::ShowOpenDialog() {
	BOOL ret = GetOpenFileName(&ofn);
	return ret;
}
BOOL daxie::dialog::FileChooser::ShowSaveDialog() {
	BOOL ret = GetSaveFileName(&ofn);
	return ret;
}

daxie::tstring daxie::dialog::FileChooser::GetSelectedFilename() {
	daxie::tstring ret;

	ret.clear();
	int length = lstrlen(&filename[0]);
	for (int i = 0; i < length; i++) {
		ret.push_back(filename[i]);
	}

	return ret;
}
