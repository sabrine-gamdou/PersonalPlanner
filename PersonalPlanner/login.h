#ifndef LOGIN_H
#define LOGIN_H

#include "userdaoimp.h"
#include "taskdaoimp.h"
#include "mainwindow.h"
#include "registrationform.h"

#include <QMessageBox>
#include <QFile>
#include <QDesktopWidget>
#include <QWidget>

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

    bool login(QString &un, QString &pass);

private slots:
    void on_loginBtn_clicked();
    void on_registerBtn_clicked();

private:
    QString m_username;
    QString m_password;

    Ui::Login *ui;
    MainWindow w;
    RegistrationForm r;

    bool loggedIn;

    UserDaoImp* m_userManager;
    TaskDaoImp* m_taskManager;

    void initialize(QString &un, QString &pass);
};

#endif // LOGIN_H
