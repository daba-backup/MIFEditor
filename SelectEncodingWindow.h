#pragma once

#include"Window.h"
#include"Button.h"
#include"ComboBox.h"
#include"Static.h"
#include<memory>

namespace daxie {
	namespace window {
		class SelectEncodingWindow :public daxie::window::Window {
		private:
			bool already_created_flag;

			bool ok_flag;
			int selected_encoding;

			std::unique_ptr<daxie::control::Static> label_encoding;

			std::unique_ptr<daxie::control::DropdownList> dl_encoding;

			std::unique_ptr<daxie::control::Button> button_cancel;
			std::unique_ptr<daxie::control::Button> button_ok;

		public:
			SelectEncodingWindow();
			virtual ~SelectEncodingWindow();

		public:
			BOOL onCreate(HWND hwnd, LPCREATESTRUCT cs)override;
			void onDestroy(HWND hwnd)override;
			void onSize(HWND hwnd, UINT state, int cx, int cy)override;
			void onCommand(HWND hwnd, int id, HWND hwndctrl, UINT code_notify)override;

		public:
			bool GetOKFlag();
			int GetSelectedEncoding();
			std::string GetSelectedEncodingStr();
		};
	}
}