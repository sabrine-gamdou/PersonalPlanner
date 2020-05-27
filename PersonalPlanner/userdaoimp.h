#ifndef USERDAOIMP_H
#define USERDAOIMP_H
#include "user.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class UserDaoImp
{
public:
    UserDaoImp();
    ~UserDaoImp();
    bool create (User &t_user);
    User *read(QString t_username);
    bool update(User &t_user);
    bool delete_(User &t_user);
    bool checkLogin(QString t_username, QString t_password);
    User *user() const;
    void setUser(User *user);

private:
    User* m_user;
};

#endif // USERDAOIMP_H
