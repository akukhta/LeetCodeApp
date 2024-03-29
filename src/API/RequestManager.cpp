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

void RequestManager::_runCode(std::unique_ptr<CodeToRun> code, std::function<void(std::unique_ptr<RunCodeResult>)> callback, bool isSubmited)
{
    std::string protocol = "https";
    std::string url = StringUtiles::formatString("https://leetcode.com/problems/{}/{}/", code->titleSlug, isSubmited ? "submit" : "interpret_solution");
    std::string type = "POST";
    auto referer = StringUtiles::formatString("referer: https://leetcode.com/problems/{}/submissions/", code->titleSlug);

    auto cookies = CookieHandler::getInstance()->generateCookieString();
    auto xcsrf = StringUtiles::formatString("x-csrftoken: {}", (*CookieHandler::getInstance())["csrftoken"]);
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, cookies.c_str());
    headers = curl_slist_append(headers, referer.c_str());
    headers = curl_slist_append(headers, xcsrf.c_str());
    std::string body = code->getString();
    auto fileName = executeRequest(url, protocol, type, body, headers);
    auto interpretIdTask = JsonManager::getInterpretID(fileName, isSubmited);
    std::string interpretId;
    auto r = interpretIdTask.get();
    
    if (std::holds_alternative<std::string>(r))
    {
        interpretId = std::get<std::string>(r);
    }
    else
    {
        interpretId = std::to_string(std::get<size_t>(r));
    }

    std::string status;

    std::string checkUrl = StringUtiles::formatString("https://leetcode.com/submissions/detail/{}/check/", interpretId);
    std::string checkType = "GET";
    struct curl_slist* checkHeaders = NULL;
    checkHeaders = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string checkFileName;

    do
    {
        checkFileName = executeRequest(checkUrl, protocol, checkType, "", checkHeaders);
        auto checkTask = JsonManager::getStatus(checkFileName);
        checkTask.wait();
        status = checkTask.get();

    } while (status == "STARTED" || status == "PENDING");

    if (status == "SUCCESS")
    {
        auto resultTask = JsonManager::getRunCodeResult(checkFileName);
        resultTask.wait();
        callback(resultTask.get());
    }
}

std::shared_ptr<RequestManager> RequestManager::getInstance()
{
    static std::shared_ptr<RequestManager> obj(new RequestManager());
    return obj;
}

std::future<std::string> RequestManager::getUserInfo() noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    std::string referer = "https://leetcode.com/problemset/all/";
    auto xcsrf = StringUtiles::formatString("x-csrftoken: {}", (*CookieHandler::getInstance())["csrftoken"]);
    
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, ("referer: " + referer).c_str());
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    headers = curl_slist_append(headers, xcsrf.c_str());
    std::string body = "{\"query\":\"\\n    query globalData {\\n  userStatus {\\n    userId\\n    isSignedIn\\n    isMockUser\\n    isPremium\\n    isVerified\\n    username\\n    avatar\\n    isAdmin\\n    isSuperuser\\n    permissions\\n    isTranslator\\n    activeSessionId\\n    notificationStatus {\\n      lastModified\\n      numUnread\\n    }\\n  }\\n}\\n    \",\"variables\":{}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getAllProblems()
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string body = "{\"query\":\"query allQuestionsRaw {\\r\\n  allQuestions: allQuestionsRaw {\\r\\n    title\\r\\n    titleSlug\\r\\n    translatedTitle\\r\\n    questionId\\r\\n    questionFrontendId\\r\\n    status\\r\\n    difficulty\\r\\n    isPaidOnly\\r\\n    categoryTitle\\r\\n    __typename\\r\\n  }\\r\\n}\\r\\n\",\"variables\":{}}";
    
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers);});
}

