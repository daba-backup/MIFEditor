#pragma once

#include"Object.h"
#include"TString.h"
#include<Windows.h>
#include<array>

namespace daxie {
	namespace dialog {
		class CommonDialog :public daxie::Object {
		public:
			CommonDialog();
			virtual ~CommonDialog();

		public:
			virtual void SetHwndOwner(HWND hwnd) = 0;
			virtual void SetFlags(DWORD flags) = 0;

			//virtual BOOL Show() = 0;
		};

		class ChooseColorDialog :public CommonDialog {
		private:
			CHOOSECOLOR cc;
			std::array<COLORREF, 16> cust_colors;

		public:
			ChooseColorDialog();
			virtual ~ChooseColorDialog();

		public:
			void SetHwndOwner(HWND hwnd)override;
			void SetInitialColor(COLORREF color);
			void SetFlags(DWORD flags)override;

			BOOL Show();

			COLORREF GetSelectedColor();
		};

		class ChooseFontDialog :public CommonDialog {
		private:
			CHOOSEFONT cf;
			LOGFONT lf;

		public:
			ChooseFontDialog();
			virtual ~ChooseFontDialog();

		public:
			void SetHwndOwner(HWND hwnd)override;
			void SetFlags(DWORD flags)override;

			BOOL Show();

			LOGFONT GetSelectedFont();
		};

		class FileChooser :public CommonDialog {
		private:
			OPENFILENAME ofn;
			std::array<TCHAR, MAX_PATH> filename;
			std::array<TCHAR, 256> custom_filter;

		public:
			FileChooser();
			virtual ~FileChooser();

		protected:
			OPENFILENAME & GetOfn();

		public:
			void SetHwndOwner(HWND hwnd)override;
			void SetFilter(LPCTSTR filter);
			void SetFlags(DWORD flags)override;
			void SetDefaultExtension(const daxie::tstring& extension);

			BOOL ShowOpenDialog();
			BOOL ShowSaveDialog();

			daxie::tstring GetSelectedFilename();
		};
	}
}