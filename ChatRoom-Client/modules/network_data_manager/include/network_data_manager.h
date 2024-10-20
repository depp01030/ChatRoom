#ifndef NETWORK_DATA_MANAGER_H
#define NETWORK_DATA_MANAGER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
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
    QNetworkAccessManager* m_networkManager; 
    MessageProcesser* m_messageProcesser;
    void connectToServer(); 
public:
    User* m_user;
    NetworkDataManager(QObject *parent = nullptr);
    ~NetworkDataManager();
    // bool login(const QString& username, const QString& password);
    // void sendMessageToServer(const QString& message);
    void sendMessageToServer(const QByteArray& message); 
    void broadcastMessage(const QJsonObject& messageObject);
    bool m_isLoggedIn; 
signals:
    void updateChatBox(const QString& message);
    // void loginResult(bool success, const QString& message);
    void openCard(int id); 
public slots : 
    void onConnected();
    void onDisconnected();
    void onSendingMessageToServer(const QJsonObject& data);
    void onReceivingMessageFromServer( );
 
};

#endif
    