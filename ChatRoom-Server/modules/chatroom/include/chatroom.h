#ifndef CHATROOM_H
#define CHATROOM_H

#include <QWidget>
#include <QColor>
#include "chattextedit.h"
#include "network_data_manager/include/network_data_manager.h"
#include "network_data_manager/include/message.h"
// #include "network_data_manager/include/user.h"
namespace Ui {
    class ChatRoom;
}

class ChatMessage {
private:
    QColor m_color = QColor(Qt::green);
    QString m_formattedMessage;
public: 
    ChatMessage(const QString& message)
        :  m_formattedMessage(QString("<font color='%1'> : %2</font>")
                             .arg(m_color.name()) 
                             .arg(message)) {}

    QString getFormattedMessage() const {
        return m_formattedMessage;
    }
};

class ChatRoom : public QWidget
{
    Q_OBJECT
private:
    NetworkDataManager *m_networkDataManager;
public:
    explicit ChatRoom(QWidget *parent = nullptr,
     NetworkDataManager *networkDataManager = nullptr);
    explicit ChatRoom(QWidget *parent = nullptr);
    ~ChatRoom();
 
private slots:
    void onSendButtonClicked();
    void onUpdateChatBox(const QString &message);
signals:
    void sendChatMessageToServer(const QJsonObject &message);
private:
    Ui::ChatRoom *ui;
    NetworkDataManager *m_server;
    void setupConnection();
    // void connectChatTextEdit();

};

#endif // CHATROOM_H
