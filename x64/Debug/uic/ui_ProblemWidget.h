/********************************************************************************
** Form generated from reading UI file 'ProblemWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROBLEMWIDGET_H
#define UI_PROBLEMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProblemWidgetClass
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *verticalLayout;
    QLabel *nameLabel;
    QHBoxLayout *horizontalLayout_2;
    QLabel *difficultyLabel;
    QLabel *acceptanceLabel;

    void setupUi(QMainWindow *ProblemWidgetClass)
    {
        if (ProblemWidgetClass->objectName().isEmpty())
            ProblemWidgetClass->setObjectName(QStringLiteral("ProblemWidgetClass"));
        ProblemWidgetClass->resize(563, 111);
        ProblemWidgetClass->setAutoFillBackground(false);
        ProblemWidgetClass->setStyleSheet(QStringLiteral(""));
        ProblemWidgetClass->setAnimated(true);
        ProblemWidgetClass->setDocumentMode(false);
        ProblemWidgetClass->setTabShape(QTabWidget::Rounded);
        ProblemWidgetClass->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
        centralWidget = new QWidget(ProblemWidgetClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        nameLabel = new QLabel(centralWidget);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(15);
        nameLabel->setFont(font);
        nameLabel->setStyleSheet(QStringLiteral("color: white"));

        verticalLayout->addWidget(nameLabel);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        difficultyLabel = new QLabel(centralWidget);
        difficultyLabel->setObjectName(QStringLiteral("difficultyLabel"));
        difficultyLabel->setFont(font);
        difficultyLabel->setStyleSheet(QStringLiteral("color: white"));

        horizontalLayout_2->addWidget(difficultyLabel);

        acceptanceLabel = new QLabel(centralWidget);
        acceptanceLabel->setObjectName(QStringLiteral("acceptanceLabel"));
        acceptanceLabel->setFont(font);
        acceptanceLabel->setStyleSheet(QStringLiteral("color: white"));

        horizontalLayout_2->addWidget(acceptanceLabel);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 0, 0, 1, 1);

        ProblemWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(ProblemWidgetClass);

        QMetaObject::connectSlotsByName(ProblemWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProblemWidgetClass)
    {
        ProblemWidgetClass->setWindowTitle(QApplication::translate("ProblemWidgetClass", "ProblemWidget", Q_NULLPTR));
        nameLabel->setText(QApplication::translate("ProblemWidgetClass", "Name", Q_NULLPTR));
        difficultyLabel->setText(QApplication::translate("ProblemWidgetClass", "Difficulty", Q_NULLPTR));
        acceptanceLabel->setText(QApplication::translate("ProblemWidgetClass", "Acceptance", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class ProblemWidgetClass: public Ui_ProblemWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROBLEMWIDGET_H
