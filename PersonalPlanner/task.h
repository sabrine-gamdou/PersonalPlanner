#ifndef TASK_H
#define TASK_H

#include <string>
#include <QDate>
#include <QImage>
#include <iostream>

class Task{

private:
    int m_taskID;
    QString m_title;
    QDate m_date;
    QString m_description;
    QImage m_icon;
    int m_importance;
    QString m_status;
    QString m_repetition;
    QString m_username;


public:
    Task(int t_taskID = -1, QString t_title = "", QDate t_date =  QDate(1,2,3), int t_importance = -1, QString m_username = "");
    ~Task();


    int taskID() const;
    void setTaskID(int taskID);

    QString title() const;
    void setTitle(const QString &title);

    QDate date() const;
    void setDate(const QDate &date);

    QString description() const;
    void setDescription(const QString &description);

    QImage icon() const;
    void setIcon(const QImage &icon);

    int importance() const;
    void setImportance(int importance);

    QString status() const;
    void setStatus(const QString &status);

    QString repetition() const;
    void setRepetition(const QString &repetition);

    QString username() const;
    void setUsername(const QString &username);
    //Brauchen wir die überhaupt? Werden nirgends benutzt.
    bool getActive() const;
    void setActive(bool value);

    QString toString();
};

#endif // TASK_H
