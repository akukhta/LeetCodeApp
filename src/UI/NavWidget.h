#pragma once

#include <QWidget>
#include <functional>
#include "ui_NavWidget.h"

class NavWidget : public QWidget
{
	Q_OBJECT

public:
	NavWidget(size_t pagesCount = 999, std::function<void(size_t)> callback = std::function<void(size_t)>(), QWidget *parent = nullptr);
	~NavWidget();

private slots:
	void on_prevPage_btn_clicked();
	void on_nextPage_btn_clicked();

private:
	Ui::NavWidgetClass ui;
	size_t pagesCount;
	size_t currentPage = 1;
	static QString const sep;
	std::function<void(size_t)> callback;
};
