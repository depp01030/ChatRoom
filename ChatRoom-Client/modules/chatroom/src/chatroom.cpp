#include "chatroom.h"
#include "ui_chatroom.h"
ChatRoom::ChatRoom(QWidget *parent, NetworkDataManager *server)
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
    connect(ui->textEdit_message, &ChatTextEdit::enterPressed, this, &ChatRoom::onSendButtonClicked);
    connect(this, &ChatRoom::sendMessageToServer, m_server, &NetworkDataManager::postMessageToServer);

    connect(m_server, QOverload<const QString&>::of(&NetworkDataManager::updateChatBox), 
            this, QOverload<const QString&>::of(&ChatRoom::onUpdateChatBox));
    // connect(m_server, QOverload<const MessageData&>::of(&NetworkDataManager::messageReceivedFromServer), 
    //         this, QOverload<const MessageData&>::of(&ChatRoom::onUpdateChatBox));   
 
}
 
void ChatRoom::onSendButtonClicked()
{   
    QString message = ui->textEdit_message->toPlainText();
    ui->textEdit_message->clear();
    emit sendMessageToServer(message); 
}



void ChatRoom::onUpdateChatBox(const QString &message){
    ui->textBrowser_chat_window->append(ChatMessage(message));
}
void ChatRoom::onUpdateChatBox(const MessageData &messageData){
    ui->textBrowser_chat_window->append(ChatMessage(messageData));
}


