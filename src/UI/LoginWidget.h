#pragma once

#include <QMainWindow>
#include <qprocess.h>
#include "ui_LoginWidget.h"

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
