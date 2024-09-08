#include "../include/mainwindow.h"
#include "client_utils.h"  // Updated include
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_client(new ClientUtils)  // Updated to ClientUtils
{
    ui->setupUi(this); 
    connect(m_client, &ClientUtils::messageReceived, this, &MainWindow::updateChatBox);
    setupClickedEvent();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupClickedEvent()
{
    // Connect the button's clicked signal to the onButtonClicked slot
    connect(ui->pushButton_send, &QPushButton::clicked, this, &MainWindow::onButtonClicked);
    
}

void MainWindow::onButtonClicked()
{   
    QString message = ui->textEdit_message->toPlainText();
    ui->textEdit_message->clear();
    m_client->sendMessage(message);

}
void MainWindow::updateChatBox(const QString &message){
    ui->textBrowser_chat_window->append(message);
}
