#include "../include/server_utils.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <Qstring>
ServerUtils::ServerUtils(QObject *parent) : QObject(parent),
    m_server(new QTcpServer(this)),
    m_httpServer(new QHttpServer(this)) { 
    startServer();
    startHttpServer();
}



void ServerUtils::startServer(){
    if(m_server->isListening()){
        return;
    }
    m_server->listen(QHostAddress::Any, 1234);
    connect(m_server, &QTcpServer::newConnection, this, &ServerUtils::slot_onNewConnection);
}

void ServerUtils::startHttpServer(){
    m_httpServer->route("/login", QHttpServerRequest::Method::Post,
    [this](const QHttpServerRequest &request){
        return handleHttpRequest(request);
        
    });
    m_httpServer->listen(QHostAddress::Any, 8080);
}
QHttpServerResponse ServerUtils::handleHttpRequest(const QHttpServerRequest &request) {
 
    if (request.url().path() == "/login"){
        QJsonObject responseData = {
            {"type", "system"},
            {"success", false},
            {"message", "Login successful"}
        };
        QJsonObject jsonObj = QJsonDocument::fromJson(request.body()).object();
        QString username = jsonObj["username"].toString();
        QString password = jsonObj["password"].toString();
        if (isLoginSuccess(username, password)){ 
            responseData["success"] = true;       
            QString clientIp = request.remoteAddress().toString();  
            m_authenticatedIP[clientIp] = username;
            std::cout << "Login successful" << std::endl;
        }
        else{
            std::cout << "Login failed" << std::endl;
            std::cout << "Username: " << username.toStdString() << std::endl;
            std::cout << "Password: " << password.toStdString() << std::endl;
        }
        QJsonDocument doc(responseData);
        QByteArray jsonData = doc.toJson();
        QHttpServerResponse response(jsonData, QHttpServerResponder::StatusCode::Ok);
        response.setHeader("Content-Type", "application/json");
 
        return response;
    }
    else{
        QHttpServerResponse response(QHttpServerResponder::StatusCode::NotFound);
        return response;
    }

}

bool ServerUtils::isLoginSuccess(const QString& username, const QString& password){
        
    auto it = m_users.find(username);
    if (it != m_users.end() and it->second == password){
        return true;

    }
    return false;

    
}
void ServerUtils::slot_onNewConnection() {
    QTcpSocket* client_socket = m_server->nextPendingConnection();
    connect(client_socket, &QTcpSocket::readyRead, this, &ServerUtils::slot_messageReceived);
    connect(client_socket, &QTcpSocket::disconnected, this, &ServerUtils::slot_handleDisconnection);

    // 發送歡迎消息
    QJsonObject welcomeMsg;
    welcomeMsg["type"] = "system";
    welcomeMsg["content"] = "Please login for chatting";
    client_socket->write(QJsonDocument(welcomeMsg).toJson());
    if (isIPAuthenticated(client_socket->peerAddress().toString())){
        m_authenticatedUsers[client_socket] = client_socket->peerAddress().toString();
    }
    else{
        m_unauthenticatedUsers[client_socket] = client_socket->peerAddress().toString();
    }
}
 
bool ServerUtils::isIPAuthenticated(const QString& ipAddress) const {
    return m_authenticatedIP.find(ipAddress) != m_authenticatedIP.end();
}
void ServerUtils::slot_handleDisconnection() {
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (m_authenticatedUsers.find(socket) != m_authenticatedUsers.end()){
        m_authenticatedUsers.erase(socket);
    }
    if (m_unauthenticatedUsers.find(socket) != m_unauthenticatedUsers.end()){
        m_unauthenticatedUsers.erase(socket);
    }
    if (m_authenticatedIP.find(socket->peerAddress().toString()) != m_authenticatedIP.end()){
        m_authenticatedIP.erase(socket->peerAddress().toString());
    }

}

void ServerUtils::slot_messageReceived()
{
    std::cout << "messageReceived" << std::endl;
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        std::cout << "socket is null" << std::endl;
        return; 
    }
    QByteArray data = socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    
    if (doc.isNull()) {
        std::cout << "doc is null" << std::endl;
        return;
    }
    
    QJsonObject jsonObj = doc.object();
    QString type = jsonObj["type"].toString();
    if (isUserAuthenticated(socket)) {
        std::cout << "isUserAuthenticated" << std::endl;
        if (type == "message"){
            QString message = jsonObj["content"].toString();
            std::cout << "message: " << message.toStdString() << std::endl;
            emit messageReceived(message);
            broadcastMessage(message);
        }
    }
    else { 
        std::cout << "isUserAuthenticated false" << std::endl;
        QJsonObject response;
        response["type"] = "error";
        response["message"] = "You must login first";
        socket->write(QJsonDocument(response).toJson());
    }
}

 
bool ServerUtils::isUserAuthenticated(QTcpSocket* socket) const {
    return m_authenticatedUsers.find(socket) != m_authenticatedUsers.end();
}
void ServerUtils::broadcastMessage(const QString& message)
{
    QJsonObject messageObj;
    messageObj["type"] = "message";
    messageObj["content"] = message;
    
    QJsonDocument doc(messageObj);
    QByteArray jsonData = doc.toJson();

 
   
    for (auto &client: m_authenticatedUsers){
        client.first->write(jsonData);
    }
    
    for (auto &client: m_unauthenticatedUsers){
        client.first->write(jsonData);
    }
}



void ServerUtils::sendMessage(const QString& message)
{
    emit messageReceived(message);
    broadcastMessage(message);
}