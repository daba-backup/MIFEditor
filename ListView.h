#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class ListView :public daxie::control::Control {
		public:
			ListView(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~ListView();

		public:
			void SetExtendedStyle(DWORD dw_style);

			void AddColumn(int column, int width, const daxie::tstring& text);
			void AddItem(int row, int column, const daxie::tstring& value);
			void AddItem(int row, int column, int value);
			void AddItem(int row, int column, float value, int digits);
		};
	}
}