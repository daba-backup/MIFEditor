#include"MIFParser.h"
#include<fstream>
#include<string>
#include<vector>
#include"Encoding.h"
#include"TStringFunctions.h"

daxie::xops::MIFParser::MIFParser(const daxie::tstring& filename, const std::string& encoding) {
	error_flag = false;
	error_message = TEXT("エラーはありません。");

	//Get lines from the MIF file.
	std::ifstream file(filename);
	if (!file) {
		error_flag = true;
		error_message = TEXT("ファイルを開けません。");

		return;
	}

	std::vector<std::string> lines;

	std::string str;
	while (std::getline(file, str)) {
		lines.push_back(str);
	}

	file.close();

	if (lines.size() < 10) {
		error_flag = true;
		error_message = TEXT("MIFファイルの行数が少なすぎます。");

		return;
	}

	//Convert encoding.
	for (auto& line : lines) {
		line = daxie::encoding::Encoding::Encode_MtoM(line, encoding.c_str(), "UTF-8");
	}

	//Get mission information.
	daxie::tstring mission_name;
	daxie::tstring mission_formal_name;
	daxie::tstring bd1_filename;
	daxie::tstring pd1_filename;
	daxie::tstring str_sky_type;
	daxie::tstring str_flags;
	daxie::tstring article_info_filename;
	daxie::tstring image1_filename;
	daxie::tstring image2_filename;
	std::vector<daxie::tstring> briefing_text;

	mission_name = daxie::TStringFunctions::string_to_tstring(lines[0]);
	mission_formal_name = daxie::TStringFunctions::string_to_tstring(lines[1]);
	bd1_filename= daxie::TStringFunctions::string_to_tstring(lines[2]);
	pd1_filename = daxie::TStringFunctions::string_to_tstring(lines[3]);
	str_sky_type = daxie::TStringFunctions::string_to_tstring(lines[4]);
	str_flags = daxie::TStringFunctions::string_to_tstring(lines[5]);
	article_info_filename = daxie::TStringFunctions::string_to_tstring(lines[6]);
	image1_filename = daxie::TStringFunctions::string_to_tstring(lines[7]);
	image2_filename = daxie::TStringFunctions::string_to_tstring(lines[8]);
	briefing_text.clear();

	int lines_num = static_cast<int>(lines.size());
	for (int i = 9; i < lines_num; i++) {
		daxie::tstring line= daxie::TStringFunctions::string_to_tstring(lines[i]);
		briefing_text.push_back(line);
	}

	int sky_type;
	int flags;
	try {
		sky_type = std::stoi(str_sky_type);
		flags = std::stoi(str_flags);
	}
	catch (const std::invalid_argument&) {
		error_flag = true;
		error_message = TEXT("数値のフォーマットが不正です。");

		return;
	}
	catch (const std::out_of_range&) {
		error_flag = true;
		error_message = TEXT("範囲外の数値が含まれています。");

		return;
	}

	mission_info.SetMissionName(mission_name);
	mission_info.SetMissionFormalName(mission_formal_name);
	mission_info.SetBD1Filename(bd1_filename);
	mission_info.SetPD1Filename(pd1_filename);
	mission_info.SetSkyType(sky_type);

	if ((flags & 0b00000010) != 0)mission_info.SetDarkenScreenFlag(true);
	else mission_info.SetDarkenScreenFlag(false);
	if ((flags & 0b00000001) != 0)mission_info.SetExtraHitcheckFlag(true);
	else mission_info.SetExtraHitcheckFlag(false);

	mission_info.SetArticleInfoFilename(article_info_filename);
	mission_info.SetImage1Filename(image1_filename);
	mission_info.SetImage2Filename(image2_filename);
	mission_info.SetBriefingText(briefing_text);
}
daxie::xops::MIFParser::~MIFParser() {

}

bool daxie::xops::MIFParser::GetErrorFlag() {
	return error_flag;
}
daxie::tstring daxie::xops::MIFParser::GetErrorMessage() {
	return error_message;
}

daxie::xops::MissionInfo daxie::xops::MIFParser::GetMissionInfo() {
	return mission_info;
}