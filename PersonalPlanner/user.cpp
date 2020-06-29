#include "user.h"

User::User(QString t_username, QString t_password, QString t_firstname, QString t_lastname, QString t_email) : m_username(t_username), m_password(t_password), m_firstname(t_firstname), m_lastname(t_lastname), m_email(t_email){

}

User::~User(){

}

QString User::firstname() const{
    return m_firstname;
}

void User::setFirstname(const QString &firstname){
    m_firstname = firstname;
}

QString User::lastname() const{
    return m_lastname;
}

void User::setLastname(const QString &lastname){
    m_lastname = lastname;
}

QString User::email() const{
    return m_email;
}

void User::setEmail(const QString &email){
    m_email = email;
}

QDate User::birthday() const{
    return m_birthday;
}

void User::setBirthday(const QDate &birthday){

    m_birthday = birthday;
}

QString User::address() const{
    return m_address;
}

void User::setAddress(const QString &address){
    m_address = address;
}

QString User::username() const{
    return m_username;
}

QString User::password() const{
    return m_password;
}

int User::score() const{
    return m_score;
}

void User::setScore(int score){
    m_score = score;
}

int User::getWidth() const{
    return width;
}

void User::setWidth(int value){
    width = value;
}

int User::getHeight() const{
    return height;
}

void User::setHeight(int value){
    height = value;
}

QByteArray User::getProfilePicture() const{
    return m_profilePicture;
}

void User::setProfilePicture(const QByteArray &profilePicture){
    m_profilePicture = profilePicture;
}

QString User::toString(){
    QString string ;
    string.append("Username: " );
    string.append(m_username);
    string.append("\nPassword: ");
    string.append(m_password);
    string.append("\nFirstname: ");
    string.append(m_firstname);
    string.append("\nLastname: ");
    string.append(m_lastname);
    string.append("\nEmail: ");
    string.append(m_email);
    string.append("\nBirthday: ");
    string.append(m_birthday.toString("dd.MM.yyyy"));
    string.append("\nAddress: ");
    string.append(m_address);
    string.append("\nScore: ");
    string.append(QString::number(m_score));

    return string;
}
