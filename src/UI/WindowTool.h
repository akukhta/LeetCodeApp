#pragma once

#include <QMainWindow>
#include <stack>
#include <list>
#include <qapplication.h>
#include <qdesktopwidget.h>
#include "../../src/UI/UserWidget.h"
#include "../../src/Common/DefaultSizeable.h"
#include "../../src/Common/User.h"
#include "ui_WindowTool.h"

class WindowTool : public QMainWindow
{
	Q_OBJECT

public:
	WindowTool(QWidget* currentWindow = nullptr, std::function<void(WindowTool*)> exitCallback = closeApp, QWidget* parent = nullptr);
	~WindowTool();
	void UpdateActiveWindow(QWidget* newActiveWindow);

	static void closeApp(WindowTool* w);
	static void closePage(WindowTool* w);
	static void hidePage(WindowTool* w);

	static std::stack<QWidget*, std::list<QWidget*>> windows;

private slots:
	
	void on_profileBtn_clicked()
	{
		if (User::getInstance()->isLogged)
		{
			auto wid = UserWidget::getInstance();
			wid->show();
		}
	}

	void on_closeBtn_clicked()
	{
		exitCallback(this);
		
		if (!windows.empty())
		{
			windows.pop();

			if (windows.empty())
			{
				QApplication::exit();
				return;
			}

			currentWindow = windows.top();
			currentWindow->show();
		}
	}

	void on_schrinkBtn_clicked()
	{
		DefaultSizeable* defS = dynamic_cast<DefaultSizeable*>(currentWindow);

		if (defS == nullptr)
		{
			throw std::runtime_error("Can`t shrink because form isn`t default sizeable");
		}

		if (currentWindow->isFullScreen())
		{
			auto defaultSize = defS->getDefaultSize();
			auto screenSize = QApplication::desktop()->screenGeometry().size();
			currentWindow->setFixedSize(defaultSize);
			currentWindow->move(screenSize.width() / 2 - defaultSize.width() / 2, screenSize.height() / 2 - defaultSize.height() / 2);
		}
		else
		{
			currentWindow->move(0, 0);
			currentWindow->setFixedSize(QApplication::desktop()->screenGeometry().size());
		}
	}

private:
	QWidget* currentWindow;
	Ui::WindowToolClass ui;
	std::function<void(WindowTool*)> exitCallback;
	QSize defaultWindowSize;
};
