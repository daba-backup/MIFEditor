#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class TextArea :public daxie::control::Control {
		public:
			TextArea(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~TextArea();
		};
	}
}