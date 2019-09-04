#include"Encoding.h"
#include<vector>
#include"TStringFunctions.h"

#ifdef USE_ICU

#include<unicode/ucnv.h>
#include<unicode/unistr.h>

#pragma comment(lib, "icuuc.lib")

std::string daxie::encoding::Encoding::Encode_TtoM(
	const daxie::tstring& src, const std::string& encoding_from,const std::string& encoding_to) {
	std::string dst;
	std::string str_src = daxie::TStringFunctions::tstring_to_string(src);

	dst = daxie::encoding::Encoding::Encode_MtoM(str_src, encoding_from, encoding_to);

	return dst;
}
std::string daxie::encoding::Encoding::Encode_MtoM(
	const std::string& src, const std::string& encoding_from,const std::string& encoding_to) {
	std::string dst;

	const icu::UnicodeString ustr(src.c_str(), encoding_from.c_str());
	const int32_t length = ustr.extract(0, ustr.length(), nullptr, encoding_to.c_str());

	if (length > 0) {
		std::vector<char> buf(length+1);

		ustr.extract(0, ustr.length(), &buf[0], encoding_to.c_str());
		dst.assign(buf.begin(), buf.end());

		dst.pop_back();
	}
	else {
		dst.clear();
	}

	return dst;
}

#endif