#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "network_data_manager/include/network_data_manager.h"
#include "chatroom/include/chatroom.h"
#include "game_screen/include/game_screen.h"

 

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
    GameScreen *m_gameScreen;
    void setupUi();
    void loadTheme();
    void setupClickedEvent();
    void setupWidgets(QWidget *placeholder, QWidget *widget);
    void setupChatRoom();  
    void setupGameScreen();  
};

#endif // MAINWINDOW_H