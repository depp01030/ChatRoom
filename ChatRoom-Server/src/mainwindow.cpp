#include "../include/mainwindow.h"
#include "../include/server_utils.h"
#include "ui_mainwindow.h"
#include <QFile>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_server(new ServerUtils)
{
    ui->setupUi(this);

    // Apply dark theme
    loadTheme();

    connect(m_server, QOverload<const QString&>::of(&ServerUtils::messageReceived), 
            this, QOverload<const QString&>::of(&MainWindow::updateChatBox));
    connect(m_server, QOverload<const MessageData&>::of(&ServerUtils::messageReceived), 
            this, QOverload<const MessageData&>::of(&MainWindow::updateChatBox));   
    setupClickedEvent();
    connectChatTextEdit();  // 添加這行
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_server;
}

void MainWindow::loadTheme()
{
    QFile file(":/darktheme.qss");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream stream(&file);
        this->setStyleSheet(stream.readAll());
    }
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
    m_server->sendMessage(message);
}



void MainWindow::updateChatBox(const QString &message){
    ui->textBrowser_chat_window->append(ChatMessage(message));
}
void MainWindow::updateChatBox(const MessageData &messageData){
    ui->textBrowser_chat_window->append(ChatMessage(messageData));
}

void MainWindow::connectChatTextEdit()
{
    if (ui->textEdit_message) {
        connect(ui->textEdit_message, &ChatTextEdit::enterPressed, this, &MainWindow::onButtonClicked);
    } else {
        qDebug() << "textEdit_message not found";
    }
}

