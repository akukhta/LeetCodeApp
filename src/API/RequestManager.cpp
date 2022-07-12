#include "RequestManager.h"

std::string const RequestManager::allProblemsURL = "https://leetcode.com/_next/data/Ldb_Fcc-UKa_pLAqMwyAp/problemset/all.json";
std::string const RequestManager::csrfTokenFile = "csrf1";

RequestManager::RequestManager()
{
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

void RequestManager::executeRequest(std::string const& URL, std::string const &protocol, std::string const &type,
    std::string const& body, curl_slist* headers, FILE* out)
{
    auto fileName = generateFileName(); 

    fd = fopen(fileName.c_str(), "w");

    CURL *curl = curl_easy_init();
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

    if (out != nullptr)
    {
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, NULL);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, out);
    }

    curl_easy_perform(curl);
    curl_easy_cleanup(curl);

}

std::shared_ptr<RequestManager> RequestManager::getInstance()
{
    static std::shared_ptr<RequestManager> obj(new RequestManager());
    return obj;
}

std::tuple<std::future<void>, FILE*, std::string> RequestManager::getAllProblems()
{
    std::string fileName = generateFileName();
    FILE* fd = fopen(fileName.c_str(), "w");
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, std::string("Cookie: csrftoken=" + csrf).c_str());
    std::string body = "{\"query\":\"query allQuestionsRaw {\\r\\n  allQuestions: allQuestionsRaw {\\r\\n    title\\r\\n    titleSlug\\r\\n    translatedTitle\\r\\n    questionId\\r\\n    questionFrontendId\\r\\n    status\\r\\n    difficulty\\r\\n    isPaidOnly\\r\\n    categoryTitle\\r\\n    __typename\\r\\n  }\\r\\n}\\r\\n\",\"variables\":{}}";
    
    return std::make_tuple(std::async(std::launch::async,
        &RequestManager::executeRequest, this, url, protocol, type, body, headers, fd), fd, fileName);
}

std::tuple<std::future<void>, FILE*, std::string> RequestManager::getQuestionsCount() noexcept(false)
{
    std::string fileName = generateFileName();
    FILE* fd = fopen(fileName.c_str(), "w");
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, std::string("Cookie: csrftoken=" + csrf).c_str());
    std::string body = "{\"query\":\"query problemsetQuestionList {\\r\\n  problemsetQuestionList: questionList(\\r\\n    categorySlug: \\\"\\\"\\r\\n    limit: 50\\r\\n    skip: 1050\\r\\n    filters: {}\\r\\n  ) {\\r\\n    total: totalNum\\r\\n    questions: data {\\r\\n      acRate\\r\\n      difficulty\\r\\n      freqBar\\r\\n      frontendQuestionId: questionFrontendId\\r\\n      isFavor\\r\\n      paidOnly: isPaidOnly\\r\\n      status\\r\\n      title\\r\\n      titleSlug\\r\\n      topicTags {\\r\\n        name\\r\\n        id\\r\\n        slug\\r\\n      }\\r\\n      hasSolution\\r\\n      hasVideoSolution\\r\\n    }\\r\\n  }\\r\\n}\\r\\n    \",\"variables\":{}}";
    
    return std::make_tuple(std::async(std::launch::async,
        &RequestManager::executeRequest, this, url, protocol, type, body, headers, fd), fd, fileName);
}

void RequestManager::getCSRFToken()
{
    CURL* curl;
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
