#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class Tab :public daxie::control::Control {
		public:
			Tab(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~Tab();

		public:
			void InsertItem(int index, const daxie::tstring& text);
			void SetCurrentSelection(int index);

			int GetCurrentSelection();
		};
	}
}