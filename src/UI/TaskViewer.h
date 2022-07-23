#pragma once

#include <QMainWindow>
#include "../../src/Data/JsonManager.h"
#include "ui_TaskViewer.h"

class TaskViewer : public QMainWindow
{
	Q_OBJECT

public:
	TaskViewer(std::string const &filePath, QWidget *parent = nullptr);
	~TaskViewer();

private:
	Ui::TaskViewerClass ui;
	std::string const filePath;
};
