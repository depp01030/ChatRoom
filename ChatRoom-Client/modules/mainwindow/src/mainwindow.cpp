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
    delete m_gameController;   
}
void MainWindow::setupUi()
{
    
    ui->setupUi(this);
    // Apply dark theme
    loadTheme(); 
    m_chatRoom = new ChatRoom(this, m_server);
    setupWidgets(ui->chatRoomPlaceholder, m_chatRoom);
    m_gameController = new GameController(this, m_server);
    setupWidgets(ui->gameScreenPlaceholder,
     m_gameController->m_gameScreen
    );
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


void MainWindow::setupClickedEvent()
{

}