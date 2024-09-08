#include "../include/mainwindow.h"
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    int i = 0;
    i++;
    i++;
    w.show();
    return a.exec();
}
