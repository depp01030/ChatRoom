#include "mainwindow.h"
#include "server_utils/include/client_utils.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(new ServerUtils)
    , m_chatRoom(nullptr)  // 初始化为 nullptr 
{
    
    _setupUi();
    setupClickedEvent(); 
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_server;
    delete m_chatRoom;  
    // delete m_gameScreen;   
}
void MainWindow::_setupUi()
{
    
    ui->setupUi(this);
    // Apply dark theme
    loadTheme(); 
    setupChatRoom();   
    // setupGameScreen();   

}
void MainWindow::loadTheme()
{ 
    QFile file(":/darktheme.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        this->setStyleSheet(stream.readAll());
    }
}
void MainWindow::setupChatRoom() 
{
    // Create the ChatRoom
    m_chatRoom = new ChatRoom(this, m_server);
    
    // Find the placeholder widget in the UI
    QWidget *placeholder = ui->chatRoomPlaceholder;   

    // Create a layout for the placeholder
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    
    // Add the ChatRoom to the layout
    layout->addWidget(m_chatRoom);
    
    // Set the layout to the placeholder
    placeholder->setLayout(layout);
}

// void MainWindow::setupGameScreen()
// {
//     // Create the GameScreen
//     m_gameScreen = new GameScreen(this, m_server);
    
//     // Find the placeholder widget in the UI
//     QWidget *placeholder = ui->gameScreenPlaceholder;  
    
//     // Create a layout for the placeholder
//     QVBoxLayout *layout = new QVBoxLayout(placeholder);
    
//     // Add the m_gameScreen to the layout
//     layout->addWidget(m_gameScreen);
    
//     // Set the layout to the placeholder
//     placeholder->setLayout(layout);
// }


void MainWindow::setupClickedEvent()
{

}