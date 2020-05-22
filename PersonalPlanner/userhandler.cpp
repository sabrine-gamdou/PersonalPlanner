#include "userhandler.h"

User *user1;

UserHandler::UserHandler()
{

}

User *UserHandler::getUser(QString username ){
    QSqlQuery query;
    qDebug() << query.prepare(" SELECT * FROM users WHERE username=" ":username");
    query.bindValue(":username", username);
    qDebug() << query.exec();

    qDebug() << query.next();

    while(query.next()){
        username = query.value(0).toString();
        qDebug() << username;
    }

    user1 = new User(username, " ");

    user1->setUsername(username);


    return user1;
}

bool UserHandler::updateUser(User t_user){
    QSqlQuery query;
    query.prepare("UPDATE users SET  WHERE username=" "VALUES (:username)");
    query.bindValue(":username", t_user.username());

    return query.exec();
}

bool UserHandler::newUser(User t_user){
    QSqlQuery query;
    qDebug() << query.prepare("INSERT INTO users(username, password) VALUES (:username, :password)");
    query.bindValue(":username", t_user.username());
    query.bindValue(":password", t_user.password());

    return query.exec();
}

bool UserHandler::deleteUser(User t_user){
    QSqlQuery query;
    query.prepare("DELETE FROM users WHERE username=" "VALUES (:username)");
    query.bindValue(":username", t_user.username());

    return query.exec();
}
