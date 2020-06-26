#ifndef USERDAOIMP_H
#define USERDAOIMP_H

#include "user.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QSqlError>

class UserDaoImp
{
public:
    UserDaoImp();
    ~UserDaoImp();

    bool create (User &t_user);
    User read(const QString &t_username);
    bool update(User &t_user);
    bool updateScore(const QString &t_username, int score);
    bool delete_(const QString& t_username);
    bool checkLogin(const QString& t_username, const QString& t_password);
    bool updateProfilePicture(QByteArray &arr, QString &username, int width, int height);
    bool checkUserExist(const QString &t_username);
};

#endif // USERDAOIMP_H
