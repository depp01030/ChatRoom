#ifndef NETWORK_DATA_MANAGER_H
#define NETWORK_DATA_MANAGER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer> 
#include <QtHttpServer/QtHttpServer> // Added for QHttpServer
#include <QNetworkAccessManager>

#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
// #include "game_controller/include/game_controller.h"
#include "message_processer.h"
#include "message.h"
#include "user.h"
class MessageProcesser;
class NetworkDataManager : public QObject
{
    Q_OBJECT
private:
    QTcpSocket* m_socket; 
    QHttpServer* m_httpServer;
    QTcpServer* m_server;
    QNetworkAccessManager* m_networkManager; 
    MessageProcesser* m_messageProcesser;
    void startServer();
    void startHttpServer(); 
public:
    User* m_user;
    NetworkDataManager(QObject *parent = nullptr);
    ~NetworkDataManager();
    // bool login(const QString& username, const QString& password);
 
    void sendMessageToServer(const QByteArray& message); 
    void broadcastMessage(const QJsonObject& messageObject);
    bool m_isLoggedIn; 
signals:
    void updateChatBox(const QString& message);
    // void loginResult(bool success, const QString& message); 
    void openCard(int id);
public slots : 
    void onDisconnected();
    void onSendingMessageToServer(const QJsonObject& jsonObj); 
    void onReceivingMessageFromServer( );
    void onReceivingMessageFromLocal(); 
// ====================================================== //
private:   
    std::map<QTcpSocket*, QString> m_authenticatedUsers; // socket, IP
 
public slots : 
    void onNewConnection(); 
    
};

#endif
