#include <iostream>
#include "../include/server_utils.h"
#include <Qstring>
ServerUtils::ServerUtils(QObject *parent) : QObject(parent) {
    m_server = new QTcpServer(this);
    this->startServer();
    
}

void ServerUtils::sendMessage(const QString& message)
{
    emit messageReceived(message);
    broadcastMessage(message);
}

void ServerUtils::startServer(){
    if(m_server->isListening()){
        return;
    }
    m_server->listen(QHostAddress::Any, 1234);
    connect(m_server, &QTcpServer::newConnection, this, &ServerUtils::onNewConnection);
}

void ServerUtils::onNewConnection(){
    QTcpSocket* client_socket = m_server->nextPendingConnection();
    m_client_sockets.push_back(client_socket);
    connect(client_socket, &QTcpSocket::readyRead, this, &ServerUtils::slot_messageReceived);
    sendMessage("New connection");
}

void ServerUtils::slot_messageReceived()
{
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (!socket) {
        return;

    }
    QByteArray data = socket->readAll();
    QString message = QString::fromUtf8(data);
    emit messageReceived(message);
    
    // Broadcast the message to all clients 
    broadcastMessage(message);
}
void ServerUtils::broadcastMessage(const QString& message)
{
    for(QTcpSocket* client_socket : m_client_sockets){
        client_socket->write(message.toUtf8()); 
    }
}

