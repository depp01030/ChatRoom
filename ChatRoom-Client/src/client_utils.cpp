#include <iostream>
#include "../include/client_utils.h"
#include <Qstring>
ClientUtils::ClientUtils(QObject *parent) : QObject(parent) {
}

void ClientUtils::sendMessage(const QString& message)
{
    std::cout << message.toStdString() << std::endl;
    emit messageSent(message);
}

