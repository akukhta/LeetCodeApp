#include "LeetCodeDesktop.h"

LeetCodeDesktop::LeetCodeDesktop(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);
    ui.verticalLayout_4->addWidget(new WindowTool(this));
    setStyleSheet("{background-color: rgb(250, 0, 0);}");
    auto rmInstance = RequestManager::getInstance();
    auto qSizeTask = rmInstance->getQuestionsCount();
    Task<void> t;
    /*auto e = rmInstance->getAllProblems();
    t.setTask(std::move(std::get<0>(e)));

#ifdef _DEBUG
    t.setPreCallBack([]() {
        qDebug() << "Fetching all problems...";
        });
#endif

    t.setPostCallBack([&e]() {
        fclose(std::get<1>(e));
        std::filesystem::remove(std::get<2>(e));

#ifdef _DEBUG
        qDebug() << "All problems have been received\n";
#endif 
        });

    t.executeTask();*/

    std::get<0>(qSizeTask).wait();
    fclose(std::get<1>(qSizeTask));

    auto jTask = JsonManager::getQuestionsCount(std::get<2>(qSizeTask));
    jTask.wait();
    size_t questionsCount = jTask.get();

    /*auto httpTask = rmInstance->getAllProblems();
    std::get<0>(httpTask).wait();
    fclose(std::get<1>(httpTask));

    auto jsonParsingTask = JsonManager::parseProblemsFromJson(std::get<2>(httpTask));
    jsonParsingTask.wait();
    auto problems = jsonParsingTask.get();

    for (auto& problem : problems)
    {
        ProblemWidget* widget = new ProblemWidget(problem.name, problem.acceptance, problem.difficulty);
        widget->setFixedWidth(size().width());
        ui.verticalLayout->addWidget(widget);
    }*/

    auto jsonParsingTask = JsonManager::getProblemListPage(std::get<2>(qSizeTask));
    jsonParsingTask.wait();
    auto problems = jsonParsingTask.get();

    for (auto& problem : problems)
    {
        ProblemWidget* widget = new ProblemWidget(problem.name, problem.acceptance, problem.difficulty);
        //widget->setFixedWidth(size().width() - 120);
        //ui.centralWidget->addWidget(widget);
        ui.verticalLayout_1->addWidget(widget);
    }
}

LeetCodeDesktop::~LeetCodeDesktop()
{}
