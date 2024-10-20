#ifndef MESSAGE_PROCESSER_H
#define MESSAGE_PROCESSER_H
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include "network_data_manager.h"
#include "message.h"
#include "user.h"
#include "operation_type.h"
class NetworkDataManager;
class MessageProcesser{
private:
    NetworkDataManager* m_networkDataManager;
public:
    MessageProcesser(NetworkDataManager *networkDataManager);
    void processSocketMessage(const QByteArray& data);
    QJsonObject messageWrapper(const QJsonObject& jsonObj);
    QByteArray messageObjToByteArray(const QJsonObject& messageObject);
    void handleMessage(const QJsonObject& jsonObject);
    void handleChatMessage(const QJsonObject& jsonObject);
    void handleGameMessage(const QJsonObject& jsonObject);
    void handleSystemMessage(const QJsonObject& jsonObject);
};
#endif // MESSAGE_PROCESSER_H
 