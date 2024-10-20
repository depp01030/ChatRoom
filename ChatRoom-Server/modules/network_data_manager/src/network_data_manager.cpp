#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
// #include <QNetworkAccessManager>
// #include <QNetworkRequest>
#include <QNetworkReply> 
#include <Qstring>
#include <QEventLoop>
#include "network_data_manager.h"

NetworkDataManager::NetworkDataManager(QObject *parent) 
    : QObject(parent),
      m_isLoggedIn(false),
      m_server(new QTcpServer(this)),
      // m_socket = new QTcpSocket(this);
      m_httpServer(new QHttpServer(this)),
      m_messageProcesser(new MessageProcesser(this)),
      m_networkManager(new QNetworkAccessManager(this)),
      m_user(new User("Server", m_server->serverAddress().toString()))
{
    startServer(); 
    startHttpServer(); 
}  
NetworkDataManager::~NetworkDataManager(){
    delete m_server;
    delete m_httpServer;
    delete m_networkManager;
}
void NetworkDataManager::startServer(){
    if(m_server->isListening()){
        return;
    }
    m_server->listen(QHostAddress("127.0.0.1"), 1234);
    connect(m_server, &QTcpServer::newConnection, this, &NetworkDataManager::onNewConnection);
}
void NetworkDataManager::startHttpServer(){
    // m_httpServer->route("/login", QHttpServerRequest::Method::Post,
    // [this](const QHttpServerRequest &request){
    //     return handleHttpRequest(request);
        
    // });
    // m_httpServer->listen(QHostAddress("127.0.0.1"), 8080);
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


void NetworkDataManager::onNewConnection() {
    QTcpSocket* client_socket = m_server->nextPendingConnection();
    connect(client_socket, &QTcpSocket::readyRead, this, &NetworkDataManager::onReceivingMessageFromLocal);
    connect(client_socket, &QTcpSocket::disconnected, this, &NetworkDataManager::onDisconnected);
    qDebug() << "New connection";
    // 發送歡迎消息
    QJsonObject welcomeMsg;
    welcomeMsg["type"] = "system";
    welcomeMsg["content"] = "Please login for chatting";
    // client_socket->write(QJsonDocument(welcomeMsg).toJson());
    m_authenticatedUsers[client_socket] = client_socket->peerAddress().toString();
    
}

void NetworkDataManager::onDisconnected() {
    // Handle disconnected
}



void NetworkDataManager::onSendingMessageToServer(const QJsonObject& jsonObj) {
    try{
        //qDebug() << "Received message from local: " << jsonObj;
        QJsonObject messageObj = m_messageProcesser->messageWrapper(jsonObj);

        // QString userID = messageObj["userID"].toString();
        // QString chatMessage = userID + ": " + messageObj["content"].toString(); 
        // emit updateChatBox(chatMessage);

        QByteArray message = m_messageProcesser->messageObjToByteArray(messageObj);
        sendMessageToServer(message);
    }catch(const std::exception& e){
        qDebug() << "Error: " << e.what();
    }
} 
void NetworkDataManager::onReceivingMessageFromServer( ) {
    qDebug() << "onMessageReceivedFromServer";
    QByteArray data = m_socket->readAll();
    m_messageProcesser->processSocketMessage(data); 
} 
void NetworkDataManager::onReceivingMessageFromLocal()
{
    std::cout << "messageReceived" << std::endl;
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        std::cout << "socket is null" << std::endl;
        return; 
    }
    QByteArray data = socket->readAll(); 
    m_messageProcesser->processSocketMessage(data); 
    
}
void NetworkDataManager::sendMessageToServer(const QByteArray& message) {
    m_messageProcesser->processSocketMessage(message); 
    // broadcastMessage(message);
}  
void NetworkDataManager::broadcastMessage(const QJsonObject& messageObject)
{
    QByteArray message = m_messageProcesser->messageObjToByteArray(messageObject);
    for (auto &client: m_authenticatedUsers){
        qDebug() << "send message to client :"  << client.first->peerAddress().toString();
        client.first->write(message);
    }
}
