#include <string>
#include <QDate>
#include <QImage>
#ifndef TASK_H
#define TASK_H


class Task{

private:
    int m_taskID;
    QString m_title;
    QDate m_date;
    QString m_description;
    QImage m_icon;
    int m_importance;
    QString m_status;

public:
    Task(int t_taskID, QString t_title, QDate t_date, int t_importance);
    ~Task();

    QString toString();

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



    int taskID() const;
    void setTaskID(int taskID);
};

#endif // TASK_H
