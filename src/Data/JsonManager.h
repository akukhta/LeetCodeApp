#pragma once
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include <vector>
#include <stdexcept>
#include <future>
#include <unordered_map>
#include "../../src/Common/ProblemWidgetData.h"

class JsonManager
{
public:
	JsonManager() = delete;
	static std::future<std::vector<ProblemWidgetData>> parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::future<std::vector<ProblemWidgetData>> getProblemListPage(std::string const& fileName) noexcept(false);
	static std::future<std::string> getProblemDescription(std::string const& fileName) noexcept(false);
	static std::future<size_t> getQuestionsCount(std::string const &fileName) noexcept(false);
	static std::future<std::unordered_map<std::string, std::string>> getCodeSnipsets(std::string const& fileName) noexcept(false);
	static std::future<std::string> getTestCase(std::string const& fileName) noexcept(false);
private:
	static std::vector<ProblemWidgetData> _parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::vector<ProblemWidgetData> _getProblemListPage(std::string const &fileName) noexcept(false);
	static std::string _getProblemDescription(std::string const& fileName) noexcept(false);
	static std::unordered_map<std::string, std::string> _getCodeSnipsets(std::string const& fileName) noexcept(false);
	static size_t _getQuestionsCount(std::string const &fileName) noexcept(false);
	static std::string _getTestCase(std::string const& fileName) noexcept(false);
};

