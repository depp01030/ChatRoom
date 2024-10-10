#ifndef NETWORK_DATA_MANAGER_H
#define NETWORK_DATA_MANAGER_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QNetworkAccessManager>

class NetworkDataManager : public QObject
{
    Q_OBJECT

public:
    NetworkDataManager(QObject *parent = nullptr);
    void connectToServer();
    // bool login(const QString& username, const QString& password);
    void postMessageToServer(const QString& message);

    bool m_isLoggedIn;

signals:
    void updateChatBox(const QString& message);
    // void loginResult(bool success, const QString& message);

private slots:
    void onConnected();
    void onMessageReceivedFromLocal(const QString& message);
    void onMessageReceivedFromServer( );
    void onDisconnected();
    

private:
    QTcpSocket* m_socket;
    QNetworkAccessManager* m_networkManager;
};

#endif
