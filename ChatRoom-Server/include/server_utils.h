#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H
#include <iostream>
#include <Map>
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QTimer> // Added for QTimer
#include <QtHttpServer/QtHttpServer> // Added for QHttpServer

class ServerUtils : public QObject
{
    Q_OBJECT

public:
    explicit ServerUtils(QObject *parent = nullptr);
    void sendMessage(const QString& message);
    void startServer();
    void startHttpServer();
    
signals:
    void messageReceived(const QString& message);
    
private slots:
    void slot_onNewConnection();
    void slot_messageReceived();
    void slot_handleDisconnection();

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
    void broadcastMessage(const QString& message);
    // void handleLogin(QTcpSocket* socket, const QJsonObject& loginData);
    bool isLoginSuccess(const QString& username, const QString& password);
    bool isIPAuthenticated(const QString& ipAddress) const;
    bool isUserAuthenticated(QTcpSocket* socket) const;
    void removeUnauthenticatedSocket(QTcpSocket* socket);
 
};

#endif
