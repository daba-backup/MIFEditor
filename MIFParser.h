#pragma once

#include"Object.h"
#include"TString.h"
#include"MissionInfo.h"

namespace daxie {
	namespace xops {
		class MIFParser :public daxie::Object {
		private:
			bool error_flag;
			daxie::tstring error_message;

			daxie::xops::MissionInfo mission_info;

		public:
			MIFParser(const daxie::tstring& filename,const std::string& encoding);
			virtual ~MIFParser();

		public:
			bool GetErrorFlag();
			daxie::tstring GetErrorMessage();

			daxie::xops::MissionInfo GetMissionInfo();
		};
	}
}