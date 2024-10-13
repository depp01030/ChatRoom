#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network_data_manager/include/network_data_manager.h"
#include "chatroom/include/chatroom.h"
#include "game_controller/include/game_controller.h"

 

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;
    NetworkDataManager *m_server;
    ChatRoom *m_chatRoom;  
    GameController *m_gameController;
    void setupUi();
    void loadTheme();
    void setupClickedEvent();
    void setupWidgets(QWidget *placeholder, QWidget *widget);
 
};

#endif // MAINWINDOW_H