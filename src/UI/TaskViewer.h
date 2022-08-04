#pragma once

#include <QMainWindow>
#include <qframe.h>
#include <qclipboard.h>
#include <memory>
#include "../../src/Data/JsonManager.h"
#include "../../src/UI/WindowTool.h"
#include "ui_TaskViewer.h"

class TaskViewer : public QMainWindow, std::enable_shared_from_this<TaskViewer>
{
	Q_OBJECT

public:
	~TaskViewer();
	void getData(std::string const& filePath);
	static std::shared_ptr<TaskViewer> getInstance();

private:
	TaskViewer(QWidget *parent = nullptr);

private slots:
	void indexChanged(QString text);
	void on_copyBtn_clicked();

private:
	Ui::TaskViewerClass ui;
	std::string const filePath;
	std::unordered_map<std::string, std::string> snipsets;
};
