#include "../include/mainwindow.h"
#include "../include/client_utils.h"
#include "../include/logindialog.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_client(new ClientUtils(this))
{

    ui->setupUi(this);  
    connect(m_client, &ClientUtils::messageReceived, this, &MainWindow::onMessageReceived);
    setupClickedEvent(); 

    // Show login dialog
    while (true) {
        LoginDialog loginDialog(this);
        if (loginDialog.exec() == QDialog::Accepted) {
            QString username = loginDialog.getUsername();
            QString password = loginDialog.getPassword(); 
            if (m_client->login(username, password)) {
                std::cout << "Login successful" << std::endl;
                break;  // Exit the loop if login is successful
            } else {
                std::cout << "Login failed, please try again." << std::endl;
            }
        } else {
            std::cout << "Login cancelled" << std::endl;
            QApplication::exit(-1);  // Exit the application if the login dialog is cancelled
            break;
        }
    }
    m_client->connectToServer();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete m_client;
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

bool MainWindow::get_login_status() const
{
    return m_client->m_isLoggedIn;  // 返回 m_client 的登錄狀態
}

void MainWindow::onMessageReceived(const QString& message){
    updateChatBox(message);
}
