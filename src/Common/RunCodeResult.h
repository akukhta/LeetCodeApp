#pragma once
#include <string>
#include <algorithm>

#ifdef __cpp_lib_format
#include <format>
#else
#include <sstream>
#endif

class StringUtiles
{
public:
	StringUtiles() = delete;

	template <typename... Args>
	static std::string formatString(std::string const& format, Args&&... args)
	{
		return formatWrapper(format, args...);
	}

#ifdef __cpp_lib_format
	template <typename... Args>
	static std::string formatWrapper(std::string_view const& format, Args&&... args)
	{
		return std::vformat(format, std::make_format_args(args...));
	}
#else

	template <typename T>
	static void getByIndex(std::ostream& out, size_t neededIndex, size_t currentIndex, T arg)
	{
		if (neededIndex == currentIndex)
		{
			out << arg;
		}
		else
		{
			throw std::runtime_error("No argument with this index has been found");
		}
	}


	template <typename T, typename... Args>
	static void getByIndex(std::ostream& out, size_t neededIndex, size_t currentIndex, T arg, Args&&... args)
	{
		if (neededIndex == currentIndex)
		{
			out << arg;
		}
		else
		{
			getByIndex(out, neededIndex, currentIndex + 1, args...);
		}
	}

	template <typename... Args>
	static std::string parse(std::string s, Args&&... args)
	{
		std::stringstream ss;

		for (size_t i = 0; i < s.size(); i++)
		{
			if (s[i] == '}')
			{
				throw std::runtime_error("Incorrect format string");
			}

			if (s[i] != '{')
			{
				ss << s[i];
			}
			else
			{
				if (s[i + 1] != '{')
				{
					auto end = s.find('}', i);

					if (end == std::string::npos || s[end + 1] == '}')
					{
						throw std::runtime_error("Incorrect format string");
					}

					size_t index = std::stoi(s.substr(i + 1, end - i - 1));

					getByIndex(ss, index, 0, args...);

					i = end;
				}
				else
				{
					auto end = s.find("}}", i);

					auto strBetween = s.substr(i + 2, end - i - 2);

					if (end == std::string::npos || std::any_of(strBetween.begin(), strBetween.end(), [](auto x) {return x == '}' || x == '{'; }))
					{
						throw std::runtime_error("Incorrect format string");
					}

					ss << s.substr(i, end - i + 2);
					i = end + 1;
				}

			}
		}

		return ss.str();
	}

	template <typename... Args>
	static std::string formatWrapper(std::string_view const& format, Args&&... args)
	{
		std::string s(format.begin(), format.end());
		return parse(s, args...);
	}

#endif



	static std::string formatCodeString(std::string const& str)
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
			StringUtiles::formatString("{{\"question_id\": \"{0}\",\n\"data_input\": \"[2,7,11,15]\\n9\",\n\"lang\": \"{1}\",\n\"typed_code\": \"{2}\",\n\"judge_type\": \"small\"\n}}",
				questionID, lang, StringUtiles::formatCodeString(code));
		return result;
	}
};