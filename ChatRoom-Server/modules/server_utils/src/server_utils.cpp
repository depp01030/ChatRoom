#include "../include/server_utils.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <Qstring>
#include <QColor>
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
    m_server->listen(QHostAddress("127.0.0.1"), 1234);
    connect(m_server, &QTcpServer::newConnection, this, &ServerUtils::onNewConnection);
}

void ServerUtils::startHttpServer(){
    m_httpServer->route("/login", QHttpServerRequest::Method::Post,
    [this](const QHttpServerRequest &request){
        return handleHttpRequest(request);
        
    });
    m_httpServer->listen(QHostAddress("127.0.0.1"), 8080);
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
void ServerUtils::onNewConnection() {
    QTcpSocket* client_socket = m_server->nextPendingConnection();
    connect(client_socket, &QTcpSocket::readyRead, this, &ServerUtils::onMessageReceived);
    connect(client_socket, &QTcpSocket::disconnected, this, &ServerUtils::onDisconnection);

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
void ServerUtils::onDisconnection() {
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

void ServerUtils::onMessageReceived()
{
    std::cout << "messageReceived" << std::endl;
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        std::cout << "socket is null" << std::endl;
        return; 
    }
    QByteArray data = socket->readAll();

    QString jsonString(data);

    QStringList jsonStrings = jsonString.split("\end");
    qDebug() << jsonStrings;
    for (const QString& str : jsonStrings) {
        // 如果字串不是空的
        if (!str.trimmed().isEmpty()) {
            // 嘗試解析 JSON
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            if (!doc.isNull()) {
                QJsonObject jsonObject = doc.object();
                qDebug() << "Parsed JSON:" << jsonObject;
                
                // 在這裡處理解析後的 JSON 對象
                // 例如，打印類型
                qDebug() << "Type:" << jsonObject["type"].toInt();
            }
        }
    }








    // qDebug() << data;
    // QJsonObject message = QJsonDocument::fromJson(data).object();
    // // MessageData messageData(obj);
    // // if (!messageData.status){
    // //     return;
    // // }
    // qDebug() << message["type"].toString();
    
    
    // if (isUserAuthenticated(socket)) { 
    //     // if (messageData.type == "message"){  
    //     //     emit messageReceived(messageData);
    //     //     broadcastMessage(messageData.toByteArray());
    //     // }
    // }
    // else { 
    //     std::cout << "User Not Login" << std::endl; 
    //     MessageData messageData(
    //         "error", "You must login first", "depp", "red"
    //      );
    //     socket->write(messageData.toByteArray());
    // }
}

 
bool ServerUtils::isUserAuthenticated(QTcpSocket* socket) const {
    return m_authenticatedUsers.find(socket) != m_authenticatedUsers.end();
}
QByteArray ServerUtils::packMessage(const QString& type, const QString& message){
    
    MessageData messageData(type, message, "depp", "red");
    QByteArray packedMessage = messageData.toByteArray();
    return packedMessage;
}
void ServerUtils::broadcastMessage(const QByteArray& packedMessage)
{
    for (auto &client: m_authenticatedUsers){
        client.first->write(packedMessage);
    }
    for (auto &client: m_unauthenticatedUsers){
        client.first->write(packedMessage);
    }
}



void ServerUtils::sendMessage(const QString& message)
{    
    // 生成隨機顏色
    QColor randomColor(
        QRandomGenerator::global()->bounded(256),  // 紅
        QRandomGenerator::global()->bounded(256),  // 綠
        QRandomGenerator::global()->bounded(256)   // 藍
    );
    
    QString color = randomColor.name();
    MessageData messageData("message", message, "Server", color);
    emit messageReceived(messageData);
    broadcastMessage(messageData.toByteArray());
}