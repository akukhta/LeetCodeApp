#pragma once

#include <QMainWindow>
#include <qevent.h>
#include <qdebug.h>
#include "ui_ProblemWidget.h"

class ProblemWidget : public QMainWindow
{
	Q_OBJECT

public:
	ProblemWidget(QString name = "Name", QString acceptance = "Acceptance", QString difficulty = "Difficulty", QWidget* parent = nullptr);
	~ProblemWidget();

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
};

struct ProblemWidgetData
{
	QString name;
	QString acceptance;
	QString difficulty;
};