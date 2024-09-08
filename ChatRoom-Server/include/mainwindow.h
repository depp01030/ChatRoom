#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../include/server_utils.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void onButtonClicked();
    
private:
    Ui::MainWindow *ui;
    ServerUtils *m_server;
    void setupClickedEvent();
    void updateChatBox(const QString &message);
    
};

#endif // MAINWINDOW_H