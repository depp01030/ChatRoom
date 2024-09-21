#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../include/server_utils.h"
#include "../include/chattextedit.h"


 
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();
    void updateChatBox(const QString &message);
    void updateChatBox(const MessageData &messageData);

private:
    Ui::MainWindow *ui;
    ServerUtils *m_server;
    void setupClickedEvent();
    void loadTheme();
    void connectChatTextEdit();
};

#endif // MAINWINDOW_H