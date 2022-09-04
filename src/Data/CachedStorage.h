#pragma once
#include <memory>
#include <unordered_map>
#include "../../src/API/RequestManager.h"

class CachedStorage : public std::enable_shared_from_this<CachedStorage>
{
public:
	static std::shared_ptr<CachedStorage> getInstance();
	std::string getFile(std::string const& url);

private:
	CachedStorage() = default;
	
	//url-to-file -> path-to-local-file
	std::unordered_map<std::string, std::string> cachedFiles;

};

