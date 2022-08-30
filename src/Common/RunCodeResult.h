#pragma once
#include <string>
#include <format>

struct RunCodeResult
{
	std::string statusRuntime;
	std::string statusMemory;
	std::string statusMsg;
};

struct CodeToRun
{
	size_t questionID;
	std::string dataInput;
	std::string lang;
	std::string code;
	std::string titleSlug;

	std::string getString()
	{
		std::string result = 
			std::format("{{\"question_id\":\" {0} \",\"data_input\":\" {1} \",\"lang\":\" {2} \",\"typed_code\":\" {3} \",\"judge_type\":\"small\"}}",
			questionID, dataInput, lang, code);
		return result;
	}
};