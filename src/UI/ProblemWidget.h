#pragma once

#include <QMainWindow>
#include <qevent.h>
#include <qdebug.h>
#include <qmessagebox.h>
#include "ui_ProblemWidget.h"
#include "../../src/API/RequestManager.h"
#include "../../src/UI/TaskViewer.h"
#include "../../src/Common/ProblemWidgetData.h"

class ProblemWidget : public QMainWindow
{
	Q_OBJECT

public:
	ProblemWidget(QString name = "Name", QString acceptance = "Acceptance", QString difficulty = "Difficulty", QString titleSlug = "", QWidget* parent = nullptr);
	~ProblemWidget();
	static QWidget* previousScreen;

protected:
	void enterEvent(QEvent*);
	void leaveEvent(QEvent*);
	bool event(QEvent* e);

	void hoverEnter(QHoverEvent* event);
	void hoverLeave(QHoverEvent* event);
	void hoverMove(QHoverEvent* event);

private:
	Ui::ProblemWidgetClass ui;
	static QString const active;
	static QString const passtive;
	static QString const passtiveLabel;
	static QString const activeLabel;
	void activated();
	void leaved();
	QString titleSlug;
};