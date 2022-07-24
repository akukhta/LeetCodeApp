#pragma once

#include <QMainWindow>
#include <qframe.h>
#include "../../src/Data/JsonManager.h"
#include "../../src/UI/WindowTool.h"
#include "ui_TaskViewer.h"

class TaskViewer : public QMainWindow
{
	Q_OBJECT

public:
	TaskViewer(std::string const &filePath, QWidget *parent = nullptr);
	~TaskViewer();

private slots:
	void indexChanged(QString text);

private:
	Ui::TaskViewerClass ui;
	std::string const filePath;
	std::unordered_map<std::string, std::string> snipsets;
};
