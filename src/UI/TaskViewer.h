#pragma once

#include <QMainWindow>
#include "ui_TaskViewer.h"

class TaskViewer : public QMainWindow
{
	Q_OBJECT

public:
	TaskViewer(QWidget *parent = nullptr);
	~TaskViewer();

private:
	Ui::TaskViewerClass ui;
};
