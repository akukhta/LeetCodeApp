#include "LeetCodeDesktop.h"

LeetCodeDesktop::LeetCodeDesktop(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);
    ui.verticalLayout_4->addWidget(new WindowTool(this));
    setStyleSheet("{background-color: rgb(250, 0, 0);}");
    auto rmInstance = RequestManager::getInstance();
    auto qCount = rmInstance->getQuestionsCount();
    Task<std::string> qCountTask(std::move(qCount));
    qCountTask.executeTask();
    auto path = qCountTask.getResult();
    Task<size_t> jTask(JsonManager::getQuestionsCount(path));
    jTask.executeTask();
    auto rez = jTask.getResult();
    Task<std::vector<ProblemWidgetData>> jsonParsingTask(JsonManager::getProblemListPage(path));
    jsonParsingTask.setPostCallBack([&path]() { std::filesystem::remove(path);});
    jsonParsingTask.executeTask();
    auto problems = jsonParsingTask.getResult();

    for (auto& problem : problems)
    {
        ProblemWidget* widget = new ProblemWidget(problem.name, problem.acceptance, problem.difficulty);
        ui.verticalLayout_1->addWidget(widget);
    }
}

LeetCodeDesktop::~LeetCodeDesktop()
{}
