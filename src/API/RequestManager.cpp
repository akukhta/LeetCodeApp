#include "RequestManager.h"

std::string const RequestManager::allProblemsURL = "https://leetcode.com/_next/data/Ldb_Fcc-UKa_pLAqMwyAp/problemset/all.json";
std::string const RequestManager::csrfTokenFile = "csrf1";

size_t write_data(void* ptr, size_t size, size_t nmemb, FILE* stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

RequestManager::RequestManager()
{
    curl_global_init(CURL_GLOBAL_DEFAULT);
    getCSRFToken();
    randGenerator = std::default_random_engine(rDevice());
    dist = std::uniform_int_distribution<int>(INT_MIN + 1, INT_MAX - 1);
}

std::string RequestManager::generateFileName() const
{
    int seed = dist(randGenerator);
    std::string fileName = std::to_string(std::hash<std::string>()(std::to_string(seed)));
    return fileName;
}

std::string RequestManager::executeRequest(std::string const& URL, std::string const &protocol, std::string const &type,
    std::string const& body, curl_slist* headers)
{
    auto fileName = generateFileName(); 

    fd = fopen(fileName.c_str(), "wb");

    if (fd == nullptr)
    {
        throw std::runtime_error("Can`t open the file to write the request's answer");
    }

    curl = curl_easy_init();

    if (curl == nullptr)
    {
        throw std::runtime_error("Can`t init curl instance");
    }

    curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, type.c_str());
    curl_easy_setopt(curl, CURLOPT_URL, URL.c_str());
    curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, protocol.c_str());
    
    if (headers != nullptr)
    {
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
    }

    if (body != "")
    {
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, body.c_str());
    }

    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fd);

    curl_easy_perform(curl);
    int code;
    curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &code);
    curl_easy_cleanup(curl);

    fclose(fd);
    storedFiles.push_back(fileName);
    
    return fileName;
}

std::shared_ptr<RequestManager> RequestManager::getInstance()
{
    static std::shared_ptr<RequestManager> obj(new RequestManager());
    return obj;
}

std::future<std::string> RequestManager::getAllProblems()
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, std::string("Cookie: csrftoken=" + csrf).c_str());
    std::string body = "{\"query\":\"query allQuestionsRaw {\\r\\n  allQuestions: allQuestionsRaw {\\r\\n    title\\r\\n    titleSlug\\r\\n    translatedTitle\\r\\n    questionId\\r\\n    questionFrontendId\\r\\n    status\\r\\n    difficulty\\r\\n    isPaidOnly\\r\\n    categoryTitle\\r\\n    __typename\\r\\n  }\\r\\n}\\r\\n\",\"variables\":{}}";
    
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers);});
}

std::future<std::string> RequestManager::getQuestionsCount() noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, std::string("Cookie: csrftoken=" + csrf).c_str());
    std::string body = "{\"query\":\"query problemsetQuestionList {\\r\\n  problemsetQuestionList: questionList(\\r\\n    categorySlug: \\\"\\\"\\r\\n    limit: 50\\r\\n    skip: 0\\r\\n    filters: {}\\r\\n  ) {\\r\\n    total: totalNum\\r\\n    questions: data {\\r\\n      acRate\\r\\n      difficulty\\r\\n      freqBar\\r\\n      frontendQuestionId: questionFrontendId\\r\\n      isFavor\\r\\n      paidOnly: isPaidOnly\\r\\n      status\\r\\n      title\\r\\n      titleSlug\\r\\n      topicTags {\\r\\n        name\\r\\n        id\\r\\n        slug\\r\\n      }\\r\\n      hasSolution\\r\\n      hasVideoSolution\\r\\n    }\\r\\n  }\\r\\n}\\r\\n    \",\"variables\":{}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getPage(size_t page) noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, std::string("Cookie: csrftoken=" + csrf).c_str());
    std::string body = "{\"query\":\"query problemsetQuestionList {\\r\\n  problemsetQuestionList: questionList(\\r\\n    categorySlug: \\\"\\\"\\r\\n    limit:" + std::to_string(questionsPerPage) + "\\r\\n    skip : " + std::to_string((page - 1) * questionsPerPage)+ "\\r\\n    filters : {}\\r\\n  ) {\\r\\n    total : totalNum\\r\\n    questions : data{\\r\\n      acRate\\r\\n      difficulty\\r\\n      freqBar\\r\\n      frontendQuestionId : questionFrontendId\\r\\n      isFavor\\r\\n      paidOnly : isPaidOnly\\r\\n      status\\r\\n      title\\r\\n      titleSlug\\r\\n      topicTags {\\r\\n        name\\r\\n        id\\r\\n        slug\\r\\n}\\r\\n      hasSolution\\r\\n      hasVideoSolution\\r\\n}\\r\\n  }\\r\\n }\\r\\n    \",\"variables\":{}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

RequestManager::~RequestManager()
{
    for (auto& file : storedFiles)
    {
        std::filesystem::remove(file);
    }
}

void RequestManager::getCSRFToken()
{
    CURLcode res;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, "https://leetcode.com/");
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, true);
        curl_easy_setopt(curl, CURLOPT_DEFAULT_PROTOCOL, "https");
        curl_easy_setopt(curl, CURLOPT_COOKIEJAR, csrfTokenFile.c_str());
        curl_easy_setopt(curl, CURLOPT_COOKIEFILE, csrfTokenFile.c_str());
        res = curl_easy_perform(curl);
    }
    curl_easy_cleanup(curl);

    std::ifstream in(csrfTokenFile);
    std::string tmp = "";

    while (tmp != "csrftoken")
    {
        in >> tmp;
    }

    in >> csrf;
    in.close();

    std::filesystem::remove(csrfTokenFile);
}
