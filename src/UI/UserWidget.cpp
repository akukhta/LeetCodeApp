#include "UserWidget.h"

UserWidget::UserWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);

	auto infoTask = RequestManager::getInstance()->getProfileInfo(User::getInstance()->username);
	ui.avatar->setPixmap(QPixmap(QString::fromStdString(User::getInstance()->avatarPath)));

	ui.closeBtn->setIcon(QPixmap(":/icons/closeIcon.png"));
	
	auto userInfoTask = JsonManager::getUserDetailsInfo(infoTask.get());
	auto userInfo = userInfoTask.get();

	ui.realNameLabel->setText(QString::fromStdString(userInfo->realName));
	ui.giturlLabel->setText(QString::fromStdString(userInfo->githubUrl));
	ui.rankLabel->setText("Rank: " + QString::number(userInfo->rank));
	ui.nicLabel->setText(QString::fromStdString(User::getInstance()->username));
}

UserWidget::~UserWidget()
{}
