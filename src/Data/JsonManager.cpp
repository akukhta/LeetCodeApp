#include "JsonManager.h"

std::future<std::string> JsonManager::getTitleSlug(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getTitleSlug, fileName);
    return task;
}

std::future<size_t> JsonManager::getQuestionID(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getQuestionID, fileName);
    return task;
}

std::future<std::vector<ProblemWidgetData>> JsonManager::parseProblemsFromJson(std::string const &fileName)
{
    auto task = std::async(_parseProblemsFromJson, fileName);
    return task;
}

std::future<std::vector<ProblemWidgetData>> JsonManager::getProblemListPage(std::string const &fileName) noexcept(false)
{
    auto task = std::async(_getProblemListPage, fileName);
    return task;
}

std::future<std::string> JsonManager::getProblemDescription(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getProblemDescription, fileName);
    return task;
}

std::future<size_t> JsonManager::getQuestionsCount(std::string const &fileName) noexcept(false)
{
    auto task = std::async(_getQuestionsCount, fileName);
    return task;
}

std::future<std::unordered_map<std::string, std::pair<std::string,std::string>>> JsonManager::getCodeSnipsets(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getCodeSnipsets, fileName);
    return task;
}

std::future<std::string> JsonManager::getTestCase(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getTestCase, fileName);
    return task;
}

std::future<std::string> JsonManager::getInterpretID(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getInterpretID, fileName);
    return task;
}

std::future<std::string> JsonManager::getStatus(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getStatus, fileName);
    return task;
}

std::future<std::unique_ptr<RunCodeResult>> JsonManager::getRunCodeResult(std::string const& fileName) noexcept(false)
{
    auto task = std::async(_getRunCodeResult, fileName);
    return task;
}

std::string JsonManager::_getTitleSlug(std::string const& fileName) noexcept(false)
{
    std::string result;
    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("question").toObject();
    result = json.value("titleSlug").toString().toStdString();

    return result;
}

size_t JsonManager::_getQuestionID(std::string const& fileName) noexcept(false)
{
    size_t result;
    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("question").toObject();
    result = json.value("questionId").toString().toInt();

    return result;
}

std::vector<ProblemWidgetData> JsonManager::_parseProblemsFromJson(std::string const &fileName) noexcept(false)
{
    std::vector<ProblemWidgetData> result;
    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    QJsonArray arrayOfQuestions = json.value("allQuestions").toArray();

    for (auto question : arrayOfQuestions)
    {
        QJsonObject obj = question.toObject();
        result.push_back({ obj.value("title").toString(), QString::number(obj.value("acRate").toDouble()), 
            obj.value("difficulty").toString(), obj.value("titleSlug").toString(), obj.value("status").toString()});
    }

    return result;
}

std::vector<ProblemWidgetData> JsonManager::_getProblemListPage(std::string const &fileName) noexcept(false)
{
    std::vector<ProblemWidgetData> result;
    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("problemsetQuestionList").toObject();
    QJsonArray arrayOfQuestions = json.value("questions").toArray();

    for (auto question : arrayOfQuestions)
    {
        QJsonObject obj = question.toObject();
        result.push_back({ obj.value("title").toString(), QString::number(obj.value("acRate").toDouble()), obj.value("difficulty").toString(), obj.value("titleSlug").toString(), obj.value("status").toString()});
    }
    jsonDoc.close();
    return result;
}

std::string JsonManager::_getProblemDescription(std::string const& fileName) noexcept(false)
{
    std::string result;
    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("question").toObject();
    result = json.value("content").toString().toStdString();

    return result;
}

std::unordered_map<std::string, std::pair<std::string, std::string>> JsonManager::_getCodeSnipsets(std::string const& fileName) noexcept(false)
{
    std::unordered_map <std::string, std::pair<std::string, std::string>> snipsets;

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("question").toObject();
    QJsonArray arrayOfQuestions = json.value("codeSnippets").toArray();

    for (auto question : arrayOfQuestions)
    {
        QJsonObject obj = question.toObject();
        snipsets.insert(std::make_pair(obj.value("lang").toString().toStdString(), 
            std::make_pair(obj.value("langSlug").toString().toStdString(), obj.value("code").toString().toStdString())));
    }

    return snipsets;
}

size_t JsonManager::_getQuestionsCount(std::string const &fileName) noexcept(false)
{
    size_t questionsCount;

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("problemsetQuestionList").toObject();
    questionsCount = json.value("total").toInt();
    jsonDoc.close();
    return questionsCount;
}

std::string JsonManager::_getTestCase(std::string const& fileName) noexcept(false)
{
    std::string result;

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    json = json.value("data").toObject();
    json = json.value("question").toObject();
    result = json.value("sampleTestCase").toString().toStdString();

    return result;
}

std::string JsonManager::_getInterpretID(std::string const& fileName) noexcept(false)
{
    std::string result;

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    result = json.value("interpret_id").toString().toStdString();

    return result;
}

std::string JsonManager::_getStatus(std::string const& fileName) noexcept(false)
{
    std::string result;

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    result = json.value("state").toString().toStdString();

    return result;
}

std::unique_ptr<RunCodeResult> JsonManager::_getRunCodeResult(std::string const& fileName) noexcept(false)
{
    std::unique_ptr<RunCodeResult> result = std::make_unique<RunCodeResult>();

    QFile jsonDoc(QString::fromStdString(fileName));

    if (!jsonDoc.open(QFile::ReadOnly | QFile::Text))
    {
        throw std::runtime_error("Can`t open JSON file");
    }

    auto bArr = jsonDoc.readAll();

    QJsonDocument document = QJsonDocument::fromJson(bArr);
    QJsonObject json = document.object();
    result->statusRuntime = json.value("status_runtime").toString().toStdString();
    result->statusMemory = json.value("status_memory").toString().toStdString();
    result->statusMsg = json.value("status_msg").toString().toStdString();

    return result;
}
