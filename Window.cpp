#include"Window.h"
#include<windowsx.h>
#include"WindowTool.h"

HINSTANCE daxie::window::Window::hinstance = NULL;
daxie::window::Window* daxie::window::Window::p_this = NULL;
const daxie::tstring daxie::window::Window::WINDOW_CLASS_NAME = TEXT("WINDOW");

daxie::window::Window::Window() :hwnd(NULL),window_destroyed_flag(false) {

}
daxie::window::Window::~Window() {

}

BOOL daxie::window::Window::DHRegisterWindowClass() {
	hinstance = GetModuleHandle(NULL);

	WNDCLASSEX wincx;

	wincx.cbSize = sizeof(WNDCLASSEX);
	wincx.style = CS_HREDRAW | CS_VREDRAW;
	wincx.lpfnWndProc = WndProcMgr;
	wincx.cbClsExtra = 0;
	wincx.cbWndExtra = 0;
	wincx.hInstance = hinstance;
	wincx.hIcon = static_cast<HICON>(LoadImage(hinstance, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED));
	wincx.hCursor = static_cast<HCURSOR>(LoadImage(NULL, IDC_ARROW, IMAGE_CURSOR, 0, 0, LR_SHARED));
	wincx.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
	wincx.lpszMenuName = NULL;
	wincx.lpszClassName = WINDOW_CLASS_NAME.c_str();
	wincx.hIconSm = static_cast<HICON>(LoadImage(NULL, IDI_APPLICATION, IMAGE_ICON, 0, 0, LR_SHARED));

	if (!RegisterClassEx(&wincx))return FALSE;
	return TRUE;
}
BOOL daxie::window::Window::DHCreateWindow(const daxie::tstring& title, int x, int y, int width, int height,
	HWND hwnd_parent, HMENU hmenu, const daxie::tstring& class_name, DWORD style, DWORD ex_style) {
	p_this = this;

	hwnd = CreateWindowEx(ex_style, class_name.c_str(), title.c_str(), style,
		x, y, width, height, hwnd_parent, hmenu, hinstance, this);
	if (hwnd == NULL)return FALSE;
	return TRUE;
}

LRESULT CALLBACK daxie::window::Window::WndProcMgr(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	daxie::window::Window* window = reinterpret_cast<daxie::window::Window*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

	if (window != NULL) {
		LRESULT lresult = window->WndProc(hwnd, msg, wParam, lParam);
		return lresult;
	}
	else {
		if (msg == WM_CREATE || msg == WM_INITDIALOG) {
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(p_this));
			SendMessage(hwnd, msg, wParam, lParam);
			p_this = NULL;
		}
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}
LRESULT CALLBACK daxie::window::Window::WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
	switch (msg) {
		HANDLE_MSG(hwnd, WM_CREATE, onCreate);
		HANDLE_MSG(hwnd, WM_DESTROY, onDestroy);
		HANDLE_MSG(hwnd, WM_CLOSE, onClose);
		HANDLE_MSG(hwnd, WM_PAINT, onPaint);
		HANDLE_MSG(hwnd, WM_SIZE, onSize);
		HANDLE_MSG(hwnd, WM_TIMER, onTimer);
		HANDLE_MSG(hwnd, WM_COMMAND, onCommand);
		HANDLE_MSG(hwnd, WM_CHAR, onChar);
		HANDLE_MSG(hwnd, WM_LBUTTONDOWN, onLButtonDown);
		HANDLE_MSG(hwnd, WM_RBUTTONDOWN, onRButtonDown);
		HANDLE_MSG(hwnd, WM_MBUTTONDOWN, onMButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONDBLCLK, onLButtonDown);
		HANDLE_MSG(hwnd, WM_RBUTTONDBLCLK, onRButtonDown);
		HANDLE_MSG(hwnd, WM_LBUTTONUP, onLButtonUp);
		HANDLE_MSG(hwnd, WM_RBUTTONUP, onRButtonUp);
		HANDLE_MSG(hwnd, WM_MBUTTONUP, onMButtonUp);
		HANDLE_MSG(hwnd, WM_MOUSEMOVE, onMouseMove);
		HANDLE_MSG(hwnd, WM_MOUSEWHEEL, onMouseWheel);
		HANDLE_MSG(hwnd, WM_DROPFILES, onDropFiles);
	}

	return DefWindowProc(hwnd, msg, wParam, lParam);
}

