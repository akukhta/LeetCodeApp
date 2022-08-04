#pragma once

#include <QtWidgets/QMainWindow>
#include <unordered_map>
#include "ui_LeetCodeDesktop.h"
#include "WindowTool.h"
#include "ProblemWidget.h"
#include "../../src/API/RequestManager.h"
#include "../../src/Data/JsonManager.h"
#include "../../src/UI/NavWidget.h"

class LeetCodeDesktop : public QMainWindow
{
    Q_OBJECT

public:
    LeetCodeDesktop(QWidget *parent = nullptr);
    ~LeetCodeDesktop();

private:
    Ui::LeetCodeDesktopClass ui;
    size_t const questionsPerPage = 50;
    size_t pagesCount;
    std::string loadPage(size_t pageNum);
    void loadProblemsFromFile(std::string path);
    void navWidBtn(size_t pageNum);
    void createProblemWidgets();
};
