#include "userdaoimp.h"
#include "databasesingleton.h"

UserDaoImp::UserDaoImp(){

}


UserDaoImp::~UserDaoImp(){

}


bool UserDaoImp::create (User &user){
    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("INSERT INTO users (username, pass, firstname, lastname, email, birthday, address, score) "
                                                  "VALUES (:username, :pass, :firstname, :lastname, :email, :birthday, :address, :score)");
    query.bindValue(":username", user.username());
    query.bindValue(":pass", user.password());
    query.bindValue(":firstname", user.firstname());
    query.bindValue(":lastname", user.lastname());
    query.bindValue(":email", user.email());
    query.bindValue(":birthday", user.birthday());
    query.bindValue(":address", user.address());
    query.bindValue(":score", user.score());

    if( !query.exec()){
        qDebug() << query.lastError().text();
        return false;
    }
    return true;
}


User UserDaoImp::read(const QString &username){
    QString password;
    QString firstname;
    QString lastname;
    QString email;
    QDate birthday(1,2,3);
    QString address;
    QByteArray profilePicture;

    int score = 0;
    int width;
    int height;

    DatabaseSingleton::getInstance();
    QSqlQuery query;

    query.prepare( " SELECT * FROM users WHERE username=" ":username");
    query.bindValue(":username", username);

    query.exec();

    while (query.next()) {
        password = query.value(1).toString();
        firstname = query.value(2).toString();
        lastname = query.value(3).toString();
        email = query.value(4).toString();
        birthday = query.value(5).toDate();
        address = query.value(6).toString();
        score = query.value(7).toInt();
        profilePicture = query.value(8).toByteArray();
        width = query.value(9).toInt();
        height = query.value(10).toInt();

        qDebug() << username << password << firstname << lastname << email
                 << birthday << address << score;
    }

    User user(username, password, firstname, lastname, email);
    user.setBirthday(birthday);
    user.setAddress(address);
    user.setScore(score);
    user.setProfilePicture(profilePicture);
    user.setWidth(width);
    user.setHeight(height);

    return user;
}


bool UserDaoImp::update(User &user){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("UPDATE users SET pass = (:pass), firstname = (:firstname), "
                                                  "lastname = (:lastname), email = (:email), birthday = (:birthday),"
                                                  "address = (:address), score = (:score) WHERE username = (:un)");
    query.bindValue(":un", user.username());
    query.bindValue(":pass", user.password());
    query.bindValue(":firstname", user.firstname());
    query.bindValue(":lastname", user.lastname());
    query.bindValue(":email", user.email());
    query.bindValue(":birthday", user.birthday());
    query.bindValue(":address", user.address());
    query.bindValue(":score", user.score());

    return query.exec();
}


bool UserDaoImp::updateScore(const QString &username, int score){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("UPDATE users SET  score = (:score) WHERE username = (:un)");
    query.bindValue(":un", username);
    query.bindValue(":score", score);

    return query.exec();
}


bool UserDaoImp::delete_(const QString &username){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("DELETE FROM users WHERE username = (:un)");
    query.bindValue(":un", username);

    return query.exec();
}


bool UserDaoImp::checkLogin(const QString &username, const QString &password){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("SELECT username FROM users WHERE username = (:un) AND pass = (:pass)");
    query.bindValue(":un", username);
    query.bindValue(":pass", password);

    if( query.exec()){
        if (query.next())
            return true;
    }
    return false;
}


bool UserDaoImp::updateProfilePicture(QByteArray &arr, QString &username, int width, int height){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare updateProfilePicture Query: "<< query.prepare("UPDATE users SET profile_picture = (:pic), width = (:width), height = (:height) WHERE username = (:un)");
    query.bindValue(":un", username);
    query.bindValue(":pic", arr);
    query.bindValue(":width",width);
    query.bindValue(":height",height);

    return query.exec();
}


bool UserDaoImp::checkUserExist(const QString &username){
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("SELECT username FROM users WHERE username = (:un)");
    query.bindValue(":un", username);

    if( query.exec()){
        if (query.next())
            return true;
    }
    return false;
}
