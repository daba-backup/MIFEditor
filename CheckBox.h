#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class CheckBox :public daxie::control::Control {
		public:
			CheckBox(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~CheckBox();

		public:
			BOOL IsChecked();

			void Check();
			void Uncheck();
		};
	}
}