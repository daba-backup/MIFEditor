#pragma once

#include"Object.h"
#include"TString.h"
#include"MissionInfo.h"

namespace daxie {
	namespace xops {
		class MIFWriter :public daxie::Object {
		private:
			bool error_flag;
			daxie::tstring error_message;

			daxie::xops::MissionInfo mission_info;

		public:
			MIFWriter(const daxie::xops::MissionInfo& mission_info);
			virtual ~MIFWriter();

		public:
			bool GetErrorFlag();
			daxie::tstring GetErrorMessage();

			void Write(const daxie::tstring& filename,const std::string& encoding);
		};
	}
}