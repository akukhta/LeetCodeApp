#include "ProblemWidget.h"

QString const ProblemWidget::active = "border-radius: 15px; background-color: rgb(255, 255, 255);";
QString const ProblemWidget::passtive = "border-radius: 15px; background-color: rgb(118, 222, 109);";
QString const ProblemWidget::passtiveNotSolved = "border-radius: 15px; background-color: rgb(45, 45, 68);";
QString const ProblemWidget::activeLabel = "QLabel { color : rgb(0,0, 0);}";
QString const ProblemWidget::passtiveLabelNotSolved = "QLabel { color : rgb(255, 255, 255);}";
QString const ProblemWidget::passtiveLabelSolved = "QLabel { color : rgb(0, 0, 0);}";
QWidget* ProblemWidget::previousScreen = nullptr;

std::shared_ptr<std::vector<ProblemWidget*>> ProblemWidget::getInstance()
{
    static std::shared_ptr<std::vector<ProblemWidget*>> vec = std::shared_ptr<std::vector<ProblemWidget*>>(new std::vector<ProblemWidget*>());
    
    if (vec->empty())
    {
        for (size_t i = 0; i < 50; i++)
        {
            vec->push_back(new ProblemWidget());
        }
    }

    return vec;
}

ProblemWidget::ProblemWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setAttribute(Qt::WA_Hover, true);
    leaved();
}

bool ProblemWidget::event(QEvent* e)
{
    static std::shared_ptr<TaskViewer> viewer = TaskViewer::getInstance();

    switch (e->type())
    {
    case QEvent::MouseButtonPress:
    {
        auto reqManager = RequestManager::getInstance();
        auto t = reqManager->getTasksDescription(titleSlug.toStdString());
        t.wait();
        previousScreen->hide();
        WindowTool::windows.push(this);
        viewer->getData(t.get());
        viewer->show();
    }
    default:
        break;
    }

    return QWidget::event(e);
}

void ProblemWidget::enterEvent(QEvent* e)
{
    activated();
}

void ProblemWidget::leaveEvent(QEvent* e)
{
    leaved();
}

void ProblemWidget::activated()
{
    setStyleSheet(active);
    ui.nameLabel->setStyleSheet(activeLabel);
    ui.acceptanceLabel->setStyleSheet(activeLabel);
    ui.difficultyLabel->setStyleSheet(activeLabel);
}

void ProblemWidget::leaved()
{
    setStyleSheet(isSolved ? passtive : passtiveNotSolved);
    ui.nameLabel->setStyleSheet(isSolved ? passtiveLabelSolved : passtiveLabelNotSolved);
    ui.acceptanceLabel->setStyleSheet(isSolved ? passtiveLabelSolved : passtiveLabelNotSolved);
    ui.difficultyLabel->setStyleSheet(isSolved ? passtiveLabelSolved : passtiveLabelNotSolved);
}

ProblemWidget::~ProblemWidget()
{}

void ProblemWidget::setData(QString name, QString acceptance, QString difficulty, QString titleSlug, QString status)
{
    this->titleSlug = titleSlug;
    ui.nameLabel->setText(name);
    ui.acceptanceLabel->setText(acceptance);
    ui.difficultyLabel->setText(difficulty);
    isSolved = status == "ac" ? true : false;

    if (isSolved)
    {
        setStyleSheet(passtive);
        ui.nameLabel->setStyleSheet(activeLabel);
        ui.acceptanceLabel->setStyleSheet(activeLabel);
        ui.difficultyLabel->setStyleSheet(activeLabel);
    }
    else
    {
        setStyleSheet(passtiveNotSolved);
        ui.nameLabel->setStyleSheet(passtiveLabelNotSolved);
        ui.acceptanceLabel->setStyleSheet(passtiveLabelNotSolved);
        ui.difficultyLabel->setStyleSheet(passtiveLabelNotSolved);
    }
}
