#include "WindowTool.h"

QWidget* WindowTool::mainWindow = nullptr;

WindowTool::WindowTool(std::function<void(WindowTool*)> exitCallback, QWidget *parent)
	: exitCallback(exitCallback), QMainWindow(parent)
{
	ui.setupUi(this);
	ui.profileBtn->setIcon(QPixmap(":/icons/profile.png"));
	ui.schrinkBtn->setIcon(QPixmap(":/icons/shrink.png"));
	ui.closeBtn->setIcon(QPixmap(":/icons/closeIcon.png"));
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

void WindowTool::hidePage(WindowTool* w)
{
	w->parentWidget()->parentWidget()->hide();

	if (mainWindow)
	{
		mainWindow->show();
	}
}
