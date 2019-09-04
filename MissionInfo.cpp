#include"MissionInfo.h"

daxie::xops::MissionInfo::MissionInfo() {
	mission_name.clear();
	mission_formal_name.clear();
	bd1_filename.clear();
	pd1_filename.clear();
	sky_type = 0;
	extra_hitcheck_flag = false;
	darken_screen_flag = false;
	article_info_filename.clear();
	image1_filename.clear();
	image2_filename.clear();
	briefing_text.clear();
}
daxie::xops::MissionInfo::~MissionInfo() {

}

void daxie::xops::MissionInfo::SetMissionName(const daxie::tstring& mission_name) {
	this->mission_name = mission_name;
}
void daxie::xops::MissionInfo::SetMissionFormalName(const daxie::tstring& mission_formal_name) {
	this->mission_formal_name = mission_formal_name;
}
void daxie::xops::MissionInfo::SetBD1Filename(const daxie::tstring& bd1_filename) {
	this->bd1_filename = bd1_filename;
}
void daxie::xops::MissionInfo::SetPD1Filename(const daxie::tstring& pd1_filename) {
	this->pd1_filename = pd1_filename;
}
void daxie::xops::MissionInfo::SetSkyType(int sky_type) {
	this->sky_type = sky_type;
}
void daxie::xops::MissionInfo::SetExtraHitcheckFlag(bool extra_hitcheck_flag) {
	this->extra_hitcheck_flag = extra_hitcheck_flag;
}
void daxie::xops::MissionInfo::SetDarkenScreenFlag(bool darken_screen_flag) {
	this->darken_screen_flag = darken_screen_flag;
}
void daxie::xops::MissionInfo::SetArticleInfoFilename(const daxie::tstring& article_info_filename) {
	this->article_info_filename = article_info_filename;
}
void daxie::xops::MissionInfo::SetImage1Filename(const daxie::tstring& image1_filename) {
	this->image1_filename = image1_filename;
}
void daxie::xops::MissionInfo::SetImage2Filename(const daxie::tstring& image2_filename) {
	this->image2_filename = image2_filename;
}
void daxie::xops::MissionInfo::SetBriefingText(const std::vector<daxie::tstring>& briefing_text) {
	this->briefing_text = briefing_text;
}
void daxie::xops::MissionInfo::AddLineToBriefingText(const daxie::tstring& line) {
	briefing_text.push_back(line);
}

daxie::tstring daxie::xops::MissionInfo::GetMissionName() {
	return mission_name;
}
daxie::tstring daxie::xops::MissionInfo::GetMissionFormalName() {
	return mission_formal_name;
}
daxie::tstring daxie::xops::MissionInfo::GetBD1Filename() {
	return bd1_filename;
}
daxie::tstring daxie::xops::MissionInfo::GetPD1Filename() {
	return pd1_filename;
}
int daxie::xops::MissionInfo::GetSkyType() {
	return sky_type;
}
bool daxie::xops::MissionInfo::GetExtraHitcheckFlag() {
	return extra_hitcheck_flag;
}
bool daxie::xops::MissionInfo::GetDarkenScreenFlag() {
	return darken_screen_flag;
}
daxie::tstring daxie::xops::MissionInfo::GetArticleInfoFilename() {
	return article_info_filename;
}
daxie::tstring daxie::xops::MissionInfo::GetImage1Filename() {
	return image1_filename;
}
daxie::tstring daxie::xops::MissionInfo::GetImage2Filename() {
	return image2_filename;
}
std::vector<daxie::tstring> daxie::xops::MissionInfo::GetBriefingText() {
	return briefing_text;
}