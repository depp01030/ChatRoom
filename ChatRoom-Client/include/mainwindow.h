#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "client_utils.h"  // Updated include

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool get_login_status() const;

private slots: 
    void onMessageReceived(const QString& message);

private:
    Ui::MainWindow *ui;
    ClientUtils *m_client;
    void setupClickedEvent();
    void onButtonClicked();
    void updateChatBox(const QString &message);
};

#endif // MAINWINDOW_H