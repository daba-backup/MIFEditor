#pragma once

#include"MenuItem.h"
#include<memory>

namespace daxie {
	namespace menu {
		class Menu :public daxie::menu::MenuItem {
			friend class MenuBar;

		private:
			HMENU hmenu;

		public:
			Menu(const daxie::tstring& text);
			virtual ~Menu();

		public:
			void Add(int index, std::unique_ptr<daxie::menu::Menu>& menu);
			void Add(int index, std::unique_ptr<daxie::menu::MenuItem>& item);

			void AddSeparator(int index);
		};
	}
}