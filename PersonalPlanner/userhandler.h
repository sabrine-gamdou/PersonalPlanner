#ifndef USERHANDLER_H
#define USERHANDLER_H

#include <user.h>
#include <QVariant>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlDatabase>
#include <QDebug>


class UserHandler
{
public:
    UserHandler();
    User* getUser(QString username);
    bool updateUser(User t_user);
    bool newUser(User t_user);
    bool deleteUser(User t_user);

private:
    User *user1;


};

#endif // USERHANDLER_H
