#ifndef USER_H
#define USER_H

#include <QString>
#include <QDate>

class User
{
public:
    User(QString t_username, QString t_password, QString t_firstname, QString t_lastname, QString t_email);
    ~User();

    QString toString();

    QString firstname() const;
    void setFirstname(const QString &firstname);

    QString lastname() const;
    void setLastname(const QString &lastname);

    QString email() const;
    void setEmail(const QString &email);

    QDate birthday() const;
    void setBirthday(const QDate &birthday);

    QString address() const;
    void setAddress(const QString &address);

    QString username() const;
    void setUsername(const QString &username);

    QString password() const;
    void setPassword(const QString &password);

    int score() const;
    void setScore(int score);

private:
    QString m_firstname;
    QString m_lastname;
    QString m_email;
    QDate m_birthday;
    QString m_address;
    QString m_taskList;
    QString m_username;
    QString m_password;
    int m_score;
};

#endif // USER_H
