#pragma once

#include"Object.h"
#include"TString.h"

namespace daxie {
	namespace prg {
		class EmbeddedInfo :public daxie::Object {
		public:
			static const daxie::tstring PROGRAM_NAME;
			static const daxie::tstring RELEASE_DATE;
			static const daxie::tstring AUTHOR_NAME;
		};
	}
}