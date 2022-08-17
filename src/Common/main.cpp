#include "../../src/UI/LeetCodeDesktop.h"
#include "../../src/UI/LoginWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LoginWidget w;
    w.show();
    return a.exec();
}
