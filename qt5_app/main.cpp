#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    q0 = 0, q1 = 90, q2 = 90, q3 = 0;

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
