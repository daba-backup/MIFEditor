#pragma once

#include"Object.h"
#include"TString.h"
#include<Windows.h>

namespace daxie {
	namespace tool {
		class WindowTool :public daxie::Object {
		public:
			static daxie::tstring GetWindowTextTString(HWND hwnd);
		};
	}
}