#include<Windows.h>
#include<Shlwapi.h>
#include<tchar.h>
#include<memory>
#include"MainWindow.h"
#include"WCC.h"
#include"TStringFunctions.h"

#pragma comment(lib,"shlwapi")

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nShowCmd) {
	daxie::system::WCC::Initialize();
	
	auto main_window= std::make_unique<daxie::window::MainWindow>();
	main_window->DHCreateWindow(TEXT("MIFエディタ"));

	daxie::tstring filename(lpCmdLine);
	filename = daxie::TStringFunctions::get_string_in_between(filename, TEXT('\"'), TEXT('\"'));

	if (PathFileExists(filename.c_str()) == TRUE) {
		main_window->PublicLoadMIF(filename);
	}

	daxie::system::WCC::MsgLoop();

	return 0;
}
