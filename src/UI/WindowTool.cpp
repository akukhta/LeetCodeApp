#include "WindowTool.h"

std::stack<QWidget*, std::list<QWidget*>> WindowTool::windows = std::stack<QWidget*, std::list<QWidget*>>();

WindowTool::WindowTool(QWidget* currentWindow, std::function<void(WindowTool*)> exitCallback, QWidget *parent)
	: currentWindow(currentWindow), exitCallback(exitCallback), QMainWindow(parent)
{
	ui.setupUi(this);
	ui.profileBtn->setIcon(QPixmap(":/icons/profile.png"));
	ui.schrinkBtn->setIcon(QPixmap(":/icons/shrink.png"));
	ui.closeBtn->setIcon(QPixmap(":/icons/closeIcon.png"));

	defaultWindowSize = size();
}

WindowTool::~WindowTool()
{}

void WindowTool::UpdateActiveWindow(QWidget * newActiveWindow)
{
	currentWindow = newActiveWindow;
}

void WindowTool::closeApp(WindowTool *w)
{
	QApplication::quit();
}

void WindowTool::closePage(WindowTool *w)
{
	w->parentWidget()->parentWidget()->close();
}

void WindowTool::hidePage(WindowTool* w)
{
	w->parentWidget()->parentWidget()->hide();

	if (w->currentWindow)
	{
		w->currentWindow->show();
	}
}
