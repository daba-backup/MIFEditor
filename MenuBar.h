#pragma once

#include"Object.h"
#include"Menu.h"
#include<memory>
#include<Windows.h>

namespace daxie {
	namespace menu {
		class MenuBar :public daxie::Object {
		private:
			HWND hwnd;
			HMENU hmenu;

		public:
			MenuBar(HWND hwnd);
			virtual ~MenuBar();

		public:
			void Add(int index, std::unique_ptr<daxie::menu::Menu>& menu);
			void Add(int index, std::unique_ptr<daxie::menu::MenuItem>& item);

			void UpdateMenuBar();
		};
	}
}