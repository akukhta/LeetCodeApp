#include "LoginWidget.h"

LoginWidget::LoginWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->setPixmap(QPixmap(":/icons/logo.svg"));
	setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint);
}

LoginWidget::~LoginWidget()
{}

void LoginWidget::on_closeBtn_clicked()
{
	QApplication::quit();
}

void LoginWidget::on_guestBtn_clicked()
{
	w = new LeetCodeDesktop();
	w->show();
	close();
}

void LoginWidget::on_loginBtn_clicked()
{
	QFile::copy(":/scripts/login", "login.pyw");

	QProcess process;
	process.start("python.exe", { "login.pyw" });
	process.waitForFinished();

	std::filesystem::remove("login.pyw");
	CookieHandler::getInstance()->loadCookiesFromFile("cookies");
	std::filesystem::remove("cookies");

	w = new LeetCodeDesktop();
	w->show();
	close();
}
