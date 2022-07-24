#include "TaskViewer.h"

TaskViewer::TaskViewer(std::string const& filePath, QWidget *parent)
	: filePath(filePath), QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(indexChanged(QString)));
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Window);

	ui.gridLayout->addWidget(new WindowTool(this),0,0,1,2);
	auto taskDescription = JsonManager::getProblemDescription(this->filePath);
	taskDescription.wait();
	ui.textBrowser->setText(QString::fromStdString(taskDescription.get()));
	auto codeSnipsets = JsonManager::getCodeSnipsets(this->filePath);
	codeSnipsets.wait();
	snipsets = codeSnipsets.get();

	size_t idx = 0;

	for (auto const& lang : snipsets)
	{
		ui.comboBox->addItem(QString::fromStdString(lang.first));
		ui.comboBox->setItemData(idx++, QBrush(Qt::white), Qt::TextColorRole);
	}

}

void TaskViewer::indexChanged(QString text)
{
	ui.textBrowser_2->setText(QString::fromStdString(snipsets[text.toStdString()]));
}

TaskViewer::~TaskViewer()
{}
