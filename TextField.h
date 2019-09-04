#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class TextField :public daxie::control::Control {
		public:
			TextField(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~TextField();
		};
	}
}