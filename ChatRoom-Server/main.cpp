#include "modules/mainwindow/include/mainwindow.h"
#include "modules/game_screen/include/game_screen.h"
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
