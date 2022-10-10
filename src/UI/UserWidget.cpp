#include "UserWidget.h"

UserWidget::UserWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);

	auto rManager = RequestManager::getInstance();

	auto infoTask = rManager->getProfileInfo(User::getInstance()->username);
	
	ui.avatar->setPixmap(QPixmap(QString::fromStdString(User::getInstance()->avatarPath)));

	ui.closeBtn->setIcon(QPixmap(":/icons/closeIcon.png"));
	
	auto userInfoTask = JsonManager::getUserDetailsInfo(infoTask.get());
	auto userInfo = userInfoTask.get();
	auto taskStatsTask = rManager->getTaskSolvingProgress();

	ui.realNameLabel->setText(QString::fromStdString(userInfo->realName));
	ui.giturlLabel->setText(QString::fromStdString(userInfo->githubUrl));
	ui.rankLabel->setText("Rank: " + QString::number(userInfo->rank));
	ui.nicLabel->setText(QString::fromStdString(User::getInstance()->username));

	auto taskStatPTast = JsonManager::getTaskStats(taskStatsTask.get());
	auto taskStats = taskStatPTast.get();

	ui.progressBar->setMaximum(taskStats->questions[TasksStat::difficulty::EASY].first);
	ui.progressBar->setValue(taskStats->questions[TasksStat::difficulty::EASY].second);

	ui.progressBar_2->setMaximum(taskStats->questions[TasksStat::difficulty::MEDIUM].first);
	ui.progressBar_2->setValue(taskStats->questions[TasksStat::difficulty::MEDIUM].second);
	
	ui.progressBar_3->setMaximum(taskStats->questions[TasksStat::difficulty::HARD].first);
	ui.progressBar_3->setValue(taskStats->questions[TasksStat::difficulty::HARD].second);
}

UserWidget::~UserWidget()
{}

std::shared_ptr<UserWidget> UserWidget::getInstance()
{
	static std::shared_ptr<UserWidget> ptr = std::shared_ptr<UserWidget>(new UserWidget());
	return ptr;
}
