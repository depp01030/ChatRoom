#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include <QObject>

class ClientUtils : public QObject
{
    Q_OBJECT

public:
    ClientUtils(QObject *parent = nullptr);
    void sendMessage(const QString& message);
 
signals:
    void messageSent(const QString& message);

};

#endif
