#include "LeetCodeDesktop.h"

LeetCodeDesktop::LeetCodeDesktop(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    LoginWidget* widget = new LoginWidget();
    widget->show();
    setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);
    ui.verticalLayout_4->addWidget(new WindowTool(std::bind(WindowTool::closeApp, std::placeholders::_1), this));
    auto rmInstance = RequestManager::getInstance();
    auto qCount = rmInstance->getQuestionsCount();
    qCount.wait();
    auto path = qCount.get();
    auto jTask = JsonManager::getQuestionsCount(path);
    jTask.wait();
    pagesCount = ceil(static_cast<double>(jTask.get()) / questionsPerPage);

    NavWidget* wid = new NavWidget(pagesCount, std::bind(&LeetCodeDesktop::navWidBtn, this, std::placeholders::_1));
    wid->setFixedWidth(ui.centralWidget->width() * 2);
    
    ProblemWidget::previousScreen = this;
    WindowTool::mainWindow = this;

    ui.horizontalLayout_2->addWidget(wid);
    createProblemWidgets();
    loadProblemsFromFile(path);

    auto allQuestions = rmInstance->getAllProblems();
    
}

LeetCodeDesktop::~LeetCodeDesktop()
{
    auto x = rand();
    x += rand();
    x -= rand();
    x *= rand();
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

    setUpdatesEnabled(false);

    auto pWidgets = ProblemWidget::getInstance();

    for (size_t i = 0; i < problemsData.size(); i++)
    {
        (*pWidgets)[i]->setData(problemsData[i].name, problemsData[i].acceptance, problemsData[i].difficulty, problemsData[i].titleSlug);
    }

    setUpdatesEnabled(true);
}

void LeetCodeDesktop::navWidBtn(size_t pageNum)
{
    loadProblemsFromFile(loadPage(pageNum));
}

void LeetCodeDesktop::createProblemWidgets()
{
    auto pWidgets = ProblemWidget::getInstance();

    for (size_t i = 0; i < pWidgets->size(); i++)
    {
        ui.verticalLayout_1->addWidget((*pWidgets)[i]);
    }
}
