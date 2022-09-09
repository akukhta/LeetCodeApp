#pragma once
#include <memory>
#include <unordered_map>
#include <fstream>

class CookieHandler : public std::enable_shared_from_this<CookieHandler>
{
private:
	CookieHandler() = default;
	std::unordered_map<std::string, std::string> cookies;

public:
	static std::shared_ptr<CookieHandler> getInstance()
	{
		static std::shared_ptr<CookieHandler> handler(new CookieHandler());
		return handler;
	}

	std::string& operator[] (std::string const& key)
	{
		return cookies[key];
	}

	// Load and parse cookies in "key=value\n" format
	void loadCookiesFromFile(std::string const& filePath)
	{

		std::ifstream in(filePath);

		if (!in.is_open())
		{
			throw std::runtime_error("Can`t open cookies' file!");
		}

		std::string line;

		while (in >> line)
		{
			size_t sepPos = line.find("=");

			if (sepPos == std::string::npos)
			{
				continue;
			}

			std::string key = line.substr(0, sepPos);
			std::string value = line.substr(sepPos + 1);
			
			cookies[key] = value;
		}

		in.close();
	}

	std::string generateCookieString() const
	{
		std::string cookieStr = "cookie: ";

		for (auto const& cookie : cookies)
		{
			cookieStr += cookie.first + "=" + cookie.second + "; ";
		}

		cookieStr.resize(cookieStr.length() - 2);
		return cookieStr;
	}

	bool isLogged() const
	{
		return cookies.find("LEETCODE_SESSION") != cookies.end();
	}
};
