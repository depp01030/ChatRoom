#include "mainwindow.h"
// #include "network_data_manager/include/network_data_manager.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(new NetworkDataManager)
{
    
    setupUi();
    setupClickedEvent(); 
}
MainWindow::~MainWindow()
{
    delete ui;
    delete m_server;
    delete m_chatRoom;  
    delete m_gameScreen;   
}
void MainWindow::setupUi()
{
    
    ui->setupUi(this);
    // Apply dark theme
    loadTheme(); 
    m_chatRoom = new ChatRoom(this, m_server);
    setupWidgets(ui->chatRoomPlaceholder, m_chatRoom);
    m_gameScreen = new GameScreen(this);
    setupWidgets(ui->gameScreenPlaceholder, m_gameScreen);
    // setupChatRoom();   
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

void MainWindow::setupWidgets(QWidget *placeholder, QWidget *widget){
 
    // Create a layout for the placeholder
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    
    // Add the ChatRoom to the layout
    layout->addWidget(widget);
    
    // Set the layout to the placeholder
    placeholder->setLayout(layout);
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

void MainWindow::setupGameScreen()
{
    // Create the GameScreen
    m_gameScreen = new GameScreen(this);
    
    // Find the placeholder widget in the UI
    QWidget *placeholder = ui->gameScreenPlaceholder;  
    
    // Create a layout for the placeholder
    QVBoxLayout *layout = new QVBoxLayout(placeholder);
    
    // Add the m_gameScreen to the layout
    layout->addWidget(m_gameScreen);
    
    // Set the layout to the placeholder
    placeholder->setLayout(layout);
}


void MainWindow::setupClickedEvent()
{

}