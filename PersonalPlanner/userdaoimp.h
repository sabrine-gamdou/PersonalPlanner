#ifndef USERDAOIMP_H
#define USERDAOIMP_H

#include "user.h"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>

class UserDaoImp
{
public:
    UserDaoImp();
    ~UserDaoImp();

    bool create (User &user);
    User read(const QString &username);
    bool update(User &user);
    bool updateScore(const QString &username, int score);
    bool delete_(const QString &username);
    bool checkLogin(const QString &username, const QString &password);
    bool updateProfilePicture(QByteArray &arr, QString &username, int width, int height);
    bool checkUserExist(const QString &username);
};

#endif // USERDAOIMP_H
