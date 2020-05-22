#ifndef USER_H
#define USER_H

#include <string>
#include <QDate>



class User
{
public:
    User(QString t_username, QString t_password);
    std::string toString();

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

private:
    std::string m_firstname;
    std::string m_lastname;
    std::string m_email;
    std::string m_birthday;
    std::string m_address;
    std::string m_taskList;
    QString m_username;
    QString m_password;
    std::string m_score;
};

#endif // USER_H
