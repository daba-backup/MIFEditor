#include"MainWindow.h"
#include"CommonDialog.h"
#include"EmbeddedInfo.h"
#include"MIFParser.h"
#include"MIFWriter.h"
#include"MissionInfo.h"
#include"TStringFunctions.h"
#include<tchar.h>

const int daxie::prg::PreviewTextFormatter::MISSION_FORMAL_NAME_MAX_BYTE_NUM = 35;
const int daxie::prg::PreviewTextFormatter::BRIEFING_TEXT_LINE_MAX_BYTE_NUM = 45;
const int daxie::prg::PreviewTextFormatter::BRIEFING_TEXT_MAX_LINE_NUM = 16;

daxie::tstring daxie::prg::PreviewTextFormatter::GetFormattedMissionFormalName(const daxie::tstring& str) {
	daxie::tstring ret;
	ret.clear();

	int length = static_cast<int>(str.length());
	int count = 0;

	for (int i = 0; i < length; i++) {
		ret.push_back(str[i]);

		if (str[i] == TEXT('\t'))count += 6;
		else if (_istascii(str[i]))count += 1;
		else count += 2;

		if (count >= MISSION_FORMAL_NAME_MAX_BYTE_NUM)break;
	}

	return ret;
}
daxie::tstring daxie::prg::PreviewTextFormatter::GetFormattedBriefingText(const daxie::tstring& str) {
	daxie::tstring ret;
	ret.clear();

	std::vector<daxie::tstring> lines = daxie::TStringFunctions::split(str, TEXT("\r\n"));
	int line_num = static_cast<int>(lines.size());
	if (line_num > BRIEFING_TEXT_MAX_LINE_NUM)line_num = BRIEFING_TEXT_MAX_LINE_NUM;

	for (int i = 0; i < line_num; i++) {
		int length = static_cast<int>(lines[i].length());
		int count = 0;

		daxie::tstring line_temp;
		line_temp.clear();

		for (int j = 0; j < length; j++) {
			line_temp.push_back(lines[i][j]);

			if (lines[i][j] == TEXT('\t'))count += 6;
			else if (_istascii(lines[i][j]))count += 1;
			else count += 2;

			if (count >= BRIEFING_TEXT_LINE_MAX_BYTE_NUM)break;
		}

		ret += line_temp;
		ret += TEXT("\r\n");
	}

	return ret;
}

daxie::window::MainWindow::MainWindow():
	formal_name_display_height(60),tab_height(50) {
	already_created_flag = false;
	operation_type = daxie::prg::OperationType::NONE;

	last_used_filename.clear();
	last_used_encoding.clear();

	formatted_mission_formal_name.clear();
	formatted_briefing_text.clear();

	current_page = 0;
}
daxie::window::MainWindow::~MainWindow() {

}

void daxie::window::MainWindow::PublicLoadMIF(const daxie::tstring& filename) {
	std::string encoding = "Shift-JIS";

	selected_filename = filename;
	last_used_filename = selected_filename;
	last_used_encoding = encoding;

	this->LoadMIF(encoding);
}