HWND daxie::window::Window::GetHwnd() {
	return hwnd;
}

BOOL daxie::window::Window::onCreate(HWND hwnd, LPCREATESTRUCT cs) {
	this->hwnd = hwnd;
	return TRUE;
}
void daxie::window::Window::onDestroy(HWND hwnd) {
	//PostQuitMessage(0);
	window_destroyed_flag = true;
}
LRESULT daxie::window::Window::onClose(HWND hwnd) {
	return DefWindowProc(hwnd, WM_CLOSE, 0, 0);
}
void daxie::window::Window::onPaint(HWND hwnd) {
	PAINTSTRUCT ps;
	HDC hdc = BeginPaint(hwnd, &ps);
	EndPaint(hwnd, &ps);
}
void daxie::window::Window::onSize(HWND hwnd, UINT state, int cx, int cy) {

}
void daxie::window::Window::onTimer(HWND hwnd, UINT id) {

}
void daxie::window::Window::onCommand(HWND hwnd, int id, HWND hwndctrl, UINT code_notify) {

}
void daxie::window::Window::onChar(HWND hwnd, TCHAR ch, int c_repeat) {

}
void daxie::window::Window::onLButtonDown(HWND hwnd, BOOL is_double_click, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onRButtonDown(HWND hwnd, BOOL is_double_click, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onMButtonDown(HWND hwnd, BOOL is_double_click, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onLButtonUp(HWND hwnd, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onRButtonUp(HWND hwnd, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onMButtonUp(HWND hwnd, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onMouseMove(HWND hwnd, int x, int y, UINT key_flags) {

}
void daxie::window::Window::onMouseWheel(HWND hwnd, int x, int y, int z_delta, UINT fw_keys) {

}
void daxie::window::Window::onDropFiles(HWND hwnd, HDROP hdrop) {

}

void daxie::window::Window::DHSetWindowText(const daxie::tstring& text) {
	SetWindowText(hwnd, text.c_str());
}
void daxie::window::Window::CloseWindow() {
	SendMessage(hwnd, WM_CLOSE, 0, 0);
}
void daxie::window::Window::AppendWindowStyle(LONG_PTR style) {
	LONG_PTR cur_style = GetWindowLongPtr(hwnd, GWL_STYLE);
	SetWindowLongPtr(hwnd, GWL_STYLE, cur_style | style);
}
void daxie::window::Window::RemoveWindowStyle(LONG_PTR style) {
	LONG_PTR cur_style = GetWindowLongPtr(hwnd, GWL_STYLE);
	SetWindowLongPtr(hwnd, GWL_STYLE, cur_style &~style);
}
void daxie::window::Window::DHMoveWindow(int x, int y, int width, int height) {
	MoveWindow(hwnd, x, y, width, height, TRUE);
}
void daxie::window::Window::DHDragAcceptFiles(bool accept_flag) {
	if (accept_flag == true)DragAcceptFiles(hwnd, TRUE);
	else DragAcceptFiles(hwnd, FALSE);
}

daxie::tstring daxie::window::Window::DHGetWindowText() {
	daxie::tstring text = daxie::tool::WindowTool::GetWindowTextTString(hwnd);

	return text;
}
bool daxie::window::Window::IsDestroyed() {
	return window_destroyed_flag;
}
POINT daxie::window::Window::GetWindowPos() {
	RECT rect;
	POINT pt;

	GetWindowRect(hwnd, &rect);
	pt.x = rect.left;
	pt.y = rect.top;

	return pt;
}
POINT daxie::window::Window::GetWindowSize() {
	RECT rect;
	POINT pt;

	GetClientRect(hwnd, &rect);
	pt.x = rect.right;
	pt.y = rect.bottom;

	return pt;
}
