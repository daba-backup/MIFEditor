#pragma once

#include"Window.h"
#include"SelectEncodingWindow.h"
#include<memory>
#include<vector>
#include"MenuBar.h"
#include"Menu.h"
#include"MenuItem.h"
#include"Button.h"
#include"CheckBox.h"
#include"ComboBox.h"
#include"Static.h"
#include"Tab.h"
#include"TextArea.h"
#include"TextField.h"

namespace daxie {
	namespace prg {
		class PreviewTextFormatter final :public daxie::Object {
		private:
			static const int MISSION_FORMAL_NAME_MAX_BYTE_NUM;
			static const int BRIEFING_TEXT_LINE_MAX_BYTE_NUM;
			static const int BRIEFING_TEXT_MAX_LINE_NUM;

		public:
			static daxie::tstring GetFormattedMissionFormalName(const daxie::tstring& str);
			static daxie::tstring GetFormattedBriefingText(const daxie::tstring& str);
		};

		enum class OperationType {
			NONE,
			READ,
			WRITE
		};
	}

	namespace window {
		class MainWindow final:public daxie::window::Window {
		private:
			const int tab_height;
			const int formal_name_display_height;

		private:
			bool already_created_flag;
			daxie::prg::OperationType operation_type;

			daxie::tstring selected_filename;
			daxie::tstring last_used_filename;
			std::string last_used_encoding;

			daxie::tstring formatted_mission_formal_name;
			daxie::tstring formatted_briefing_text;

			int current_page;

			//Window
			std::unique_ptr<daxie::window::SelectEncodingWindow> window_sew;

			//Menu
			std::unique_ptr<daxie::menu::MenuBar> menubar;
			std::unique_ptr<daxie::menu::Menu> menu_file;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_create_new;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_open;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_overwrite;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_save_as;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_exit;
			std::unique_ptr<daxie::menu::Menu> menu_help;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_version_info;
			std::unique_ptr<daxie::menu::MenuItem> menuitem_visit_website;

			//Tab
			std::unique_ptr<daxie::control::Tab> tab;

			//Static
			std::unique_ptr<daxie::control::Static> label_mission_name;
			std::unique_ptr<daxie::control::Static> label_mission_formal_name;
			std::unique_ptr<daxie::control::Static> label_bd1_filename;
			std::unique_ptr<daxie::control::Static> label_pd1_filename;
			std::unique_ptr<daxie::control::Static> label_sky;
			std::unique_ptr<daxie::control::Static> label_image1_filename;
			std::unique_ptr<daxie::control::Static> label_image2_filename;
			std::unique_ptr<daxie::control::Static> label_article_info_filename;
			std::unique_ptr<daxie::control::Static> label_briefing_text;

			std::unique_ptr<daxie::control::Static> label_mission_formal_name_display;
			std::unique_ptr<daxie::control::Static> label_briefing_text_display;

			//ComboBox
			std::unique_ptr<daxie::control::DropdownList> dl_sky_type;

			//Edit
			std::unique_ptr<daxie::control::TextField> edit_mission_name;
			std::unique_ptr<daxie::control::TextField> edit_mission_formal_name;
			std::unique_ptr<daxie::control::TextField> edit_bd1_filename;
			std::unique_ptr<daxie::control::TextField> edit_pd1_filename;
			std::unique_ptr<daxie::control::TextField> edit_image1_filename;
			std::unique_ptr<daxie::control::TextField> edit_image2_filename;
			std::unique_ptr<daxie::control::TextField> edit_article_info_filename;
			std::unique_ptr<daxie::control::TextArea> edit_briefing_text;

			//CheckBox
			std::unique_ptr<daxie::control::CheckBox> cb_extra_hitcheck;
			std::unique_ptr<daxie::control::CheckBox> cb_darken_screen;

			//Button
			std::unique_ptr<daxie::control::Button> button_open;
			std::unique_ptr<daxie::control::Button> button_save;

		public:
			MainWindow();
			~MainWindow();

			void PublicLoadMIF(const daxie::tstring& filename);

		public:
			BOOL onCreate(HWND hwnd, LPCREATESTRUCT cs)override;
			void onDestroy(HWND hwnd)override;
			LRESULT onClose(HWND hwnd)override;
			void onPaint(HWND hwnd)override;
			void onSize(HWND hwnd, UINT state, int cx, int cy)override;
			void onCommand(HWND hwnd, int id, HWND hwndctrl, UINT code_notify)override;
			void onTimer(HWND hwnd, UINT id)override;

		private:
			void onSize_Edit(int cx,int cy);
			void onSize_Preview(int cs, int cy);

			void onTimer_Tab();
			void onTimer_SelectEncodingWindow();

			void ShowEditPage();
			void HideEditPage();
			void ShowPreviewPage();
			void HidePreviewPage();

			void SetDefaultValuesToControls();

			void PrepareLoadMIF();
			void PrepareWriteMIF();

			void LoadMIF(const std::string& encoding);
			void WriteMIF(const std::string& encoding);
		};
	}
}