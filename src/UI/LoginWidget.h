#pragma once

#include <QMainWindow>
#include <qprocess.h>
#include <QFile>
#include <filesystem>
#include "ui_LoginWidget.h"
#include "../../src/Common/CookieHandler.h"

class LoginWidget : public QMainWindow
{
	Q_OBJECT

public:
	LoginWidget(QWidget *parent = nullptr);
	~LoginWidget();

private slots:
	void on_closeBtn_clicked();
	void on_guestBtn_clicked();
	void on_loginBtn_clicked();

private:
	Ui::LoginWidgetClass ui;

};
