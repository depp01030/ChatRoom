#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <QNetworkAccessManager>

class ClientUtils : public QObject
{
    Q_OBJECT

public:
    ClientUtils(QObject *parent = nullptr);
    void connectToServer();
    bool login(const QString& username, const QString& password);
    void postMessageToServer(const QString& message);

    bool m_isLoggedIn;

signals:
    void messageReceived(const QString& message);
    void loginResult(bool success, const QString& message);

private slots:
    void onConnected();
    void onMessageReceivedFromLocal(const QString& message);
    void onMessageReceived();
    void onDisconnected();
    

private:
    QTcpSocket* m_socket;
    QNetworkAccessManager* m_networkManager;
};

#endif
