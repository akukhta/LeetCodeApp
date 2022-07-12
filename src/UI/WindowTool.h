#pragma once

#include <QMainWindow>
#include "ui_WindowTool.h"

class WindowTool : public QMainWindow
{
	Q_OBJECT

public:
	WindowTool(QWidget *parent = nullptr);
	~WindowTool();

private slots:
	
	void on_closeBtn_clicked()
	{
		QApplication::quit();
	}

	void on_schrinkBtn_clicked()
	{
		// Don't know how to implement this yet
	}

private:
	Ui::WindowToolClass ui;
};
