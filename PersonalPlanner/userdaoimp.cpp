#include "userdaoimp.h"
#include "databasesingleton.h"

UserDaoImp::UserDaoImp(){

}


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

User UserDaoImp::read(const QString& t_username){
    QString t_firstname;
    QString t_lastname;
    QString t_email;
    QDate t_birthday(1,2,3);
    QString t_address;
    QString t_password;
    QByteArray t_profilePicture;
    int t_score = 0;
    int width;
    int height;

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM users WHERE username=" ":t_username");
    query.bindValue(":t_username", t_username);

    query.exec();

    while (query.next()) {
        //t_username = query.value(0).toString();
        t_password = query.value(1).toString();
        t_firstname = query.value(2).toString();
        t_lastname = query.value(3).toString();
        t_email = query.value(4).toString();
        t_birthday = query.value(5).toDate();
        t_address = query.value(6).toString();
        t_score = query.value(7).toInt();
        t_profilePicture = query.value(8).toByteArray();
        width = query.value(9).toInt();
        height = query.value(10).toInt();

        qDebug() << t_username << t_password << t_firstname << t_lastname << t_email
                 << t_birthday << t_address << t_score;
    }

    User user(t_username, t_password, t_firstname, t_lastname, t_email);
    user.setBirthday(t_birthday);
    user.setAddress(t_address);
    user.setScore(t_score);
    user.setProfilePicture(t_profilePicture);
    user.setWidth(width);
    user.setHeight(height);

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

bool UserDaoImp::updateScore(const QString &t_username, int score){
    DatabaseSingleton::getInstance();

    QSqlQuery query;


    qDebug() << "Prepare Query: "<< query.prepare("UPDATE users SET  score = (:score) WHERE username = (:un)");

    query.bindValue(":un", t_username);
    query.bindValue(":score", score);

    return query.exec();
}



bool UserDaoImp::delete_(const QString &t_username){
    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("DELETE FROM users WHERE username = (:un)");
    query.bindValue(":un", t_username);

    return query.exec();
}


bool UserDaoImp::checkLogin(const QString &t_username, const QString &t_password){
    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("SELECT username FROM users WHERE username = (:un) AND pass = (:pass)");
    query.bindValue(":un", t_username);
    query.bindValue(":pass", t_password);

    if( query.exec()){
        if (query.next()){
            return true;
        }
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

bool UserDaoImp::checkUserExist(const QString &t_username){
    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("SELECT username FROM users WHERE username = (:un)");
    query.bindValue(":un", t_username);

    if( query.exec()){
        if (query.next()){
            return true;
        }
    }
    return false;
}

