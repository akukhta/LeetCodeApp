#pragma once

#include <QMainWindow>
#include <qframe.h>
#include <qclipboard.h>
#include <memory>
#include "../../src/Data/JsonManager.h"
#include "../../src/UI/WindowTool.h"
#include "../../src/API/RequestManager.h"
#include "../../src/Data/CachedStorage.h"
#include "../../src/Common/DefaultSizeable.h"
#include "ui_TaskViewer.h"

class TaskViewer : public QMainWindow, std::enable_shared_from_this<TaskViewer>, public DefaultSizeable
{
	Q_OBJECT

public:
	~TaskViewer();
	void getData(std::string const& filePath);
	static std::shared_ptr<TaskViewer> getInstance();

private:
	TaskViewer(QWidget *parent = nullptr);
	void displayRunCodeResult(std::unique_ptr<RunCodeResult> result);

private slots:
	void indexChanged(QString text);
	void on_copyBtn_clicked();
	void on_runBtn_clicked();

private:
	Ui::TaskViewerClass ui;
	std::string const filePath;
	std::unordered_map<std::string, std::pair<std::string, std::string>> snipsets;
	size_t questionID;
	std::string titleSlug;
	std::vector<std::string> langSlugs;
	void findImages(std::string& context);
	WindowTool* wTool;
};
