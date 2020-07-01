#ifndef USER_H
#define USER_H

#include <QDate>

class User
{
public:
    User(QString t_username, QString t_password, QString t_firstname, QString t_lastname, QString t_email);
    ~User();

    QString username() const;

    QString password() const;

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

    int score() const;
    void setScore(int score);

    int getWidth() const;
    void setWidth(int value);

    int getHeight() const;
    void setHeight(int value);

    QByteArray getProfilePicture() const;
    void setProfilePicture(const QByteArray &profilePicture);

    QString toString();

private:
    QString m_username;
    QString m_password;
    QString m_firstname;
    QString m_lastname;
    QString m_email;
    QDate m_birthday;
    QString m_address;
    QString m_taskList;
    QByteArray m_profilePicture;

    int m_score;
    int width;
    int height;
};

#endif // USER_H
