#pragma once

#include <QMainWindow>
#include "ui_WindowTool.h"

class WindowTool : public QMainWindow
{
	Q_OBJECT

public:
	WindowTool(std::function<void (WindowTool*)> exitCallback = closeApp, QWidget* parent = nullptr);
	~WindowTool();

	static void closeApp(WindowTool* w);
	static void closePage(WindowTool* w);
	static void hidePage(WindowTool* w);

	static QWidget* mainWindow;

private slots:
	
	void on_closeBtn_clicked()
	{
		exitCallback(this);
	}

	void on_schrinkBtn_clicked()
	{
		// Don't know how to implement this yet
	}

private:
	Ui::WindowToolClass ui;
	std::function<void(WindowTool*)> exitCallback;
};
