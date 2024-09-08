#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>   

class ServerUtils : public QObject
{
    Q_OBJECT

public:
    explicit ServerUtils(QObject *parent = nullptr);
    void sendMessage(const QString& message);
    void startServer();

signals:
    void messageReceived(const QString& message);

private slots:
    void onNewConnection();
    void slot_messageReceived();

private:
    QTcpServer* m_server;
    QVector<QTcpSocket*> m_client_sockets;
    void broadcastMessage(const QString& message);
};

#endif
