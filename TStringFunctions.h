#pragma once

#include"Object.h"
#include"TString.h"
#include<vector>

namespace daxie {
	class TStringFunctions :public Object {
	public:
		static daxie::tstring to_string(int value);
		static daxie::tstring to_string(float value);
		static daxie::tstring to_string(float value, int digits);

		static daxie::tstring string_to_tstring(const std::string& src);
		static std::string tstring_to_string(const daxie::tstring& src);

		static std::vector<daxie::tstring> split(const daxie::tstring& str,const daxie::tstring& separator);

		static daxie::tstring get_string_in_between(const daxie::tstring& str, TCHAR c1, TCHAR c2);
	};
}