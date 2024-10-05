#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "../include/client_utils.h"
#include <Qstring>
#include <QEventLoop>

ClientUtils::ClientUtils(QObject *parent) : QObject(parent), m_isLoggedIn(false) {
    m_socket = new QTcpSocket(this);
    m_networkManager = new QNetworkAccessManager(this);
    connect(m_socket, &QTcpSocket::connected, this, &ClientUtils::slot_onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientUtils::slot_messageReceived);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientUtils::slot_onDisconnected); 
    // Constructor implementation
}

bool ClientUtils::login(const QString& username, const QString& password) {
    QJsonObject loginData;
    loginData["username"] = username;
    loginData["password"] = password;
    QJsonDocument doc(loginData);

    QNetworkRequest request(QUrl("http://127.0.0.1:8080/login"));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QNetworkReply* reply = m_networkManager->post(request, doc.toJson());
    
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    QByteArray response = reply->readAll();
    std::cout << "Response: " << response.toStdString() << std::endl;
    QJsonObject responseObj = QJsonDocument::fromJson(response).object();
    m_isLoggedIn = responseObj["success"].toBool();
    std::cout << "Login result: " << m_isLoggedIn << std::endl;
    return m_isLoggedIn;
}

void ClientUtils::connectToServer() {
    m_socket->connectToHost("127.0.0.1", 1234);  
}

void ClientUtils::sendMessage(const QString& message) {
 
    QJsonObject messageData;
    messageData["type"] = "message";
    messageData["content"] = message;
    QJsonDocument doc(messageData);

    m_socket->write(doc.toJson());
}



void ClientUtils::slot_onConnected() {
    // Handle new connection
    std::cout << "Connected to server" << std::endl;
}

void ClientUtils::slot_messageReceived() {
    // Handle ready read
    QByteArray data = m_socket->readAll();
    QJsonDocument doc = QJsonDocument::fromJson(data);
    if (doc.isNull()){
        return;
    }
    QJsonObject jsonObj = doc.object();
    if (jsonObj["type"] == "message"){
        QString message = jsonObj["content"].toString();
        emit messageReceived(message);
    }
}

void ClientUtils::slot_onDisconnected() {
    // Handle disconnected
}