std::future<std::string> RequestManager::getQuestionsCount(std::string const& filters) noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string body = "{\"query\":\"query problemsetQuestionList {\\r\\n  problemsetQuestionList: questionList(\\r\\n    categorySlug: \\\"\\\"\\r\\n    limit: 50\\r\\n    skip: 0\\r\\n    filters: {}\\r\\n  ) {\\r\\n    total: totalNum\\r\\n    questions: data {\\r\\n      acRate\\r\\n      difficulty\\r\\n      freqBar\\r\\n      frontendQuestionId: questionFrontendId\\r\\n      isFavor\\r\\n      paidOnly: isPaidOnly\\r\\n      status\\r\\n      title\\r\\n      titleSlug\\r\\n      topicTags {\\r\\n        name\\r\\n        id\\r\\n        slug\\r\\n      }\\r\\n      hasSolution\\r\\n      hasVideoSolution\\r\\n    }\\r\\n  }\\r\\n}\\r\\n    \",\"variables\":{}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getPage(size_t page, std::string const& filters) noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    
    std::string body = "{\"query\":\"\\n    query problemsetQuestionList($categorySlug: String, $limit: Int, $skip: Int, $filters: QuestionListFilterInput) {\\n  problemsetQuestionList: questionList(\\n    categorySlug: $categorySlug\\n    limit: $limit\\n    skip: $skip\\n    filters: $filters\\n  ) {\\n    total: totalNum\\n    questions: data {\\n      acRate\\n      difficulty\\n      freqBar\\n      frontendQuestionId: questionFrontendId\\n      isFavor\\n      paidOnly: isPaidOnly\\n      status\\n      title\\n      titleSlug\\n      topicTags {\\n        name\\n        id\\n        slug\\n      }\\n      hasSolution\\n      hasVideoSolution\\n    }\\n  }\\n}\\n    \",\"variables\":{\"categorySlug\":\"\",\"skip\":" + std::to_string((page - 1) * questionsPerPage) + ", \"limit\": " + std::to_string(questionsPerPage) + ", \"filters\":" + filters + "}}";
    
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getTasksDescription(std::string taskName) noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string body = "{\"query\":\"query questionData($titleSlug: String!) {\\r\\nquestion(titleSlug: $titleSlug) {\\r\\nquestionId\\r\\nquestionFrontendId\\r\\nboundTopicId\\r\\ntitle\\r\\ntitleSlug\\r\\ncontent\\r\\ntranslatedTitle\\r\\ntranslatedContent\\r\\nisPaidOnly\\r\\ndifficulty\\r\\nlikes\\r\\ndislikes\\r\\nisLiked\\r\\nsimilarQuestions\\r\\nexampleTestcases\\r\\ncategoryTitle\\r\\ncontributors {\\r\\nusername\\r\\nprofileUrl\\r\\navatarUrl\\r\\n__typename\\r\\n}\\r\\ntopicTags {\\r\\nname\\r\\nslug\\r\\ntranslatedName\\r\\n__typename\\r\\n}\\r\\ncompanyTagStats\\r\\ncodeSnippets {\\r\\nlang\\r\\nlangSlug\\r\\ncode\\r\\n__typename\\r\\n}\\r\\nstats\\r\\nhints\\r\\nsolution {\\r\\nid\\r\\ncanSeeDetail\\r\\npaidOnly\\r\\nhasVideoSolution\\r\\npaidOnlyVideo\\r\\n__typename\\r\\n}\\r\\nstatus\\r\\nsampleTestCase\\r\\nmetaData\\r\\njudgerAvailable\\r\\njudgeType\\r\\nmysqlSchemas\\r\\nenableRunCode\\r\\nenableTestMode\\r\\nenableDebugger\\r\\nenvInfo\\r\\nlibraryUrl\\r\\nadminUrl\\r\\nchallengeQuestion {\\r\\nid\\r\\ndate\\r\\nincompleteChallengeCount\\r\\nstreakCount\\r\\ntype      __typename\\r\\n}\\r\\n__typename\\r\\n}\\r\\n}\",\"variables\":{\"titleSlug\":\"" + taskName + "\"}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getFile(std::string filePath) noexcept(false)
{
    std::string protocol = "https";
    std::string url = filePath;
    std::string type = "GET";

    return std::async(std::launch::async, [this, url, protocol, type]() {return executeRequest(url, protocol, type); });
}

std::future<std::string> RequestManager::getProfileInfo(std::string const& userName) noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string body = "{\"query\":\"\\n    query userProfile($username: String!) {\\n  matchedUser(username: $username) {\\n    contestBadge {\\n      name\\n      expired\\n      hoverText\\n      icon\\n    }\\n    username\\n    githubUrl\\n    twitterUrl\\n    linkedinUrl\\n    profile {\\n      ranking\\n      userAvatar\\n      realName\\n      aboutMe\\n      school\\n      websites\\n      countryName\\n      company\\n      jobTitle\\n      skillTags\\n      postViewCount\\n      postViewCountDiff\\n      reputation\\n      reputationDiff\\n      solutionCount\\n      solutionCountDiff\\n      categoryDiscussCount\\n      categoryDiscussCountDiff\\n    }\\n  }\\n}\\n    \",\"variables\":{\"username\":\"" + userName + "\"}}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });
}

std::future<std::string> RequestManager::getTaskSolvingProgress() noexcept(false)
{
    std::string protocol = "https";
    std::string url = "https://leetcode.com/graphql";
    std::string type = "POST";
    struct curl_slist* headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");
    headers = curl_slist_append(headers, CookieHandler::getInstance()->generateCookieString().c_str());
    std::string body = "{\r\n    \"query\": \"\\n    query userProblemsSolved($username: String!) {\\n  allQuestionsCount {\\n    difficulty\\n    count\\n  }\\n  matchedUser(username: $username) {\\n    problemsSolvedBeatsStats {\\n      difficulty\\n      percentage\\n    }\\n    submitStatsGlobal {\\n      acSubmissionNum {\\n        difficulty\\n        count\\n      }\\n    }\\n  }\\n}\\n    \",\r\n    \"variables\": {\r\n        \"username\": \"" + User::getInstance()->username + "\"\r\n    }\r\n}";
    return std::async(std::launch::async, [this, url, protocol, type, body, headers]() {return executeRequest(url, protocol, type, body, headers); });

}

void RequestManager::runCode(std::unique_ptr<CodeToRun> code, std::function<void(std::unique_ptr<RunCodeResult>)> callback, bool isSubmited)
{
    std::thread(&RequestManager::_runCode, this, std::move(code), callback, isSubmited).detach();
}


RequestManager::~RequestManager()
{
    for (auto& file : storedFiles)
    {
        std::filesystem::remove(file);
    }
}

void RequestManager::getCSRFToken(std::string const &url)
{
    CURLcode res;
    curl = curl_easy_init();

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "GET");
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
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

    auto p = CookieHandler::getInstance();
    (*p.get())["csrftoken"] = csrf;

    std::filesystem::remove(csrfTokenFile);
}
