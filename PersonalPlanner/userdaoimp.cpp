#include "userdaoimp.h"
#include "databasesingleton.h"

UserDaoImp::UserDaoImp(){}


UserDaoImp::~UserDaoImp(){
   // delete m_user;
}



bool UserDaoImp::create (User &t_user){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("INSERT INTO users (username, pass, firstname, lastname, email, birthday, address, score) "
                                                  "VALUES (:username, :pass, :firstname, :lastname, :email, :birthday, :address, :score)");
    query.bindValue(":username", t_user.username());
    query.bindValue(":pass", t_user.password());
    query.bindValue(":firstname", t_user.firstname());
    query.bindValue(":lastname", t_user.lastname());
    query.bindValue(":email", t_user.email());
    query.bindValue(":birthday", t_user.birthday());
    query.bindValue(":address", t_user.address());
    query.bindValue(":score", t_user.score());

    if( !query.exec())
    {
        qDebug() << query.lastError().text();
        return false;
    }


    return true;

}

User UserDaoImp::read(QString t_username){

    QString t_firstname;
    QString t_lastname;
    QString t_email;
    QDate t_birthday(1,2,3);
    QString t_address;
    QString t_password;
    int t_score = 0;

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM users WHERE username=" ":t_username");
    query.bindValue(":t_username", t_username);

    query.exec();

    while (query.next()) {
        t_username = query.value(0).toString();
        t_password = query.value(1).toString();
        t_firstname = query.value(2).toString();
        t_lastname = query.value(3).toString();
        t_email = query.value(4).toString();
        t_birthday = query.value(5).toDate();
        t_address = query.value(6).toString();
        t_score = query.value(7).toInt();

        qDebug() << t_username << t_password << t_firstname << t_lastname << t_email
                 << t_birthday << t_address << t_score;
    }

    User user(t_username, t_password, t_firstname, t_lastname, t_email);
    user.setBirthday(t_birthday);
    user.setAddress(t_address);
    user.setScore(t_score);

    return user;
}


bool UserDaoImp::update(User &t_user){

    DatabaseSingleton::getInstance();

    QSqlQuery query;


    qDebug() << "Prepare Query: "<< query.prepare("UPDATE users SET pass = (:pass), firstname = (:firstname), "
                                                  "lastname = (:lastname), email = (:email), birthday = (:birthday),"
                                                  "address = (:address), score = (:score) WHERE username = (:un)");
    query.bindValue(":un", t_user.username());
    query.bindValue(":pass", t_user.password());
    query.bindValue(":firstname", t_user.firstname());
    query.bindValue(":lastname", t_user.lastname());
    query.bindValue(":email", t_user.email());
    query.bindValue(":birthday", t_user.birthday());
    query.bindValue(":address", t_user.address());
    query.bindValue(":score", t_user.score());

    return query.exec();
}


bool UserDaoImp::delete_(const QString t_username){


    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("DELETE FROM users WHERE username = (:un)");
    query.bindValue(":un", t_username);

    return query.exec();
}


bool UserDaoImp::checkLogin(const QString t_username, const QString t_password){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    bool exists = false;

    qDebug() << "Prepare Query: "<< query.prepare("SELECT username FROM users WHERE username = (:un) AND pass = (:pass)");
    query.bindValue(":un", t_username);
    query.bindValue(":pass", t_password);

    if( query.exec()){
        if (query.next()){
            exists = true;
        }

    }else{
        qDebug() << query.lastError().text();
    }

    qDebug() << exists;
    return exists;
}

User *UserDaoImp::user() const
{
    return m_user;
}

void UserDaoImp::setUser(User *user)
{
    m_user = user;
}

