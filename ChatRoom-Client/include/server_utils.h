#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>   

class ServerUtils : public QObject
{
    Q_OBJECT

public:
    QTcpSocket* m_socket;
    QTcpServer* m_server;
    ServerUtils(QObject *parent = nullptr);
    void startServer();
    void sendMessage(const QString& message);
    
 public slots:
    void onNewConnection();
    void onReadyRead();
signals:
    void messageSent(const QString& message);

};

#endif
