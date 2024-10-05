#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "server_utils/include/client_utils.h"
#include "chatroom/include/chatroom.h"
// #include "game_screen/include/game_screen.h"

 

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
    ServerUtils *m_server;
    ChatRoom *m_chatRoom;  
    // GameScreen *m_gameScreen;
    void _setupUi();
    void loadTheme();
    void setupClickedEvent();
    void setupChatRoom();  
    // void setupGameScreen();  
};

#endif // MAINWINDOW_H