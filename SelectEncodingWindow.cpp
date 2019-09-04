#include"SelectEncodingWindow.h"

daxie::window::SelectEncodingWindow::SelectEncodingWindow() {
	already_created_flag = false;

	ok_flag = false;
	selected_encoding = -1;
}
daxie::window::SelectEncodingWindow::~SelectEncodingWindow() {

}

BOOL daxie::window::SelectEncodingWindow::onCreate(HWND hwnd, LPCREATESTRUCT cs) {
	daxie::window::Window::onCreate(hwnd, cs);

	label_encoding = std::make_unique<daxie::control::Static>(TEXT("文字コード"), 0, 0, 0, 0, hwnd);
	dl_encoding = std::make_unique<daxie::control::DropdownList>(0, 0, 0, 0, hwnd);
	button_cancel= std::make_unique<daxie::control::Button>(TEXT("キャンセル"), 0, 0, 0, 0, hwnd);
	button_ok= std::make_unique<daxie::control::Button>(TEXT("OK"), 0, 0, 0, 0, hwnd);

	label_encoding->AppendWindowStyle(SS_CENTERIMAGE);
	label_encoding->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	dl_encoding->SetControlFont(64, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	button_cancel->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	button_ok->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	dl_encoding->AddItem(TEXT("Shift-JIS"));
	dl_encoding->AddItem(TEXT("EUC-KR"));
	dl_encoding->AddItem(TEXT("UTF-8"));
	dl_encoding->SetCurrentSelection(0);

	POINT pos = this->GetWindowPos();
	this->DHMoveWindow(pos.x, pos.y, 600, 200);

	this->RemoveWindowStyle(WS_THICKFRAME);
	this->RemoveWindowStyle(WS_MAXIMIZEBOX);

	already_created_flag = true;

	return TRUE;
}
void daxie::window::SelectEncodingWindow::onDestroy(HWND hwnd) {
	daxie::window::Window::onDestroy(hwnd);
}
void daxie::window::SelectEncodingWindow::onSize(HWND hwnd, UINT state, int cx, int cy) {
	if (already_created_flag == false)return;

	constexpr int left_col_width = 200;
	int right_col_width = cx - left_col_width;

	constexpr int bottom_row_height = 50;
	int top_row_height = cy - bottom_row_height;
	
	constexpr int margin = 5;
	constexpr int dl_margin_y = 10;

	int center_x = cx / 2;
	int button_width = center_x - 2 * margin;
	int button_height = bottom_row_height - 2 * margin;

	label_encoding->MoveControl(margin, margin, left_col_width - 2 * margin, top_row_height - 2 * margin);
	dl_encoding->MoveControl(left_col_width + margin, dl_margin_y, right_col_width - 2 * margin, top_row_height*10);
	button_cancel->MoveControl(margin, top_row_height + margin, button_width, button_height);
	button_ok->MoveControl(center_x + margin, top_row_height + margin, button_width, button_height);
}
void daxie::window::SelectEncodingWindow::onCommand(HWND hwnd, int id, HWND hwndctrl, UINT code_notify) {
	if (already_created_flag == false)return;

	if (button_cancel->IsThisControl(hwndctrl) == TRUE) {
		this->CloseWindow();
	}
	if (button_ok->IsThisControl(hwndctrl) == TRUE) {
		ok_flag = true;
		selected_encoding = dl_encoding->GetCurrentSelection();

		this->CloseWindow();
	}
}

bool daxie::window::SelectEncodingWindow::GetOKFlag() {
	return ok_flag;
}
int daxie::window::SelectEncodingWindow::GetSelectedEncoding() {
	return selected_encoding;
}
std::string daxie::window::SelectEncodingWindow::GetSelectedEncodingStr() {
	std::string ret = "";

	switch (selected_encoding) {
	case 0:
		ret = "Shift-JIS";
		break;
	case 1:
		ret = "EUC-KR";
		break;
	case 2:
		ret = "UTF-8";
		break;
	}

	return ret;
}
