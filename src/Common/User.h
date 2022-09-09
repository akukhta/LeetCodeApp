#pragma once
#include <memory>
#include <string>
#include "../../src/Data/CachedStorage.h"

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

	void setUserInfo(std::string const& username)
	{
		isLogged = true;
		this->username = username;
		this->avatarPath = CachedStorage::getInstance()->getAvatarPath();
	}

	bool isLogged;
	std::string username;
	std::string avatarPath;
};