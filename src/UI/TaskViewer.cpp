#include "TaskViewer.h"

TaskViewer::TaskViewer(std::string const& filePath, QWidget *parent)
	: filePath(filePath), QMainWindow(parent)
{
	ui.setupUi(this);
	auto taskDescription = JsonManager::getProblemDescription(this->filePath);
	taskDescription.wait();
	ui.textBrowser->setText(QString::fromStdString(taskDescription.get()));
}

TaskViewer::~TaskViewer()
{}