BOOL daxie::window::MainWindow::onCreate(HWND hwnd, LPCREATESTRUCT cs) {
	daxie::window::Window::onCreate(hwnd, cs);

	//Menu
	menubar = std::make_unique<daxie::menu::MenuBar>(hwnd);

	menu_file = std::make_unique<daxie::menu::Menu>(TEXT("ファイル(&F)"));
	menuitem_create_new = std::make_unique<daxie::menu::MenuItem>(TEXT("新規作成(&N)"));
	menuitem_open = std::make_unique<daxie::menu::MenuItem>(TEXT("開く(&O)"));
	menuitem_overwrite = std::make_unique<daxie::menu::MenuItem>(TEXT("上書き保存(&S)"));
	menuitem_save_as= std::make_unique<daxie::menu::MenuItem>(TEXT("名前を付けて保存(&A)"));
	menuitem_exit= std::make_unique<daxie::menu::MenuItem>(TEXT("終了(&X)"));
	menu_file->Add(0, menuitem_create_new);
	menu_file->Add(1, menuitem_open);
	menu_file->AddSeparator(2);
	menu_file->Add(3, menuitem_overwrite);
	menu_file->Add(4, menuitem_save_as);
	menu_file->AddSeparator(5);
	menu_file->Add(6, menuitem_exit);

	menu_help = std::make_unique<daxie::menu::Menu>(TEXT("ヘルプ(&H)"));
	menuitem_version_info = std::make_unique<daxie::menu::MenuItem>(TEXT("バージョン情報(&V)"));
	menuitem_visit_website = std::make_unique<daxie::menu::MenuItem>(TEXT("作者のサイトを訪問する(&W)"));
	menu_help->Add(0, menuitem_version_info);
	menu_help->AddSeparator(1);
	menu_help->Add(2, menuitem_visit_website);

	menubar->Add(0, menu_file);
	menubar->Add(1, menu_help);

	menubar->UpdateMenuBar();

	//Tab
	tab = std::make_unique<daxie::control::Tab>(0, 0, 0, 0, hwnd);
	tab->InsertItem(0, TEXT("編集"));
	tab->InsertItem(1, TEXT("プレビュー"));
	tab->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	//Static
	label_mission_name = std::make_unique<daxie::control::Static>(TEXT("ミッション識別名"), 0, 0, 0, 0, hwnd);
	label_mission_formal_name = std::make_unique<daxie::control::Static>(TEXT("ミッション正式名称"), 0, 0, 0, 0, hwnd);
	label_bd1_filename= std::make_unique<daxie::control::Static>(TEXT("ブロックのパス名"), 0, 0, 0, 0, hwnd);
	label_pd1_filename=std::make_unique<daxie::control::Static>(TEXT("ポイントのパス名"), 0, 0, 0, 0, hwnd);
	label_sky= std::make_unique<daxie::control::Static>(TEXT("空"), 0, 0, 0, 0, hwnd);
	label_image1_filename= std::make_unique<daxie::control::Static>(TEXT("画像1のパス名"), 0, 0, 0, 0, hwnd);
	label_image2_filename= std::make_unique<daxie::control::Static>(TEXT("画像2のパス名"), 0, 0, 0, 0, hwnd);
	label_article_info_filename= std::make_unique<daxie::control::Static>(TEXT("追加小物のパス名"), 0, 0, 0, 0, hwnd);
	label_briefing_text= std::make_unique<daxie::control::Static>(TEXT("ブリーフィング文章"), 0, 0, 0, 0, hwnd);
	label_mission_name->AppendWindowStyle(SS_CENTERIMAGE);
	label_mission_name->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_mission_formal_name->AppendWindowStyle(SS_CENTERIMAGE);
	label_mission_formal_name->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_bd1_filename->AppendWindowStyle(SS_CENTERIMAGE);
	label_bd1_filename->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_pd1_filename->AppendWindowStyle(SS_CENTERIMAGE);
	label_pd1_filename->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_sky->AppendWindowStyle(SS_CENTERIMAGE);
	label_sky->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_image1_filename->AppendWindowStyle(SS_CENTERIMAGE);
	label_image1_filename->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_image2_filename->AppendWindowStyle(SS_CENTERIMAGE);
	label_image2_filename->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_article_info_filename->AppendWindowStyle(SS_CENTERIMAGE);
	label_article_info_filename->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_briefing_text->AppendWindowStyle(SS_CENTERIMAGE);
	label_briefing_text->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	label_mission_formal_name_display = std::make_unique<daxie::control::Static>(TEXT(""), 0, 0, 0, 0, hwnd);
	label_briefing_text_display = std::make_unique<daxie::control::Static>(TEXT(""), 0, 0, 0, 0, hwnd);
	label_mission_formal_name_display->AppendWindowStyle(SS_CENTERIMAGE);
	label_mission_formal_name_display->SetControlFont(64, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	label_briefing_text_display->RemoveWindowStyle(SS_CENTER);
	label_briefing_text_display->AppendWindowStyle(SS_LEFT);
	label_briefing_text_display->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	//ComboBox
	dl_sky_type = std::make_unique<daxie::control::DropdownList>(0, 0, 0, 0, hwnd);
	dl_sky_type->AddItem(TEXT("なし"));
	dl_sky_type->AddItem(TEXT("晴れ"));
	dl_sky_type->AddItem(TEXT("曇り"));
	dl_sky_type->AddItem(TEXT("夜"));
	dl_sky_type->AddItem(TEXT("夕方"));
	dl_sky_type->AddItem(TEXT("荒地"));

	//Edit
	edit_mission_name = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_mission_formal_name = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_bd1_filename = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_pd1_filename = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_image1_filename = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_image2_filename = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_article_info_filename = std::make_unique<daxie::control::TextField>(0, 0, 0, 0, hwnd);
	edit_briefing_text = std::make_unique<daxie::control::TextArea>(0, 0, 0, 0, hwnd);

	edit_briefing_text->SetControlFont(32, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	//CheckBox
	cb_extra_hitcheck = std::make_unique<daxie::control::CheckBox>(TEXT("追加判定"), 0, 0, 0, 0, hwnd);
	cb_darken_screen = std::make_unique<daxie::control::CheckBox>(TEXT("画面を暗くする"), 0, 0, 0, 0, hwnd);

	//Button
	button_open = std::make_unique<daxie::control::Button>(TEXT("開く"), 0, 0, 0, 0, hwnd);
	button_save = std::make_unique<daxie::control::Button>(TEXT("保存"), 0, 0, 0, 0, hwnd);

	this->SetDefaultValuesToControls();

	//Set a timer.
	SetTimer(hwnd, 1, 17, NULL);

	already_created_flag = true;

	return TRUE;
}
void daxie::window::MainWindow::onDestroy(HWND hwnd) {
	daxie::window::Window::onDestroy(hwnd);

	PostQuitMessage(0);
}
LRESULT daxie::window::MainWindow::onClose(HWND hwnd) {
	int yesno = MessageBox(hwnd, TEXT("終了しますか?"), TEXT("通知"), MB_ICONQUESTION | MB_YESNO);

	if (yesno == IDYES)return DefWindowProc(hwnd, WM_CLOSE, 0, 0);
	else return 0;
}
void daxie::window::MainWindow::onPaint(HWND hwnd) {
	daxie::window::Window::onPaint(hwnd);
}
void daxie::window::MainWindow::onSize(HWND hwnd, UINT state, int cx, int cy) {
	if (already_created_flag == false)return;

	tab->MoveControl(0, 0, cx, tab_height);

	this->onSize_Edit(cx, cy);
	this->onSize_Preview(cx, cy);
}
void daxie::window::MainWindow::onCommand(HWND hwnd, int id, HWND hwndctrl, UINT code_notify) {
	if (already_created_flag == false)return;

	if (menuitem_exit->IsThisMenuItem(id) == TRUE) {
		this->CloseWindow();
	}

	if (menuitem_create_new->IsThisMenuItem(id) == TRUE) {
		int yesno= MessageBox(hwnd, TEXT("新規作成しますか?"), TEXT("通知"), MB_ICONINFORMATION | MB_YESNO);
		if (yesno == IDYES) {
			this->SetDefaultValuesToControls();
			
			if (window_sew) {
				if (window_sew->IsDestroyed() == false) {
					window_sew->CloseWindow();
				}
			}

			selected_filename.clear();
			last_used_filename.clear();
			last_used_encoding.clear();
		}
	}
	if (menuitem_open->IsThisMenuItem(id) == TRUE||button_open->IsThisControl(hwndctrl)==TRUE) {
		this->PrepareLoadMIF();
	}
	if (menuitem_save_as->IsThisMenuItem(id) == TRUE||button_save->IsThisControl(hwndctrl)==TRUE) {
		this->PrepareWriteMIF();
	}
	if (menuitem_overwrite->IsThisMenuItem(id) == TRUE) {
		if (last_used_filename.size()!=0 && last_used_encoding.size()!=0) {
			int yesno = MessageBox(hwnd, TEXT("上書き保存しますか?"), TEXT("通知"), MB_ICONINFORMATION | MB_YESNO);
			if(yesno==IDYES)this->WriteMIF(last_used_encoding);
		}
		else {
			this->PrepareWriteMIF();
		}
	}
	if (menuitem_version_info->IsThisMenuItem(id) == TRUE) {
		daxie::tstring str = TEXT("");

		str += daxie::prg::EmbeddedInfo::PROGRAM_NAME;
		str += TEXT("\r\n");
		str += TEXT("\r\n");
		str += TEXT("公開日:") + daxie::prg::EmbeddedInfo::RELEASE_DATE;
		str += TEXT("\r\n");
		str += TEXT("作者:") + daxie::prg::EmbeddedInfo::AUTHOR_NAME;

		MessageBox(hwnd, str.c_str(), TEXT("バージョン情報"), MB_ICONINFORMATION);
	}
	if (menuitem_visit_website->IsThisMenuItem(id) == TRUE) {
		ShellExecute(NULL, TEXT("open"), 
			TEXT("https://sites.google.com/site/xopsaddonwarehouse/home"), NULL, TEXT(""), SW_SHOW);
	}
}
void daxie::window::MainWindow::onTimer(HWND hwnd, UINT id) {
	this->onTimer_Tab();
	this->onTimer_SelectEncodingWindow();
}

void daxie::window::MainWindow::onSize_Edit(int cx,int cy) {
	constexpr float label_col_ratio = 0.2f;
	constexpr float edit_col_ratio = 0.4f;
	constexpr float briefing_col_ratio = 1.0f - label_col_ratio - edit_col_ratio;

	constexpr int margin = 5;
	constexpr int edit_margin_y = 10;

	constexpr int control_height_min = 30;

	int label_col_width = static_cast<int>(cx*label_col_ratio);
	int edit_col_width = static_cast<int>(cx*edit_col_ratio);
	int briefing_col_width = static_cast<int>(cx*briefing_col_ratio);

	int row_height = (cy - tab_height) / 9;

	int label_width = label_col_width - 2 * margin;
	int edit_width = edit_col_width - 2 * margin;
	int briefing_width = briefing_col_width - 2 * margin;

	int label_height;
	int edit_height;
	if (row_height - 2 * margin < control_height_min)label_height = control_height_min;
	else label_height = row_height - 2 * margin;
	if (row_height - 2 * edit_margin_y < control_height_min)edit_height = control_height_min;
	else edit_height = row_height - 2 * edit_margin_y;

	int edit_pos_x = label_col_width + margin;
	int briefing_pos_x = label_col_width + edit_col_width + margin;

	int pos_offset_y = tab_height + margin;
	int edit_pos_offset_y = tab_height + edit_margin_y;

	int left_partition_center_x = (label_col_width + edit_col_width) / 2;
	int cb_width = left_partition_center_x - 2 * margin;

	int center_x = label_col_width + edit_col_width;
	int right_partition_center_x = (cx + center_x) / 2;
	int button_width = (cx - right_partition_center_x) - 2 * margin;

	int edit_font_size = edit_height - 10;

	label_mission_name->MoveControl(margin, pos_offset_y, label_width, label_height);
	label_mission_formal_name->MoveControl(margin, row_height + pos_offset_y, label_width, label_height);
	label_bd1_filename->MoveControl(margin, 2 * row_height + pos_offset_y, label_width, label_height);
	label_pd1_filename->MoveControl(margin, 3 * row_height + pos_offset_y, label_width, label_height);
	label_sky->MoveControl(margin, 4 * row_height + pos_offset_y, label_width, label_height);
	label_image1_filename->MoveControl(margin, 5 * row_height + pos_offset_y, label_width, label_height);
	label_image2_filename->MoveControl(margin, 6 * row_height + pos_offset_y, label_width, label_height);
	label_article_info_filename->MoveControl(margin, 7 * row_height + pos_offset_y, label_width, label_height);
	edit_mission_name->MoveControl(edit_pos_x, edit_pos_offset_y, edit_width, edit_height);
	edit_mission_formal_name->MoveControl(edit_pos_x, row_height + edit_pos_offset_y, edit_width, edit_height);
	edit_bd1_filename->MoveControl(edit_pos_x, 2 * row_height + edit_pos_offset_y, edit_width, edit_height);
	edit_pd1_filename->MoveControl(edit_pos_x, 3 * row_height + edit_pos_offset_y, edit_width, edit_height);
	dl_sky_type->MoveControl(edit_pos_x, 4 * row_height + edit_pos_offset_y, edit_width, edit_height * 10);
	edit_image1_filename->MoveControl(edit_pos_x, 5 * row_height + edit_pos_offset_y, edit_width, edit_height);
	edit_image2_filename->MoveControl(edit_pos_x, 6 * row_height + edit_pos_offset_y, edit_width, edit_height);
	edit_article_info_filename->MoveControl(edit_pos_x, 7 * row_height + edit_pos_offset_y, edit_width, edit_height);

	label_briefing_text->MoveControl(briefing_pos_x, pos_offset_y, briefing_width, label_height);
	edit_briefing_text->MoveControl(briefing_pos_x, row_height + pos_offset_y, briefing_width, 7 * row_height - 2 * margin);

	cb_extra_hitcheck->MoveControl(margin, 8 * row_height + pos_offset_y, cb_width, label_height);
	cb_darken_screen->MoveControl(left_partition_center_x + margin, 8 * row_height + pos_offset_y, cb_width, label_height);

	button_open->MoveControl(center_x + margin, 8 * row_height + pos_offset_y, button_width, label_height);
	button_save->MoveControl(right_partition_center_x + margin, 8 * row_height + pos_offset_y, button_width, label_height);

	edit_mission_name->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_mission_formal_name->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_bd1_filename->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_pd1_filename->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	dl_sky_type->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_image1_filename->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_image2_filename->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	edit_article_info_filename->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	cb_extra_hitcheck->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	cb_darken_screen->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));

	button_open->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
	button_save->SetControlFont(edit_font_size, FW_NORMAL, FALSE, FALSE, FALSE, FALSE, TEXT("メイリオ"));
}
void daxie::window::MainWindow::onSize_Preview(int cx, int cy) {
	constexpr int margin = 5;

	int display_y = tab_height + margin;
	int display_height = formal_name_display_height - 2 * margin;

	int briefing_y = tab_height + formal_name_display_height + margin;
	int briefing_height = cy - briefing_y - margin;

	label_mission_formal_name_display->MoveControl(margin, display_y, cx - 2 * margin, display_height);
	label_briefing_text_display->MoveControl(margin, briefing_y, cx-2*margin, briefing_height);
}

