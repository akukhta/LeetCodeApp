#include "NavButton.h"

QString const NavButton::btnStyleSheet = "QPushButton {background-color: rgb(45, 45, 68); border-radius: 6px; color: white; } QPushButton:hover:!pressed{background-color: rgb(255, 255, 255); border-radius: 6px; color: black;}";
QString const NavButton::btnStyleSheetInverted = "QPushButton {background-color: rgb(255, 255, 255); border-radius: 6px; color: black;}";
NavButton* NavButton::activeButton = nullptr;
std::vector<NavButton*> NavButton::navBtns = std::vector<NavButton*>();

NavButton::NavButton(unsigned short id, QString const &text)
{
	this->id = id;
	setFixedSize(30, 30);
	setText(text);
	setStyleSheet(btnStyleSheet);
	connect(this, SIGNAL(clicked()), this, SLOT(on_NavButton_click()));
	navBtns.push_back(this);
}

void NavButton::setActive()
{
	activeButton = this;
	setStyleSheet(btnStyleSheetInverted);
}

void NavButton::setUnactive()
{
	setStyleSheet(btnStyleSheet);
}

void NavButton::on_NavButton_click()
{
	if (this != activeButton)
	{
		activeButton->setUnactive();
		setActive();
		activeButton = this;
	}

}