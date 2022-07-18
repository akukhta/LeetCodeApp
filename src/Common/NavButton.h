#pragma once
#include <qpushbutton.h>
#include <vector>

class NavButton : public QPushButton
{
	Q_OBJECT

public:
	NavButton(unsigned short id, QString const &text = "");
	void setActive();
	void setUnactive();

private slots:
	void on_NavButton_click();

private:
	bool active = false;
	static QString const btnStyleSheet;
	static QString const btnStyleSheetInverted;
	static std::vector<NavButton*> navBtns;
	static NavButton* activeButton;
	unsigned short id;
};