void daxie::window::MainWindow::onTimer_Tab() {
	int cur_sel = tab->GetCurrentSelection();
	if (cur_sel == 0) {
		this->ShowEditPage();
		this->HidePreviewPage();

		if (formatted_mission_formal_name.size() != 0) {
			formatted_mission_formal_name.clear();
			label_mission_formal_name_display->SetControlText(TEXT(""));
		}
		if (formatted_briefing_text.size() != 0) {
			formatted_briefing_text.clear();
			label_briefing_text_display->SetControlText(TEXT(""));
		}
	}
	else if (cur_sel == 1) {
		this->ShowPreviewPage();
		this->HideEditPage();

		if (formatted_mission_formal_name.size() == 0) {
			daxie::tstring mission_formal_name = edit_mission_formal_name->GetControlText();
			formatted_mission_formal_name = daxie::prg::PreviewTextFormatter::GetFormattedMissionFormalName(mission_formal_name);

			label_mission_formal_name_display->SetControlText(mission_formal_name);
		}
		if (formatted_briefing_text.size() == 0) {
			daxie::tstring briefing_text = edit_briefing_text->GetControlText();
			formatted_briefing_text = daxie::prg::PreviewTextFormatter::GetFormattedBriefingText(briefing_text);

			label_briefing_text_display->SetControlText(formatted_briefing_text);
		}
	}

	current_page = cur_sel;
}
void daxie::window::MainWindow::onTimer_SelectEncodingWindow() {
	if (!window_sew)return;
	if (window_sew->IsDestroyed() == false)return;

	//Window was already destroyed.
	bool ok_flag = window_sew->GetOKFlag();
	std::string encoding = window_sew->GetSelectedEncodingStr();

	window_sew.reset();

	if (ok_flag == false)return;

	if (operation_type == daxie::prg::OperationType::READ) {
		last_used_filename = selected_filename;
		last_used_encoding = encoding;
		this->LoadMIF(encoding);
	}
	else if (operation_type == daxie::prg::OperationType::WRITE) {
		last_used_filename = selected_filename;
		last_used_encoding = encoding;
		this->WriteMIF(encoding);
	}
}

