#include "user.h"

User::User(QString t_username, QString t_password) : m_username(t_username), m_password(t_password)
{

}

std::string User::toString(){
    return /*"Firstname: " + m_firstname + "\nLastname: " + m_lastname +
            "\nE-Mail: " + m_email + "\nBirthday: " + m_birthday +
            "\nAddress: " + m_address + "\nTaskList: " + m_taskList + */ "\nUsername: " + m_username.toUtf8().toStdString() //+
            /*"\nPassword: " + m_password.toStdString() + "\nScore: " + m_score*/;
}

QString User::username() const
{
    return m_username;
}

void User::setUsername(const QString &username)
{
    m_username = username;
}

QString User::password() const
{
    return m_password;
}

void User::setPassword(const QString &password)
{
    m_password = password;
}

