#pragma once
#include <string>
#include <format>
#include <algorithm>

class StringUtiles
{
public:
	StringUtiles() = delete;

	static std::string formatString(std::string const& str)
	{
		std::string res = str;

		for (size_t i = 0; i < res.size(); i++)
		{
			if (res[i] == '\t')
			{
				res[i] = ' ';
				res.insert(i + 1, "   ");
			}
			if (res[i] == '\n')
			{
				res[i] = '\\';
				res.insert(i + 1, "n");
			}
		}

		return res;
	}
};


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
			std::format("{{\"question_id\": \"{0}\",\n\"data_input\": \"[2,7,11,15]\\n9\",\n\"lang\": \"{1}\",\n\"typed_code\": \"{2}\",\n\"judge_type\": \"small\"\n}}",
				questionID, lang, StringUtiles::formatString(code));
		return result;
	}
};