void daxie::window::MainWindow::ShowEditPage() {
	label_mission_name->ShowControl();
	label_mission_formal_name->ShowControl();
	label_bd1_filename->ShowControl();
	label_pd1_filename->ShowControl();
	label_sky->ShowControl();
	label_image1_filename->ShowControl();
	label_image2_filename->ShowControl();
	label_article_info_filename->ShowControl();
	label_briefing_text->ShowControl();

	edit_mission_name->ShowControl();
	edit_mission_formal_name->ShowControl();
	edit_bd1_filename->ShowControl();
	edit_pd1_filename->ShowControl();
	dl_sky_type->ShowControl();
	edit_image1_filename->ShowControl();
	edit_image2_filename->ShowControl();
	edit_article_info_filename->ShowControl();
	edit_briefing_text->ShowControl();

	cb_extra_hitcheck->ShowControl();
	cb_darken_screen->ShowControl();

	button_open->ShowControl();
	button_save->ShowControl();
}
void daxie::window::MainWindow::HideEditPage() {
	label_mission_name->HideControl();
	label_mission_formal_name->HideControl();
	label_bd1_filename->HideControl();
	label_pd1_filename->HideControl();
	label_sky->HideControl();
	label_image1_filename->HideControl();
	label_image2_filename->HideControl();
	label_article_info_filename->HideControl();
	label_briefing_text->HideControl();

	edit_mission_name->HideControl();
	edit_mission_formal_name->HideControl();
	edit_bd1_filename->HideControl();
	edit_pd1_filename->HideControl();
	dl_sky_type->HideControl();
	edit_image1_filename->HideControl();
	edit_image2_filename->HideControl();
	edit_article_info_filename->HideControl();
	edit_briefing_text->HideControl();

	cb_extra_hitcheck->HideControl();
	cb_darken_screen->HideControl();

	button_open->HideControl();
	button_save->HideControl();
}
void daxie::window::MainWindow::ShowPreviewPage() {
	label_mission_formal_name_display->ShowControl();
	label_briefing_text_display->ShowControl();
}
void daxie::window::MainWindow::HidePreviewPage() {
	label_mission_formal_name_display->HideControl();
	label_briefing_text_display->HideControl();
}

