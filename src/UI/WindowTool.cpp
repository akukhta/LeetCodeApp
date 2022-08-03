#include "WindowTool.h"

QWidget* WindowTool::mainWindow = nullptr;

WindowTool::WindowTool(std::function<void(WindowTool*)> exitCallback, QWidget *parent)
	: exitCallback(exitCallback), QMainWindow(parent)
{
	ui.setupUi(this);
}

WindowTool::~WindowTool()
{}

void WindowTool::closeApp(WindowTool *w)
{
	QApplication::quit();
}

void WindowTool::closePage(WindowTool *w)
{
	w->parentWidget()->parentWidget()->close();

	if (mainWindow)
	{
		mainWindow->show();
	}
}
