#pragma once

#include <QMainWindow>
#include "../../src/API/RequestManager.h"
#include "../../src/Common/User.h"
#include "ui_UserWidget.h"

class UserWidget : public QMainWindow
{
	Q_OBJECT

public:
	UserWidget(QWidget *parent = nullptr);
	~UserWidget();

private slots:
	void on_closeBtn_clicked()
	{
		close();
	}

private:
	Ui::UserWidgetClass ui;
};
