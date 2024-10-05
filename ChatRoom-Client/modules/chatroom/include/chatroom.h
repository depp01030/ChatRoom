#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include "chattextedit.h"
#include "server_utils/include/server_utils.h"

namespace Ui {
    class ChatRoom;
}

class ChatMessage : public QString {
private:
    QString m_color = "grey";
public:
    ChatMessage(const MessageData& data)
        : QString(QString("<font color='%1'><b>%2</b>: %3</font>")
                  .arg(data.color)
                  .arg(data.user)
                  .arg(data.content)) {}

    ChatMessage(const QString& message)
        : QString(QString("<font color='%1'><b>%2</b>: %3</font>")
                  .arg(m_color)
                  .arg("Server")
                  .arg(message)) {}
};

class ChatRoom : public QWidget
{
    Q_OBJECT

public:
    explicit ChatRoom(QWidget *parent = nullptr, ServerUtils *server = nullptr);
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
 
private slots:
    void onSendButtonClicked();
    void updateChatBox(const QString &message);
    void updateChatBox(const MessageData &messageData);
private:
    Ui::ChatRoom *ui;
    ServerUtils *m_server;
    void setupConnection();
    void connectChatTextEdit();

};

#endif // CHATROOM_H
