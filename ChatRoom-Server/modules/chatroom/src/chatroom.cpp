#include "chatroom.h"
#include "ui_chatroom.h"
ChatRoom::ChatRoom(QWidget *parent, NetworkDataManager *networkDataManager)
    : QWidget(parent)
    , ui(new Ui::ChatRoom)
    , m_networkDataManager(networkDataManager)
{
    
    ui->setupUi(this);
    setupConnection();
    
}
ChatRoom::~ChatRoom()
{
    delete ui;
}
void ChatRoom::setupConnection(){
    // Connect the button's clicked signal to the onButtonClicked slot
    connect(ui->pushButton_send, &QPushButton::clicked, this, &ChatRoom::onSendButtonClicked);
    connect(ui->textEdit_message, &ChatTextEdit::enterPressed, this, &ChatRoom::onSendButtonClicked); 
    
    connect(this, &ChatRoom::sendChatMessageToServer, m_networkDataManager, &NetworkDataManager::onSendingMessageToServer);
    connect(m_networkDataManager, QOverload<const QString&>::of(&NetworkDataManager::updateChatBox), 
            this, QOverload<const QString&>::of(&ChatRoom::onUpdateChatBox));
    // connect(m_server, QOverload<const MessageData&>::of(&NetworkDataManager::messageReceivedFromServer), 
    //         this, QOverload<const MessageData&>::of(&ChatRoom::onUpdateChatBox));   
 
}
 
void ChatRoom::onSendButtonClicked()
{   
    QJsonObject messageObject = {
        {"type", static_cast<int>(MessageType::ChatMessage)},
        {"message", ui->textEdit_message->toPlainText()}, 
    }; 

    emit sendChatMessageToServer(messageObject); 
    ui->textEdit_message->clear();
} 

void ChatRoom::onUpdateChatBox(const QString &message){
    ChatMessage chatMessage(message);
    qDebug() << chatMessage.getFormattedMessage();
    ui->textBrowser_chat_window->append(chatMessage.getFormattedMessage());
}



