#pragma once

#include"Object.h"

namespace daxie {
	namespace tool {
		class UniqueIDGenerator :public daxie::Object {
		private:
			static int count;

		public:
			static int GetNextID();
		};
	}
}