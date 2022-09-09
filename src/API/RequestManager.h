#pragma once
#define _CURL_STATICLIB
#include <curl/curl.h>
#include <memory>
#include <string>
#include <chrono>
#include <random>
#include <future>
#include <fstream>
#include <filesystem>
#include <tuple>
#include <thread>
#include "../../src/Common/CookieHandler.h"
#include "../../src/Data/JsonManager.h"
#include "../../src/Common/RunCodeResult.h"

class RequestManager : public std::enable_shared_from_this<RequestManager>
{
private:
	RequestManager();
	std::string generateFileName() const;
	std::string executeRequest(std::string const& URL, std::string const& protocol = "https", std::string const& type = "GET",
		std::string const &body = "", curl_slist * headers = nullptr);
	std::random_device mutable rDevice;
	std::default_random_engine mutable randGenerator;
	std::uniform_int_distribution<int> mutable dist;
	FILE *fd;
	std::string static const allProblemsURL;
	void getCSRFToken(std::string const &url = "https://leetcode.com/");
	static std::string const csrfTokenFile;
	std::string csrf;
	std::vector<std::string> storedFiles;
	CURL* curl;
	void _runCode(std::unique_ptr<CodeToRun> code, std::function<void(std::unique_ptr<RunCodeResult>)> callback);

public:
	static std::shared_ptr<RequestManager> getInstance();
	std::future<std::string> getUserInfo() noexcept(false);
	std::future<std::string> getAllProblems() noexcept(false);
	std::future<std::string> getQuestionsCount() noexcept(false);
	std::future<std::string> getPage(size_t page) noexcept(false);
	std::future<std::string> getTasksDescription(std::string taskName) noexcept(false);
	std::future<std::string> getFile(std::string filePath) noexcept(false);

	void runCode(std::unique_ptr<CodeToRun> code, std::function<void(std::unique_ptr<RunCodeResult>)> callback);
	size_t const questionsPerPage = 50;
	~RequestManager();
};

