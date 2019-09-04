#pragma once

#include"Object.h"
#include"TString.h"
#include<string>

#define USE_ICU

#ifdef USE_ICU
namespace daxie {
	namespace encoding {
		class Encoding :public daxie::Object {
		public:
			static std::string Encode_TtoM(const daxie::tstring& src,
				const std::string& encoding_from, const std::string& encoding_to);
			static std::string Encode_MtoM(const std::string& src, 
				const std::string& encoding_from, const std::string& encoding_to);
		};
	}
}
#endif