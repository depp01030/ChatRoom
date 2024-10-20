#include <iostream>
// #include <QNetworkAccessManager>
// #include <QNetworkRequest>
#include <QNetworkReply>
#include <Qstring>
#include <QEventLoop> 
#include "network_data_manager.h" 

NetworkDataManager::NetworkDataManager(QObject *parent)
    : QObject(parent),
      m_isLoggedIn(false),
      m_socket(new QTcpSocket(this)),
      m_messageProcesser(new MessageProcesser(this)),
      m_networkManager(new QNetworkAccessManager(this)),
      m_user(new User("A", m_socket->peerAddress().toString()))
{
    connectToServer();
    connect(m_socket, &QTcpSocket::connected, this, &NetworkDataManager::onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &NetworkDataManager::onReceivingMessageFromServer);
    connect(m_socket, &QTcpSocket::disconnected, this, &NetworkDataManager::onDisconnected); 
    // Constructor implementation
}
NetworkDataManager::~NetworkDataManager()
{
    if (m_socket) {
        m_socket->disconnectFromHost();
        delete m_socket;
    }
    if (m_networkManager) {
        delete m_networkManager;
    }
}
void NetworkDataManager::onConnected() {
    // Handle new connection
    std::cout << "Connected to server" << std::endl;

}
void NetworkDataManager::connectToServer() {
    m_socket->connectToHost("127.0.0.1", 1234);  
}

void NetworkDataManager::onDisconnected() {
    // Handle disconnected
}

// bool NetworkDataManager::login(const QString& username, const QString& password) {
//     QJsonObject loginData;
//     loginData["username"] = username;
//     loginData["password"] = password;
//     QJsonDocument doc(loginData);

//     QNetworkRequest request(QUrl("http://127.0.0.1:8080/login"));
//     request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

//     QNetworkReply* reply = m_networkManager->post(request, doc.toJson());
    
//     QEventLoop loop;
//     connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
//     loop.exec();

//     QByteArray response = reply->readAll();
//     std::cout << "Response: " << response.toStdString() << std::endl;
//     QJsonObject responseObj = QJsonDocument::fromJson(response).object();
//     m_isLoggedIn = responseObj["success"].toBool();
//     std::cout << "Login result: " << m_isLoggedIn << std::endl;
//     return m_isLoggedIn;
// }

void NetworkDataManager::onSendingMessageToServer(const QJsonObject& jsonObj) {
    //qDebug() << "Received message from local: " << jsonObj;
    qDebug() << "onSendingMessageToServer : " << jsonObj;
    QJsonObject messageObj = m_messageProcesser->messageWrapper(jsonObj); 

    // QString userID = messageObj["userID"].toString();
    // QString chatMessage = userID + ": " + messageObj["content"]["message"].toString(); 
    // emit updateChatBox(chatMessage);

    QByteArray message = m_messageProcesser->messageObjToByteArray(messageObj);
    sendMessageToServer(message);
} 
void NetworkDataManager::sendMessageToServer(const QByteArray& message) {
    m_socket->write(message);
} 
void NetworkDataManager::onReceivingMessageFromServer( ) {
    qDebug() << "onMessageReceivedFromServer";
    QByteArray data = m_socket->readAll();
    m_messageProcesser->processSocketMessage(data); 
} 
void NetworkDataManager::broadcastMessage(const QJsonObject& messageObject){
    return;
}
