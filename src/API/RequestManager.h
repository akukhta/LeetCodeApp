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

class RequestManager : public std::enable_shared_from_this<RequestManager>
{
private:
	RequestManager();
	std::string generateFileName() const;
	std::string executeRequest(std::string const& URL, std::string const& protocol = "https", std::string const& type = "GET",
		std::string const &body = "", curl_slist * headers = nullptr);
	//CURL *curl;
	std::random_device mutable rDevice;
	std::default_random_engine mutable randGenerator;
	std::uniform_int_distribution<int> mutable dist;
	FILE *fd;
	std::string static const allProblemsURL;
	void getCSRFToken();
	static std::string const csrfTokenFile;
	std::string csrf;

public:
	static std::shared_ptr<RequestManager> getInstance();
	std::future<std::string> getAllProblems() noexcept(false);
	std::future<std::string> getQuestionsCount() noexcept(false);
};

