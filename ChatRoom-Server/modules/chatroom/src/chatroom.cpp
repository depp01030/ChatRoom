#include "chatroom.h"
#include "ui_chatroom.h"
ChatRoom::ChatRoom(QWidget *parent, ServerUtils *server)
    : QWidget(parent)
    , ui(new Ui::ChatRoom)
    , m_server(server)
{
    
    ui->setupUi(this);
    setupConnection();
    
}
ChatRoom::~ChatRoom()
{
    delete ui;
    delete m_server;
}
void ChatRoom::setupConnection(){
    // Connect the button's clicked signal to the onButtonClicked slot
    connect(ui->pushButton_send, &QPushButton::clicked, this, &ChatRoom::onSendButtonClicked);
    
    connect(m_server, QOverload<const QString&>::of(&ServerUtils::messageReceived), 
            this, QOverload<const QString&>::of(&ChatRoom::updateChatBox));
    connect(m_server, QOverload<const MessageData&>::of(&ServerUtils::messageReceived), 
            this, QOverload<const MessageData&>::of(&ChatRoom::updateChatBox));   
    connectChatTextEdit();
}
void ChatRoom::connectChatTextEdit()
{
    if (ui->textEdit_message) {
        connect(ui->textEdit_message, &ChatTextEdit::enterPressed, this, &ChatRoom::onSendButtonClicked);
    } else {
        qDebug() << "textEdit_message not found";
    }
}
void ChatRoom::onSendButtonClicked()
{   
    QString message = ui->textEdit_message->toPlainText();
    ui->textEdit_message->clear();
    m_server->sendMessage(message);
}



void ChatRoom::updateChatBox(const QString &message){
    ui->textBrowser_chat_window->append(ChatMessage(message));
}
void ChatRoom::updateChatBox(const MessageData &messageData){
    ui->textBrowser_chat_window->append(ChatMessage(messageData));
}


