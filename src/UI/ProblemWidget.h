#pragma once

#include <QMainWindow>
#include <qevent.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include "ui_ProblemWidget.h"
#include "../../src/API/RequestManager.h"
#include "../../src/UI/TaskViewer.h"
#include "../../src/Common/ProblemWidgetData.h"

class ProblemWidget : public QMainWindow, std::enable_shared_from_this<ProblemWidget>
{
	Q_OBJECT

public:
	static std::shared_ptr<std::vector<ProblemWidget*>> getInstance();
	~ProblemWidget();
	static QWidget* previousScreen;
	void setData(QString name = "Name", QString acceptance = "Acceptance", QString difficulty = "Difficulty", QString titleSlug = "", QString status = "null");
	static QSize defaultParentWidgetSize;

protected:
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	bool event(QEvent* e);

private:
	ProblemWidget(QWidget* parent = nullptr);
	Ui::ProblemWidgetClass ui;
	static QString const active;
	static QString const passtive;
	static QString const passtiveNotSolved;
	static QString const passtiveLabel;
	static QString const activeLabel;
	void activated();
	void leaved();
	QString titleSlug;
	bool isSolved = false;
};