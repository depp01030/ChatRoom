#include <iostream>
#include "../include/client_utils.h"
#include <Qstring>
ClientUtils::ClientUtils(QObject *parent) : QObject(parent) {
    m_socket = new QTcpSocket(this);
    connectToServer();
    connect(m_socket, &QTcpSocket::connected, this, &ClientUtils::slot_onConnected);
    connect(m_socket, &QTcpSocket::readyRead, this, &ClientUtils::slot_messageReceived);
    connect(m_socket, &QTcpSocket::disconnected, this, &ClientUtils::slot_onDisconnected);
    // Constructor implementation
}

void ClientUtils::connectToServer() {
    m_socket->connectToHost("127.0.0.1", 1234);  
}

void ClientUtils::sendMessage(const QString& message) {
    m_socket->write(message.toUtf8());    // Implementation for sending a message
    
}

void ClientUtils::slot_onConnected() {
    // Handle new connection
    std::cout << "Connected to server" << std::endl;
}

void ClientUtils::slot_messageReceived() {
    // Handle ready read
    QByteArray data = m_socket->readAll();
    QString message = QString::fromUtf8(data);
    QString completeMessage = "Client : " + message ;
    std::cout << "Message received: " << completeMessage.toStdString() << std::endl;
    emit messageReceived(completeMessage);
}

void ClientUtils::slot_onDisconnected() {
    // Handle disconnected
}
