#pragma once

#include <QMainWindow>
#include <qprogressbar.h>
#include "../../src/API/RequestManager.h"
#include "../../src/Common/User.h"
#include "ui_UserWidget.h"

class UserWidget : public QMainWindow, public std::enable_shared_from_this<UserWidget>
{
	Q_OBJECT

public:
	~UserWidget();
	static std::shared_ptr<UserWidget> getInstance();

private slots:
	void on_closeBtn_clicked()
	{
		hide();
	}

private:
	Ui::UserWidgetClass ui;
	UserWidget(QWidget* parent = nullptr);
};
