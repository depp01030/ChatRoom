#ifndef MESSAGE_H
#define MESSAGE_H

#include <QString>
#include <QJsonObject> 
#include <QJsonDocument> 

enum class MessageType{
    Message,
    GameMessage,
    SystemMessage,
    ChatMessage,
    // LoginMessage,
    // LogoutMessage,
    // RegisterMessage,
    // ForgetPasswordMessage,
    // ChangePasswordMessage,
    // ChangeUsernameMessage,
};
class Message{
public:
    
    MessageType type = MessageType::Message;
    QJsonObject content ;
    QString userIP ; 

    Message( 
        const QJsonObject& content  ) :  content(content)  {}
    Message(QByteArray data){ 
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isNull()){ 
            return ;
        }
        QJsonObject jsonObject = doc.object();
        if (jsonObject.contains("type")){
            type = static_cast<MessageType>(jsonObject["type"].toInt());
        }
        if (jsonObject.contains("content")){
            content = jsonObject["content"].toObject();
        }
        if (jsonObject.contains("userIP")){
            userIP = jsonObject["userIP"].toString();
        } 
        

    }
  
    QJsonObject toJson() const {
        QJsonObject jsonObj;
        jsonObj["type"] = static_cast<int>(type);
        jsonObj["content"] = content;
        jsonObj["userIP"] = userIP; 
        return jsonObj;
    }
    QByteArray toByteArray() const {
        QJsonObject jsonObject = this->toJson();
        QByteArray byteArrayMessage = QJsonDocument(jsonObject).toJson();
        return byteArrayMessage;
    }
    QString toText() const {
        QString text = userIP + " : ";
        text += QJsonDocument(content).toJson(QJsonDocument::Compact);
        return text;
    }   
};
#endif // MESSAGE_H
