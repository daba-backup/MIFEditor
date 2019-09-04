#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class Static :public daxie::control::Control {
		public:
			Static(const daxie::tstring& text, int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~Static();
		};
	}
}