#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H
#include <iostream>
#include <Map>
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer> 
#include <QtHttpServer/QtHttpServer> // Added for QHttpServer
#include "message_data.h"

class ServerUtils : public QObject
{
    Q_OBJECT

public:
    explicit ServerUtils(QObject *parent = nullptr);
    void sendMessage(const QString& message);
    void startServer();
    void startHttpServer();
    QByteArray packMessage(const QString& type, const QString& message);

signals:
    void messageReceived(const QString& message);
    void messageReceived(const MessageData& messageData);
    
private slots:
    void onNewConnection();
    void onMessageReceived();
    void onDisconnection();

private:
    std::map<QString, QString> m_users = {
        {"a", "a"},
        {"admin", "admin"},
        {"depp", "pass_depp"},
        {"user2", "password2"},
        {"user3", "password3"},
    };
    
    QHttpServer* m_httpServer;
    QTcpServer* m_server;
    std::map<QString, QString> m_authenticatedIP; // IP address, username
    std::map<QTcpSocket*, QString> m_authenticatedUsers; // socket, IP
    std::map<QTcpSocket*, QString> m_unauthenticatedUsers; // socket, IP

    QHttpServerResponse handleHttpRequest(const QHttpServerRequest &request);
    void broadcastMessage(const QByteArray& message);
    // void handleLogin(QTcpSocket* socket, const QJsonObject& loginData);
    bool isLoginSuccess(const QString& username, const QString& password);
    bool isIPAuthenticated(const QString& ipAddress) const;
    bool isUserAuthenticated(QTcpSocket* socket) const;
    void removeUnauthenticatedSocket(QTcpSocket* socket);
 
};

#endif
