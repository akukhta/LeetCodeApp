#include "TaskViewer.h"

TaskViewer::TaskViewer(QWidget *parent)
	: filePath(filePath), QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(indexChanged(QString)));
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Tool | Qt::Dialog);

	ui.gridLayout->addWidget(new WindowTool(std::bind(WindowTool::closePage, std::placeholders::_1), this),0,0,1,2);
}

void TaskViewer::on_copyBtn_clicked()
{
	QApplication::clipboard()->setText(ui.textBrowser_2->toPlainText());
}

void TaskViewer::indexChanged(QString text)
{
	ui.textBrowser_2->setText(QString::fromStdString(snipsets[text.toStdString()]));
}

TaskViewer::~TaskViewer()
{}

void TaskViewer::getData(std::string const& filePath)
{
	auto taskDescription = JsonManager::getProblemDescription(filePath);
	taskDescription.wait();
	ui.textBrowser->setText(QString::fromStdString(taskDescription.get()));
	auto codeSnipsets = JsonManager::getCodeSnipsets(filePath);
	codeSnipsets.wait();
	snipsets = codeSnipsets.get();

	size_t idx = 0;

	for (auto const& lang : snipsets)
	{
		ui.comboBox->addItem(QString::fromStdString(lang.first));
		ui.comboBox->setItemData(idx++, QBrush(Qt::white), Qt::TextColorRole);
	}

	if (!snipsets.empty())
	{
		ui.textBrowser_2->setText(QString::fromStdString(snipsets.begin()->second));
	}
	else
	{
		ui.textBrowser_2->clear();
		ui.comboBox->clear();
	}
}

std::shared_ptr<TaskViewer> TaskViewer::getInstance()
{
	static std::shared_ptr<TaskViewer> viewer = std::shared_ptr<TaskViewer>(new TaskViewer());
	return viewer;
}