void daxie::window::MainWindow::SetDefaultValuesToControls() {
	edit_mission_name->SetControlText(TEXT(""));
	edit_mission_formal_name->SetControlText(TEXT(""));
	edit_bd1_filename->SetControlText(TEXT(".\\addon\\"));
	edit_pd1_filename->SetControlText(TEXT(".\\addon\\"));
	dl_sky_type->SetCurrentSelection(0);
	edit_image1_filename->SetControlText(TEXT(".\\data\\briefing\\np.bmp"));
	edit_image2_filename->SetControlText(TEXT("!"));
	edit_article_info_filename->SetControlText(TEXT("!"));
	cb_extra_hitcheck->Uncheck();
	cb_darken_screen->Uncheck();
	edit_briefing_text->SetControlText(TEXT(""));
}

void daxie::window::MainWindow::PrepareLoadMIF() {
	if (window_sew) {
		window_sew->CloseWindow();
	}

	HWND hwnd = this->GetHwnd();

	auto file_chooser = std::make_unique<daxie::dialog::FileChooser>();
	file_chooser->SetHwndOwner(hwnd);
	file_chooser->SetFilter(TEXT("ミッション情報ファイル(*.mif)\0*.mif\0\0"));
	file_chooser->SetFlags(OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR);

	if (file_chooser->ShowOpenDialog() == FALSE)return;
	selected_filename = file_chooser->GetSelectedFilename();

	//Monitor this window in onTimer().
	window_sew = std::make_unique<daxie::window::SelectEncodingWindow>();
	window_sew->DHCreateWindow(TEXT("文字コードの選択"),
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd);

	operation_type = daxie::prg::OperationType::READ;
}
void daxie::window::MainWindow::PrepareWriteMIF() {
	if (window_sew) {
		window_sew->CloseWindow();
	}

	HWND hwnd = this->GetHwnd();

	auto file_chooser = std::make_unique<daxie::dialog::FileChooser>();
	file_chooser->SetHwndOwner(hwnd);
	file_chooser->SetFilter(TEXT("ミッション情報ファイル(*.mif)\0*.mif\0\0"));
	file_chooser->SetDefaultExtension(TEXT("mif"));
	file_chooser->SetFlags(OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR);

	if (file_chooser->ShowSaveDialog() == FALSE)return;
	selected_filename = file_chooser->GetSelectedFilename();

	//Monitor this window in onTimer().
	window_sew = std::make_unique<daxie::window::SelectEncodingWindow>();
	window_sew->DHCreateWindow(TEXT("文字コードの選択"),
		CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, hwnd);

	operation_type = daxie::prg::OperationType::WRITE;
}

