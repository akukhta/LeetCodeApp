#include "LeetCodeDesktop.h"

LeetCodeDesktop::LeetCodeDesktop(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);
    ui.verticalLayout_4->addWidget(new WindowTool(this));
    auto rmInstance = RequestManager::getInstance();
    auto qCount = rmInstance->getQuestionsCount();
    qCount.wait();
    auto path = qCount.get();
    auto jTask = JsonManager::getQuestionsCount(path);
    jTask.wait();
    pagesCount = ceil(static_cast<double>(jTask.get()) / questionsPerPage);

    NavWidget* wid = new NavWidget(pagesCount, std::bind(&LeetCodeDesktop::navWidBtn, this, std::placeholders::_1));
    wid->setFixedWidth(ui.centralWidget->width() * 2);

    ui.horizontalLayout_2->addWidget(wid);

    loadProblemsFromFile(path);

    auto allQuestions = rmInstance->getAllProblems();
}

LeetCodeDesktop::~LeetCodeDesktop()
{
}

std::string LeetCodeDesktop::loadPage(size_t pageNum)
{
    auto rmInstance = RequestManager::getInstance();
    auto page = rmInstance->getPage(pageNum);
    page.wait();
    return page.get();
}

void LeetCodeDesktop::loadProblemsFromFile(std::string path)
{
    auto jTask = JsonManager::getProblemListPage(path);
    jTask.wait();
    auto problemsData = jTask.get();

    QLayoutItem* child;
    while ((child = ui.verticalLayout_1->takeAt(0)) != 0) 
    {
        delete child;
    }

    for (auto& problem : problemsData)
    {
        ProblemWidget* widget = new ProblemWidget(problem.name, problem.acceptance, problem.difficulty, problem.titleSlug);
        ui.verticalLayout_1->addWidget(widget);
    }
}

void LeetCodeDesktop::navWidBtn(size_t pageNum)
{
    loadProblemsFromFile(loadPage(pageNum));
}
