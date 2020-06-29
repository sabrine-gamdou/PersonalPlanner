#ifndef TASK_H
#define TASK_H

#include <QDate>
#include <QString>

class Task{

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

    int importance() const;
    void setImportance(int importance);

    QString status() const;
    void setStatus(const QString &status);

    QString repetition() const;
    void setRepetition(const QString &repetition);

    QString username() const;
    void setUsername(const QString &username);

    QString toString();

private:
    int m_taskID;
    QString m_title;
    QDate m_date;
    QString m_description;
    int m_importance;
    QString m_status;
    QString m_repetition;
    QString m_username;
};

#endif // TASK_H
