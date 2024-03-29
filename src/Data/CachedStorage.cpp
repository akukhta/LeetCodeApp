#include "CachedStorage.h"

std::shared_ptr<CachedStorage> CachedStorage::getInstance()
{
    static std::shared_ptr<CachedStorage> instance(new CachedStorage());
    return instance;
}

std::string CachedStorage::getFile(std::string const& url)
{
    if (auto file = cachedFiles.find(url); file != cachedFiles.end())
    {
        return file->second;
    }
    else
    {
        auto loadTask = RequestManager::getInstance()->getFile(url);
        loadTask.wait();

        auto r = cachedFiles.insert(std::make_pair(url, loadTask.get()));
        return r.first->second;
    }
}

void CachedStorage::loadUsersAvatar(std::string const& url, std::string const tag)
{
    auto loadTask = RequestManager::getInstance()->getFile(url);
    loadTask.wait();
    cachedFiles.insert(std::make_pair(tag, loadTask.get()));
    
}

std::string CachedStorage::getAvatarPath()
{
    return cachedFiles["avatar"];
}
