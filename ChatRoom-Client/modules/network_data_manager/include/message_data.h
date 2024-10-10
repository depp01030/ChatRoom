#ifndef MESSAGE_DATA_H
#define MESSAGE_DATA_H

#include <QString>
#include <QJsonObject> 
#include <QJsonDocument>
class MessageData{
public:
    bool status = true;
    QString type = "";
    QString content = "";
    QString user = "";
    QString color = "";

    MessageData(
        QString type,
        QString content,
        QString user,
        QString color
    ) : type(type),
      content(content),
      user(user),
      color(color) {}
    MessageData(QByteArray data){ 
        QJsonDocument doc = QJsonDocument::fromJson(data);
        if (doc.isNull()){
            status = false;
            return ;
        }
        QJsonObject jsonObject = doc.object();
        if (jsonObject.contains("type")){
            type = jsonObject["type"].toString();
        }
        if (jsonObject.contains("content")){
            content = jsonObject["content"].toString();
        }
        if (jsonObject.contains("user")){
            user = jsonObject["user"].toString();
        }
        if (jsonObject.contains("color")){
            color = jsonObject["color"].toString();
        }
        

    }
  
    QJsonObject toJson() const {
        QJsonObject jsonObj;
        jsonObj["type"] = type;
        jsonObj["content"] = content;
        jsonObj["user"] = user;
        jsonObj["color"] = color;
        return jsonObj;
    }
    QByteArray toByteArray() const {
        QJsonObject jsonObject = this->toJson();
        QByteArray packedMessage = QJsonDocument(jsonObject).toJson();
        return packedMessage;
    }
    QString toText() const {
        QString text = "";
        text += user + " : " + content  ;
        return text;
    }   
};
#endif // MESSAGE_DATA_H