void daxie::window::MainWindow::LoadMIF(const std::string& encoding) {
	auto mif_parser = std::make_unique<daxie::xops::MIFParser>(selected_filename, encoding);
	if (mif_parser->GetErrorFlag() == true) {
		daxie::tstring error_message = mif_parser->GetErrorMessage();
		HWND hwnd = this->GetHwnd();

		MessageBox(hwnd, error_message.c_str(), TEXT("エラー"), MB_ICONEXCLAMATION);
		return;
	}

	daxie::xops::MissionInfo mission_info = mif_parser->GetMissionInfo();

	edit_mission_name->SetControlText(mission_info.GetMissionName());
	edit_mission_formal_name->SetControlText(mission_info.GetMissionFormalName());
	edit_bd1_filename->SetControlText(mission_info.GetBD1Filename());
	edit_pd1_filename->SetControlText(mission_info.GetPD1Filename());
	dl_sky_type->SetCurrentSelection(mission_info.GetSkyType());
	edit_image1_filename->SetControlText(mission_info.GetImage1Filename());
	edit_image2_filename->SetControlText(mission_info.GetImage2Filename());
	edit_article_info_filename->SetControlText(mission_info.GetArticleInfoFilename());

	if (mission_info.GetExtraHitcheckFlag() == true)cb_extra_hitcheck->Check();
	else cb_extra_hitcheck->Uncheck();
	if (mission_info.GetDarkenScreenFlag() == true)cb_darken_screen->Check();
	else cb_darken_screen->Uncheck();

	std::vector<daxie::tstring> briefing_text = mission_info.GetBriefingText();
	daxie::tstring str_briefing_text = TEXT("");
	for (auto& line : briefing_text) {
		str_briefing_text += line;
		str_briefing_text += TEXT("\r\n");
	}
	edit_briefing_text->SetControlText(str_briefing_text);
}
void daxie::window::MainWindow::WriteMIF(const std::string& encoding) {
	daxie::xops::MissionInfo mission_info;

	mission_info.SetMissionName(edit_mission_name->GetControlText());
	mission_info.SetMissionFormalName(edit_mission_formal_name->GetControlText());
	mission_info.SetBD1Filename(edit_bd1_filename->GetControlText());
	mission_info.SetPD1Filename(edit_pd1_filename->GetControlText());
	mission_info.SetSkyType(dl_sky_type->GetCurrentSelection());
	mission_info.SetImage1Filename(edit_image1_filename->GetControlText());
	mission_info.SetImage2Filename(edit_image2_filename->GetControlText());
	mission_info.SetArticleInfoFilename(edit_article_info_filename->GetControlText());

	BOOL extra_hitcheck_flag = cb_extra_hitcheck->IsChecked();
	BOOL darken_screen_flag = cb_darken_screen->IsChecked();

	if (extra_hitcheck_flag == TRUE)mission_info.SetExtraHitcheckFlag(true);
	else mission_info.SetExtraHitcheckFlag(false);
	if (darken_screen_flag == TRUE)mission_info.SetDarkenScreenFlag(true);
	else mission_info.SetDarkenScreenFlag(false);

	daxie::tstring briefing_text = edit_briefing_text->GetControlText();
	std::vector<daxie::tstring> lines = daxie::TStringFunctions::split(briefing_text, TEXT("\r\n"));

	mission_info.SetBriefingText(lines);

	auto mif_writer = std::make_unique<daxie::xops::MIFWriter>(mission_info);
	mif_writer->Write(selected_filename, encoding);

	if (mif_writer->GetErrorFlag() == true) {
		daxie::tstring error_message = mif_writer->GetErrorMessage();
		HWND hwnd = this->GetHwnd();
		
		MessageBox(hwnd, error_message.c_str(), TEXT("エラー"), MB_ICONEXCLAMATION);
		return;
	}

	HWND hwnd = this->GetHwnd();
	MessageBox(hwnd, TEXT("保存しました。"), TEXT("通知"), MB_ICONINFORMATION);
}