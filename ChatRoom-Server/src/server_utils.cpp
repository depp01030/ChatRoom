#include <iostream>
#include "../include/server_utils.h"
#include <Qstring>
ServerUtils::ServerUtils(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    m_server = new QTcpServer(this);
    this->startServer();

}

void ServerUtils::sendMessage(const QString& message)
{
    std::cout << message.toStdString() << std::endl;
    emit messageSent(message);
}

void ServerUtils::startServer(){
    if(m_server->isListening()){
        return;
    }
    m_server->listen(QHostAddress::Any, 1234);
    connect(m_server, &QTcpServer::newConnection, this, &ServerUtils::onNewConnection);
}

void ServerUtils::onNewConnection(){
    m_socket = m_server->nextPendingConnection();
    connect(m_socket, &QTcpSocket::readyRead, this, &ServerUtils::onReadyRead);
    sendMessage("New connection");
}

void ServerUtils::onReadyRead(){
    QByteArray data = m_socket->readAll();
    sendMessage(data);
}
