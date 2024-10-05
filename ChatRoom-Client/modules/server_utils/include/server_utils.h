#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H
#include <iostream>
#include <Map>
#include <QObject>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QTcpServer>
#include <QTimer> // Added for QTimer
#include <QtHttpServer/QtHttpServer> // Added for QHttpServer
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
class ServerUtils : public QObject
{
    Q_OBJECT

public:
    explicit ServerUtils(QObject *parent = nullptr);
    void sendMessage(const QString& message);
    void startServer();
    void startHttpServer();
    QByteArray packMessage(const QString& type, const QString& message);

signals:
    void messageReceived(const QString& message);
    void messageReceived(const MessageData& messageData);
    
private slots:
    void slot_onNewConnection();
    void slot_messageReceived();
    void slot_handleDisconnection();

private:
    std::map<QString, QString> m_users = {
        {"a", "a"},
        {"admin", "admin"},
        {"depp", "pass_depp"},
        {"user2", "password2"},
        {"user3", "password3"},
    };
    
    QHttpServer* m_httpServer;
    QTcpServer* m_server;
    std::map<QString, QString> m_authenticatedIP; // IP address, username
    std::map<QTcpSocket*, QString> m_authenticatedUsers; // socket, IP
    std::map<QTcpSocket*, QString> m_unauthenticatedUsers; // socket, IP

    QHttpServerResponse handleHttpRequest(const QHttpServerRequest &request);
    void broadcastMessage(const QByteArray& message);
    // void handleLogin(QTcpSocket* socket, const QJsonObject& loginData);
    bool isLoginSuccess(const QString& username, const QString& password);
    bool isIPAuthenticated(const QString& ipAddress) const;
    bool isUserAuthenticated(QTcpSocket* socket) const;
    void removeUnauthenticatedSocket(QTcpSocket* socket);
 
};

#endif
