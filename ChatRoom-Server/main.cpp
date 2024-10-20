#include "modules/mainwindow/include/mainwindow.h" 
#include <iostream>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    // GameScreen w ; 
    MainWindow w;
    w.show();
    return a.exec();
}
