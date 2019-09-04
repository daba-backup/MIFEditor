#pragma once

#include"Object.h"
#include"TString.h"

namespace daxie {
	namespace menu {
		class MenuItem :public daxie::Object {
			friend class MenuBar;
			friend class Menu;

		private:
			daxie::tstring text;
			int id;

		public:
			MenuItem(const daxie::tstring& text);
			virtual ~MenuItem();

		public:
			BOOL IsThisMenuItem(int id);

		public:
			daxie::tstring GetText();
		};
	}
}