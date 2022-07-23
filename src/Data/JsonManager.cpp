#include "JsonManager.h"

std::future<std::vector<ProblemWidgetData>> JsonManager::parseProblemsFromJson(std::string const &fileName)
{
    std::future<std::vector<ProblemWidgetData>> task = std::async(_parseProblemsFromJson, fileName);
    return task;
}

std::future<std::vector<ProblemWidgetData>> JsonManager::getProblemListPage(std::string const &fileName) noexcept(false)
{
    std::future<std::vector<ProblemWidgetData>> task = std::async(_getProblemListPage, fileName);
    return task;
}

std::future<std::string> JsonManager::getProblemDescription(std::string const& fileName) noexcept(false)
{
    std::future<std::string> task = std::async(_getProblemDescription, fileName);
    return task;
}

std::future<size_t> JsonManager::getQuestionsCount(std::string const &fileName) noexcept(false)
{
    std::future<size_t> task = std::async(_getQuestionsCount, fileName);
    return task;
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
        result.push_back({ obj.value("title").toString(), QString::number(obj.value("acRate").toDouble()), obj.value("difficulty").toString(), obj.value("titleSlug").toString()});
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
        result.push_back({ obj.value("title").toString(), QString::number(obj.value("acRate").toDouble()), obj.value("difficulty").toString(), obj.value("titleSlug").toString() });
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
