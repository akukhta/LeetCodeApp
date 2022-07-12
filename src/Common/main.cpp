#include "../../src/UI/LeetCodeDesktop.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LeetCodeDesktop w;
    w.show();
    return a.exec();
}
