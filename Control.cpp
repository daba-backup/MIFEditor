#include"Control.h"
#include<memory>
#include"WindowTool.h"

daxie::control::Control::Control(
	const daxie::tstring& text, const daxie::tstring& class_name,
	int x, int y, int width, int height,
	HWND hwnd_parent, HMENU hmenu, DWORD style, DWORD ex_style):hfont(NULL) {
	HINSTANCE hinstance = GetModuleHandle(NULL);

	hcontrol = CreateWindowEx(ex_style, class_name.c_str(), text.c_str(), style,
		x, y, width, height, hwnd_parent, hmenu, hinstance, NULL);
	this->hwnd_parent = hwnd_parent;
}
daxie::control::Control::~Control() {

}

HWND daxie::control::Control::GetControlHandle() {
	return hcontrol;
}
HWND daxie::control::Control::GetParentHandle() {
	return hwnd_parent;
}

BOOL daxie::control::Control::IsThisControl(HWND hcontrol) {
	if (this->hcontrol == hcontrol)return TRUE;
	else return FALSE;
}

void daxie::control::Control::SetControlText(const tstring& text) {
	SetWindowText(hcontrol, text.c_str());
}
void daxie::control::Control::AppendWindowStyle(LONG_PTR style) {
	LONG_PTR cur_style = GetWindowLongPtr(hcontrol, GWL_STYLE);
	SetWindowLongPtr(hcontrol, GWL_STYLE, cur_style | style);
}
void daxie::control::Control::RemoveWindowStyle(LONG_PTR style) {
	LONG_PTR cur_style = GetWindowLongPtr(hcontrol, GWL_STYLE);
	SetWindowLongPtr(hcontrol, GWL_STYLE, cur_style &~style);
}
void daxie::control::Control::EnableControl() {
	EnableWindow(hcontrol, TRUE);
}
void daxie::control::Control::DisableControl() {
	EnableWindow(hcontrol, FALSE);
}
void daxie::control::Control::ShowControl() {
	ShowWindow(hcontrol, SW_SHOW);
}
void daxie::control::Control::HideControl() {
	ShowWindow(hcontrol, SW_HIDE);
}
void daxie::control::Control::MoveControl(int x, int y, int width, int height) {
	MoveWindow(hcontrol, x, y, width, height, TRUE);
}
void daxie::control::Control::SetControlFont(int size, int weight, BOOL italic_flag,
	BOOL underline_flag, BOOL strike_out_flag, BOOL antialiased_flag, const daxie::tstring& font_name) {
	if (hfont != NULL) {
		DeleteObject(hfont);
	}

	DWORD font_quality;
	if (antialiased_flag == TRUE)font_quality = ANTIALIASED_QUALITY;
	else font_quality = DEFAULT_QUALITY;

	hfont = CreateFont(size, 0, 0, 0, weight,
		italic_flag, underline_flag, strike_out_flag,
		DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, font_quality, DEFAULT_PITCH, font_name.c_str());
	SendMessage(hcontrol, WM_SETFONT, reinterpret_cast<WPARAM>(hfont), TRUE);
}

daxie::tstring daxie::control::Control::GetControlText() {
	daxie::tstring text = daxie::tool::WindowTool::GetWindowTextTString(hcontrol);

	return text;
}