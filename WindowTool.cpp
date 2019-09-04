#include"WindowTool.h"
#include<memory>

daxie::tstring daxie::tool::WindowTool::GetWindowTextTString(HWND hwnd) {
	int text_length = GetWindowTextLength(hwnd);
	std::unique_ptr<TCHAR[]> buffer = std::make_unique<TCHAR[]>(text_length + 1);

	GetWindowText(hwnd, buffer.get(), text_length + 1);

	daxie::tstring ret = TEXT("");
	for (int i = 0; i < text_length; i++) {
		ret.push_back(buffer[i]);
	}

	return ret;
}