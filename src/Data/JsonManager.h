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
#include "../../src/Common/RunCodeResult.h"

class JsonManager
{
public:
	JsonManager() = delete;
	static std::future<std::string> getAvatarPath(std::string const& fileName) noexcept(false);
	static std::future<std::string> getUsername(std::string const& fileName) noexcept(false);
	static std::future<std::string> getTitleSlug(std::string const& fileName) noexcept(false);
	static std::future<size_t> getQuestionID(std::string const& fileName) noexcept(false);
	static std::future<std::vector<ProblemWidgetData>> parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::future<std::vector<ProblemWidgetData>> getProblemListPage(std::string const& fileName) noexcept(false);
	static std::future<std::string> getProblemDescription(std::string const& fileName) noexcept(false);
	static std::future<size_t> getQuestionsCount(std::string const &fileName) noexcept(false);
	static std::future<std::unordered_map<std::string, std::pair<std::string, std::string>>> getCodeSnipsets(std::string const& fileName) noexcept(false);
	static std::future<std::string> getTestCase(std::string const& fileName) noexcept(false);
	static std::future<std::string> getInterpretID(std::string const& fileName) noexcept(false);
	static std::future<std::string> getStatus(std::string const& fileName) noexcept(false);
	static std::future<std::unique_ptr<RunCodeResult>> getRunCodeResult(std::string const& fileName) noexcept (false);

private:
	static std::string _getAvatarPath(std::string const& fileName) noexcept(false);
	static std::string _getUsername(std::string const& fileName) noexcept(false);
	static std::string _getTitleSlug(std::string const& fileName) noexcept(false);
	static size_t _getQuestionID(std::string const& fileName) noexcept(false);
	static std::vector<ProblemWidgetData> _parseProblemsFromJson(std::string const &fileName) noexcept(false);
	static std::vector<ProblemWidgetData> _getProblemListPage(std::string const &fileName) noexcept(false);
	static std::string _getProblemDescription(std::string const& fileName) noexcept(false);
	static std::unordered_map<std::string, std::pair<std::string, std::string>> _getCodeSnipsets(std::string const& fileName) noexcept(false);
	static size_t _getQuestionsCount(std::string const &fileName) noexcept(false);
	static std::string _getTestCase(std::string const& fileName) noexcept(false);
	static std::string _getInterpretID(std::string const& fileName) noexcept(false);
	static std::string _getStatus(std::string const& fileName) noexcept(false);
	static std::unique_ptr<RunCodeResult> _getRunCodeResult(std::string const& fileName) noexcept (false);
};

