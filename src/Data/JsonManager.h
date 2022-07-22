#pragma once
#include <qjsondocument.h>
#include <qjsonobject.h>
#include <qjsonarray.h>
#include <qfile.h>
#include <vector>
#include <stdexcept>
#include <future>
#include "../../src/UI/ProblemWidget.h"

class JsonManager
{
public:
	JsonManager() = delete;
	static std::future<std::vector<ProblemWidgetData>> parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::future<std::vector<ProblemWidgetData>> getProblemListPage(std::string const& fileName) noexcept(false);
	static std::future<std::string> getProblemDescription(std::string const& fileName) noexcept(false);
	static std::future<size_t> getQuestionsCount(std::string const &fileName) noexcept(false);

private:
	static std::vector<ProblemWidgetData> _parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::vector<ProblemWidgetData> _getProblemListPage(std::string const &fileName) noexcept(false);
	static std::future<std::string> _getProblemDescription(std::string const& fileName) noexcept(false);
	static size_t _getQuestionsCount(std::string const &fileName) noexcept(false);
};

