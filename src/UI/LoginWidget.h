#pragma once

#include <QMainWindow>
#include "ui_LoginWidget.h"

class LoginWidget : public QMainWindow
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = nullptr);
	~LoginWidget();

private:
	Ui::LoginWidgetClass ui;
};
