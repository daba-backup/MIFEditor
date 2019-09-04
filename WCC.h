#pragma once

#include"Object.h"
#include<Windows.h>

namespace daxie {
	namespace system {
		class WCC :public daxie::Object {
		public:
			static BOOL Initialize();
			static void MsgLoop();
		};
	}
}