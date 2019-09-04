#pragma once

#include"Control.h"

namespace daxie {
	namespace control {
		class ComboBoxBase :public daxie::control::Control {
		public:
			ComboBoxBase(int x, int y, int width, int height, HWND hwnd_parent,DWORD style);
			virtual ~ComboBoxBase();

		public:
			void AddItem(const daxie::tstring& item);
			void RemoveItem(int index);
			void SetCurrentSelection(int index);

			int GetCurrentSelection();
			int GetItemNum();
		};

		class SimpleComboBox :public ComboBoxBase {
		public:
			SimpleComboBox(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~SimpleComboBox();
		};

		class DropdownList :public ComboBoxBase {
		public:
			DropdownList(int x, int y, int width, int height, HWND hwnd_parent);
			virtual ~DropdownList();

		public:
			void ShowDropdown();
			void HideDropdown();
			BOOL IsDropped();
		};
	}
}