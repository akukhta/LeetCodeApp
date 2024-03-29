#include "TaskViewer.h"

TaskViewer::TaskViewer(QWidget *parent)
	: filePath(filePath), QMainWindow(parent)
{
	ui.setupUi(this);
	connect(ui.comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(indexChanged(QString)));
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::Tool | Qt::Dialog);
	wTool = new WindowTool(this, std::bind(WindowTool::closePage, std::placeholders::_1), this);
	ui.gridLayout->addWidget(wTool,0,0,1,2);
	setDefaultSize(size());
}

void TaskViewer::displayRunCodeResult(std::unique_ptr<RunCodeResult> result)
{
	ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("execution time: {}\n", result->statusRuntime)));
	ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("memory: {}\n", result->statusMemory)));
	ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("message: {}\n", result->statusMsg)));
	
	if (result->compileError)
	{
		ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("compiler output: {}\n", result->fullCompileError)));
	}
	else
	{
		ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("rentime percentile: {}\n", std::to_string(result->runtimePercentile))));
		ui.runCodeResultBrowser->append(QString::fromStdString(StringUtiles::formatString("memory percentile: {}\n", std::to_string(result->memoryPercentile))));
	}


}

void TaskViewer::on_copyBtn_clicked()
{
	QApplication::clipboard()->setText(ui.textBrowser_2->toPlainText());
}

void TaskViewer::on_runBtn_clicked()
{
	ui.runCodeResultBrowser->clear();
	ui.tabWidget->setCurrentIndex(1);

	std::unique_ptr<CodeToRun> ptr = std::make_unique<CodeToRun>();
	ptr->code = StringUtiles::formatCodeString(ui.textBrowser_2->toPlainText().toStdString());
	ptr->dataInput = ui.testCasesBrowser->toPlainText().toStdString();
	ptr->lang = snipsets[ui.comboBox->currentText().toStdString()].first;
	ptr->questionID = questionID;
	ptr->titleSlug = titleSlug;

	RequestManager::getInstance()->runCode(std::move(ptr), std::bind(&TaskViewer::displayRunCodeResult, this, std::placeholders::_1));
}

void TaskViewer::on_submitBtn_clicked()
{
	ui.runCodeResultBrowser->clear();
	ui.tabWidget->setCurrentIndex(1);

	std::unique_ptr<CodeToRun> ptr = std::make_unique<CodeToRun>();
	ptr->code = StringUtiles::formatCodeString(ui.textBrowser_2->toPlainText().toStdString());
	ptr->dataInput = ui.testCasesBrowser->toPlainText().toStdString();
	ptr->lang = snipsets[ui.comboBox->currentText().toStdString()].first;
	ptr->questionID = questionID;
	ptr->titleSlug = titleSlug;

	RequestManager::getInstance()->runCode(std::move(ptr), std::bind(&TaskViewer::displayRunCodeResult, this, std::placeholders::_1), true);
}

void TaskViewer::findImages(std::string& context)
{
	static std::string pattern = "src=\"";
	size_t srcPos = 0, startingPos = 0;

	while (true)
	{
		srcPos = context.find(pattern, startingPos);

		if (srcPos == std::string::npos)
		{
			return;
		}

		auto endPos = context.find("\"", srcPos + pattern.size());

		auto address = context.substr(srcPos + pattern.size(), endPos - srcPos - pattern.size());

		auto fileName = CachedStorage::getInstance()->getFile(address);

		context.replace(srcPos + pattern.size(), endPos - srcPos - pattern.size(), fileName);

		startingPos = srcPos + 1;
	}
}

void TaskViewer::indexChanged(QString text)
{
	ui.textBrowser_2->setText(QString::fromStdString(snipsets[text.toStdString()].second));
}

TaskViewer::~TaskViewer()
{}

void TaskViewer::getData(std::string const& filePath)
{
	auto taskDescription = JsonManager::getProblemDescription(filePath);
	taskDescription.wait();
	auto taskDesc = taskDescription.get();
	findImages(taskDesc);
	ui.textBrowser->setText(QString::fromStdString(taskDesc));
	auto codeSnipsets = JsonManager::getCodeSnipsets(filePath);
	codeSnipsets.wait();
	snipsets = codeSnipsets.get();
	auto testCase = JsonManager::getTestCase(filePath);
	testCase.wait();
	auto testCaseStr = testCase.get();
	auto tSlugTask = JsonManager::getTitleSlug(filePath);
	tSlugTask.wait();
	titleSlug = tSlugTask.get();
	questionID = JsonManager::getQuestionID(filePath).get();


	size_t idx = 0;

	for (auto const& lang : snipsets)
	{
		ui.comboBox->addItem(QString::fromStdString(lang.first));
		ui.comboBox->setItemData(idx++, QBrush(Qt::white), Qt::TextColorRole);
	}

	if (!snipsets.empty())
	{
		ui.textBrowser_2->setText(QString::fromStdString(snipsets.begin()->second.second));
	}
	else
	{
		ui.textBrowser_2->clear();
		ui.comboBox->clear();
	}

	if (testCaseStr.empty())
	{
		ui.testCasesBrowser->clear();
	}
	else
	{
		ui.testCasesBrowser->setText(QString::fromStdString(testCaseStr));
	}

	ui.runCodeResultBrowser->clear();
	wTool->UpdateActiveWindow(this);
}

std::shared_ptr<TaskViewer> TaskViewer::getInstance()
{
	static std::shared_ptr<TaskViewer> viewer = std::shared_ptr<TaskViewer>(new TaskViewer());
	return viewer;
}
