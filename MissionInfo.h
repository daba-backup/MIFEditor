#pragma once

#include"Object.h"
#include"TString.h"
#include<vector>

namespace daxie {
	namespace xops {
		class MissionInfo final:public daxie::Object {
		private:
			daxie::tstring mission_name;
			daxie::tstring mission_formal_name;
			daxie::tstring bd1_filename;
			daxie::tstring pd1_filename;
			int sky_type;
			bool extra_hitcheck_flag;
			bool darken_screen_flag;
			daxie::tstring article_info_filename;
			daxie::tstring image1_filename;
			daxie::tstring image2_filename;
			std::vector<daxie::tstring> briefing_text;

		public:
			MissionInfo();
			~MissionInfo();

		public:
			void SetMissionName(const daxie::tstring& mission_name);
			void SetMissionFormalName(const daxie::tstring& mission_formal_name);
			void SetBD1Filename(const daxie::tstring& bd1_filename);
			void SetPD1Filename(const daxie::tstring& pd1_filename);
			void SetSkyType(int sky_type);
			void SetExtraHitcheckFlag(bool extra_hitcheck_flag);
			void SetDarkenScreenFlag(bool darken_screen_flag);
			void SetArticleInfoFilename(const daxie::tstring& article_info_filename);
			void SetImage1Filename(const daxie::tstring& image1_filename);
			void SetImage2Filename(const daxie::tstring& image2_filename);
			void SetBriefingText(const std::vector<daxie::tstring>& briefing_text);
			void AddLineToBriefingText(const daxie::tstring& line);

			daxie::tstring GetMissionName();
			daxie::tstring GetMissionFormalName();
			daxie::tstring GetBD1Filename();
			daxie::tstring GetPD1Filename();
			int GetSkyType();
			bool GetExtraHitcheckFlag();
			bool GetDarkenScreenFlag();
			daxie::tstring GetArticleInfoFilename();
			daxie::tstring GetImage1Filename();
			daxie::tstring GetImage2Filename();
			std::vector<daxie::tstring> GetBriefingText();
		};
	}
}