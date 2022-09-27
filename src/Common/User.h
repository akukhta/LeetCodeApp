#pragma once
#include <memory>
#include <string>
#include <array>


struct UserDetails
{
	long long rank;
	std::string realName;
	std::string githubUrl;
}; 

struct TasksStat
{
	enum difficulty : short {ALL, EASY, MEDIUM, HARD};
	std::array<std::pair<size_t, size_t>, 4> questions;
	std::array<float, 3> beats;
};

class User : public std::enable_shared_from_this<User>
{
private:
	User()
	{
		isLogged = false;
		username = "Guest";
		avatarPath = "";
	}

	//User(User const&) = delete;

public:
	static std::shared_ptr<User> getInstance()
	{
		static std::shared_ptr<User> instance(new User());
		return instance;
	}

	void setUserInfo(std::string const& username, std::string const &avatarPath)
	{
		isLogged = true;
		this->username = username;
		this->avatarPath = avatarPath;
	}

	bool isLogged;
	std::string username;
	std::string avatarPath;
};