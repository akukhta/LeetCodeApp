/********************************************************************************
** Form generated from reading UI file 'WindowTool.ui'
**
** Created by: Qt User Interface Compiler version 5.9.9
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOWTOOL_H
#define UI_WINDOWTOOL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowToolClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *profileBtn;
    QLabel *label;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *schrinkBtn;
    QPushButton *closeBtn;
    QSpacerItem *verticalSpacer;

    void setupUi(QMainWindow *WindowToolClass)
    {
        if (WindowToolClass->objectName().isEmpty())
            WindowToolClass->setObjectName(QStringLiteral("WindowToolClass"));
        WindowToolClass->resize(597, 83);
        centralWidget = new QWidget(WindowToolClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        profileBtn = new QPushButton(centralWidget);
        profileBtn->setObjectName(QStringLiteral("profileBtn"));
        profileBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"	    icon-size: 50px 50px;\n"
"		border:none;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background: 2px solid  rgb(80, 80, 122);\n"
"}"));
        QIcon icon;
        icon.addFile(QStringLiteral("Res/profile.png"), QSize(), QIcon::Normal, QIcon::Off);
        profileBtn->setIcon(icon);

        horizontalLayout->addWidget(profileBtn);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        font.setPointSize(12);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("QLabel { \n"
"border: none;\n"
"color : rgb(255, 255, 255);\n"
"}"));

        horizontalLayout->addWidget(label);

        horizontalSpacer_7 = new QSpacerItem(411, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_7);

        schrinkBtn = new QPushButton(centralWidget);
        schrinkBtn->setObjectName(QStringLiteral("schrinkBtn"));
        schrinkBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"		border:none;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background-color: rgb(80, 80, 122);\n"
"}"));
        QIcon icon1;
        icon1.addFile(QStringLiteral("Res/shrink.png"), QSize(), QIcon::Normal, QIcon::Off);
        schrinkBtn->setIcon(icon1);

        horizontalLayout->addWidget(schrinkBtn);

        closeBtn = new QPushButton(centralWidget);
        closeBtn->setObjectName(QStringLiteral("closeBtn"));
        closeBtn->setStyleSheet(QLatin1String("QPushButton\n"
"{\n"
"		border:none;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"background-color: rgb(80, 80, 122);\n"
"}"));
        QIcon icon2;
        icon2.addFile(QStringLiteral("Res/closeIcon.png"), QSize(), QIcon::Normal, QIcon::Off);
        closeBtn->setIcon(icon2);

        horizontalLayout->addWidget(closeBtn);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);


        verticalLayout_2->addLayout(verticalLayout);

        WindowToolClass->setCentralWidget(centralWidget);

        retranslateUi(WindowToolClass);

        QMetaObject::connectSlotsByName(WindowToolClass);
    } // setupUi

    void retranslateUi(QMainWindow *WindowToolClass)
    {
        WindowToolClass->setWindowTitle(QApplication::translate("WindowToolClass", "WindowTool", Q_NULLPTR));
        profileBtn->setText(QString());
        label->setText(QApplication::translate("WindowToolClass", "Guest", Q_NULLPTR));
        schrinkBtn->setText(QString());
        closeBtn->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class WindowToolClass: public Ui_WindowToolClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOWTOOL_H
