#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class RadioButtonBase :public daxie::control::Control {
		public:
			RadioButtonBase(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent,DWORD style);
			virtual ~RadioButtonBase();

		public:
			BOOL IsChecked();

			void Check();
			void Uncheck();
		};

		class HeadRadioButton :public RadioButtonBase {
		public:
			HeadRadioButton(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~HeadRadioButton();
		};

		class RadioButton :public RadioButtonBase {
		public:
			RadioButton(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~RadioButton();
		};
	}
}