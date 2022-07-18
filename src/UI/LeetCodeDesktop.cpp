#include "LeetCodeDesktop.h"

LeetCodeDesktop::LeetCodeDesktop(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);
    ui.verticalLayout_4->addWidget(new WindowTool(this));

    for (unsigned short i = 1; i <= 6; i++)
    {
        NavButton* btn = new NavButton(i, QString::number(i));
        ui.horizontalLayout_2->addWidget(btn);

        if (i == 1)
        {
            btn->setActive();
        }
    }


    auto rmInstance = RequestManager::getInstance();
    auto qCount = rmInstance->getQuestionsCount();
    qCount.wait();
    auto path = qCount.get();
    auto jTask = JsonManager::getQuestionsCount(path);
    jTask.wait();
    auto rez = jTask.get();
    auto jsonParsingTask = JsonManager::getProblemListPage(path);
    jsonParsingTask.wait();
    auto problems = jsonParsingTask.get();

    for (auto& problem : problems)
    {
        ProblemWidget* widget = new ProblemWidget(problem.name, problem.acceptance, problem.difficulty);
        ui.verticalLayout_1->addWidget(widget);
    }
    
    auto allQuestions = rmInstance->getAllProblems();
}

void LeetCodeDesktop::navBtnClicked()
{
    
}

LeetCodeDesktop::~LeetCodeDesktop()
{
}
