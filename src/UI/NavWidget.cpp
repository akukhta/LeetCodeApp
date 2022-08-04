#include "NavWidget.h"

QString const NavWidget::sep = "/";

NavWidget::NavWidget(size_t pagesCount, std::function<void(size_t)> callback, QWidget* parent)
	: pagesCount(pagesCount), QWidget(parent), callback(callback)
{
	ui.setupUi(this);
	ui.prevPage_btn->setIcon(QPixmap(":/icons/leftArrow.png"));
	ui.nextPage_btn->setIcon(QPixmap(":/icons/arrow.png"));
	ui.label->setText(sep + QString::number(pagesCount));
	ui.prevPage_btn->setEnabled(false);
}

NavWidget::~NavWidget()
{}

void NavWidget::on_nextPage_btn_clicked()
{
	if (currentPage < pagesCount)
	{
		if (currentPage == 1)
		{
			ui.prevPage_btn->setEnabled(true);
		}

		currentPage++;

		if (currentPage == pagesCount)
		{
			ui.nextPage_btn->setEnabled(false);
		}

		ui.lineEdit->setText(QString::number(currentPage));
	
		if (callback)
		{
			callback(currentPage);
		}
	}
}

void NavWidget::on_prevPage_btn_clicked()
{
	if (currentPage > 1)
	{
		if (currentPage == pagesCount)
		{
			ui.nextPage_btn->setEnabled(true);
		}

		currentPage--;
		ui.lineEdit->setText(QString::number(currentPage));

		if (currentPage == 1)
		{
			ui.prevPage_btn->setEnabled(false);
		}

		if (callback)
		{
			callback(currentPage);
		}
	}
}
