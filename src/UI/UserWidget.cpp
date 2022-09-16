#include "UserWidget.h"

UserWidget::UserWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);

	ui.closeBtn->setIcon(QPixmap(":/icons/closeIcon.png"));
	
	auto infoTask = RequestManager::getInstance()->getProfileInfo(User::getInstance()->username);
	
}

UserWidget::~UserWidget()
{}
