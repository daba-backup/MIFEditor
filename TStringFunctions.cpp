#include"TStringFunctions.h"
#include<iomanip>
#include<sstream>
#include<string>

daxie::tstring daxie::TStringFunctions::to_string(int value) {
	daxie::tstring ret;

#ifdef UNICODE
	ret = std::to_wstring(value);
#else
	ret = std::to_string(value);
#endif

	return ret;
}
daxie::tstring daxie::TStringFunctions::to_string(float value) {
	daxie::tstring ret;

#ifdef UNICODE
	ret = std::to_wstring(value);
#else
	ret = std::to_string(value);
#endif

	return ret;
}
daxie::tstring daxie::TStringFunctions::to_string(float value, int digits) {
	daxie::tstring ret;

	std::string temp;
	std::ostringstream oss;

	oss << std::fixed << std::setprecision(digits) << value;
	temp = oss.str();

	ret = TStringFunctions::string_to_tstring(temp);

	return ret;
}

daxie::tstring daxie::TStringFunctions::string_to_tstring(const std::string& src) {
	daxie::tstring ret;

#ifdef UNICODE
	auto const dst_size = ::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, nullptr, 0U);
	std::vector<wchar_t> dst(dst_size, TEXT('\0'));

	if (::MultiByteToWideChar(CP_UTF8, 0U, src.data(), -1, dst.data(), static_cast<int>(dst.size())) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()),std::system_category() };
	}

	dst.resize(std::char_traits<wchar_t>::length(dst.data()));
	dst.shrink_to_fit();

	ret.assign(dst.begin(), dst.end());

#else
	ret = src;
#endif

	return ret;
}
std::string daxie::TStringFunctions::tstring_to_string(const daxie::tstring& src) {
	std::string ret;

#ifdef UNICODE
	auto const dst_size = ::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, nullptr, 0U, nullptr, nullptr);
	std::vector<char> dst(dst_size, '\0');

	if (::WideCharToMultiByte(CP_UTF8, 0U, src.data(), -1, dst.data(), static_cast<int>(dst.size()), nullptr, nullptr) == 0) {
		throw std::system_error{ static_cast<int>(::GetLastError()),std::system_category() };
	}

	dst.resize(std::char_traits<char>::length(dst.data()));
	dst.shrink_to_fit();

	ret.assign(dst.begin(), dst.end());

#else
	ret = src;
#endif

	return ret;
}

std::vector<daxie::tstring> daxie::TStringFunctions::split(const daxie::tstring& str,const daxie::tstring& separator) {
	std::vector<daxie::tstring> ret;

	auto separator_length = separator.length();

	if (separator_length == 0) {
		ret.push_back(str);
	}
	else {
		auto offset = std::string::size_type(0);

		while (1) {
			auto pos = str.find(separator, offset);
			if (pos == std::string::npos) {
				ret.push_back(str.substr(offset));
				break;
			}

			ret.push_back(str.substr(offset, pos - offset));
			offset = pos + separator_length;
		}
	}

	return ret;
}

daxie::tstring daxie::TStringFunctions::get_string_in_between(const daxie::tstring& str, TCHAR c1, TCHAR c2) {
	auto first_pos = str.find_first_of(c1);
	auto last_pos = str.find_last_of(c2);

	if (first_pos == std::string::npos || last_pos == std::string::npos) {
		return str;
	}
	if (first_pos >= last_pos) {
		return str;
	}

	daxie::tstring ret;
	ret = str.substr(first_pos+1, last_pos - first_pos-1);

	return ret;
}