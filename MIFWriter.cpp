#include"MIFWriter.h"
#include<fstream>
#include<vector>
#include"Encoding.h"
#include"TStringFunctions.h"

daxie::xops::MIFWriter::MIFWriter(const daxie::xops::MissionInfo& mission_info) {
	error_flag = false;
	error_message = TEXT("エラーはありません。");

	this->mission_info = mission_info;
}
daxie::xops::MIFWriter::~MIFWriter() {

}

bool daxie::xops::MIFWriter::GetErrorFlag() {
	return error_flag;
}
daxie::tstring daxie::xops::MIFWriter::GetErrorMessage() {
	return error_message;
}

void daxie::xops::MIFWriter::Write(const daxie::tstring& filename, const std::string& encoding) {
	//Make a vector of lines to be output in a MIF file.
	std::vector<daxie::tstring> t_lines;
	std::vector<std::string> lines;

	t_lines.push_back(mission_info.GetMissionName());
	t_lines.push_back(mission_info.GetMissionFormalName());
	t_lines.push_back(mission_info.GetBD1Filename());
	t_lines.push_back(mission_info.GetPD1Filename());

	int sky_type = mission_info.GetSkyType();
	t_lines.push_back(daxie::TStringFunctions::to_string(sky_type));

	int flags = 0;
	if (mission_info.GetExtraHitcheckFlag() == true)flags = flags | 0b00000001;
	if (mission_info.GetDarkenScreenFlag() == true)flags = flags | 0b00000010;
	t_lines.push_back(daxie::TStringFunctions::to_string(flags));

	t_lines.push_back(mission_info.GetArticleInfoFilename());
	t_lines.push_back(mission_info.GetImage1Filename());
	t_lines.push_back(mission_info.GetImage2Filename());

	auto briefing_text=mission_info.GetBriefingText();
	for (auto& line : briefing_text) {
		t_lines.push_back(line);
	}

	//Convert lines to std::string.
	for (auto& t_line : t_lines) {
		lines.push_back(daxie::TStringFunctions::tstring_to_string(t_line));
	}

	//Convert encoding.
	for (auto& line : lines) {
		line = daxie::encoding::Encoding::Encode_MtoM(line, "UTF-8", encoding.c_str());
	}

	//Write lines in a MIF file.
	std::ofstream file(filename);
	if (!file) {
		error_flag = true;
		error_message = TEXT("ファイルを開けません。");

		return;
	}

	for (auto& line : lines) {
		file << line << std::endl;
	}
}