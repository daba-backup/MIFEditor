#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class Button :public daxie::control::Control {
		public:
			Button(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~Button();
		};
	}
}