#include "LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->setPixmap(QPixmap(":/icons/logo.svg"));
}

LoginWidget::~LoginWidget()
{}
