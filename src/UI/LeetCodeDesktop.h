#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_LeetCodeDesktop.h"
#include "WindowTool.h"
#include "ProblemWidget.h"
#include "../../src/API/RequestManager.h"
#include "../../src/Data/JsonManager.h"
#include "../../src/Common/Task.h"

class LeetCodeDesktop : public QMainWindow
{
    Q_OBJECT

public:
    LeetCodeDesktop(QWidget *parent = nullptr);
    ~LeetCodeDesktop();

private:
    Ui::LeetCodeDesktopClass ui;
};
