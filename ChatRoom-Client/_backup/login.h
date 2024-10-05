#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = nullptr);
    ~Login();

    QString getUsername() const;
    QString getPassword() const;

private:
    Ui::Login *ui;
};

#endif // LOGIN_H