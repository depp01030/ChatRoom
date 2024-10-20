#include "message_processer.h"
MessageProcesser::MessageProcesser(NetworkDataManager *networkDataManager):
    m_networkDataManager(networkDataManager){
    }
void MessageProcesser::processSocketMessage(const QByteArray& data){
    QString jsonString(data);  
    QStringList jsonStrings = jsonString.split("\end");
    for (const QString& str : jsonStrings) {
        // 如果字串不是空的
        if (!str.trimmed().isEmpty()) {
            // 嘗試解析 JSON
            QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
            if (!doc.isNull()) {
                QJsonObject messageObject = doc.object(); 
                handleMessage(messageObject); 
                m_networkDataManager->broadcastMessage(messageObject);
            }
        }
    } 
}

QJsonObject MessageProcesser::messageWrapper(const QJsonObject& jsonObj) {
    try { 
        QJsonObject messageObject = { 
            {"type", jsonObj["type"].toInt()},
            {"content", jsonObj},
            {"userID", m_networkDataManager->m_user->getUserID()},
            {"userIP", m_networkDataManager->m_user->getUserIP()},
            {"timestamp", QDateTime::currentDateTime().toString()}
        }; 
        return messageObject;
    } catch (const std::exception& e) {
        qCritical() << "Error in messageWrapper: " << e.what();
        return QJsonObject(); // Return an empty QJsonObject in case of error
    }
}
QByteArray MessageProcesser::messageObjToByteArray(const QJsonObject& messageObject) {
    QByteArray message = QJsonDocument(messageObject).toJson();
    message.append("\end");
    return message;
}

void MessageProcesser::handleMessage(const QJsonObject& messageObject)
{ 
    MessageType messageType = static_cast<MessageType>(messageObject["type"].toInt()); 
    if (messageType == MessageType::ChatMessage){
        handleChatMessage(messageObject);
    }
    else if (messageType == MessageType::GameMessage){
        handleGameMessage(messageObject);
    }
    else if (messageType == MessageType::SystemMessage){
    } 
}
void MessageProcesser::handleChatMessage(const QJsonObject& messageObject){
    QString content = messageObject["content"]["message"].toString(); 
    QString userID = messageObject["userID"].toString();
    QString chatMessage = userID + " : " + content;
    qDebug() << "chatMessage: " << chatMessage;
    
    emit m_networkDataManager->updateChatBox(chatMessage);  
}
void MessageProcesser::handleGameMessage(const QJsonObject& messageObject){
    QJsonObject gameMessage = messageObject["content"].toObject(); 
    qDebug() << "game_message: " << gameMessage;
    OperationType operationType = static_cast<OperationType>(gameMessage["operation"].toInt());  
    if (operationType == OperationType::OpenCard){ 
        emit m_networkDataManager->openCard(gameMessage["id"].toInt());
    }
    else if (operationType == OperationType::SwitchTurn){ 
        // emit m_networkDataManager->switchTurn(gameMessage["team"].toInt());
    }
    else if (operationType == OperationType::UpdateScore){ 
    }

}
void MessageProcesser::handleSystemMessage(const QJsonObject& jsonObject){

}




