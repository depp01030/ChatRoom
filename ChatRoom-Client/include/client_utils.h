#ifndef CLIENT_UTILS_H  // Changed from SERVER_UTILS_H
#define CLIENT_UTILS_H

#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>   

class ClientUtils : public QObject  // Changed from ServerUtils to ClientUtils
{
    Q_OBJECT

public:
    ClientUtils(QObject *parent = nullptr);  // Changed from ServerUtils to ClientUtils
    QTcpSocket* m_socket; 
    void connectToServer();
    void sendMessage(const QString& message);
signals:
    void messageReceived(const QString& message);
 private slots:
    void slot_onConnected();
    void slot_messageReceived();
    void slot_onDisconnected();
     
};

#endif
