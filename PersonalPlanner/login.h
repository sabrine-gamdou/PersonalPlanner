#ifndef LOGIN_H
#define LOGIN_H

#include <QWidget>
#include "userdaoimp.h"
#include "taskdaoimp.h"

namespace Ui {
class Login;
}

class Login : public QWidget
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    void on_login_clicked();
    bool login(QString u, QString p);
    ~Login();

private:
    Ui::Login *ui;
    bool loggedIn;
    UserDaoImp* m_userManager;
    TaskDaoImp* m_taskManager;


};

#endif // LOGIN_H
