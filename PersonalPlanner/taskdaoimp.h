#ifndef TASKDAOIMP_H
#define TASKDAOIMP_H

#include "task.h"
#include "tasklistmodel.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDebug>
#include <QFile>
#include <QSqlError>
#include <QDate>
#include <string>
#include <QDebug>
#include <iostream>

class TaskDaoImp{
public:
    TaskDaoImp();
    ~TaskDaoImp();
    bool create (const Task &task, const QString& username);
    Task read(int t_taskID);
    bool update(Task &task);
    bool delete_(int t_id);
    bool readAll(QString &username);

    TaskListModel *getTaskModel() const;
    void setTaskModel(TaskListModel *value);


    QList<QString> getTitleList() const;
    void setTitleList(const QList<QString> &titleList);

    QList<QString> getDateList() const;
    void setDateList(const QList<QString> &dateList);

    QList<QString> getDescriptionList() const;
    void setDescriptionList(const QList<QString> &descriptionList);

    QList<QString> getImportanceList() const;
    void setImportanceList(const QList<QString> &importanceList);

    QList<QString> getRepetitionList() const;
    void setRepetitionList(const QList<QString> &repetitionList);

    QList<int> getTaskIDList() const;
    void setTaskIDList(const QList<int> &taskIDList);

private:
    Task* m_task;
    TaskListModel* taskModel;
    //unsigned int m_counter = 1;

    QList<int> m_taskIDList;
    QList<QString> m_titleList;
    QList<QString> m_dateList;
    QList<QString> m_descriptionList;
    QList<QString> m_importanceList;
    QList<QString> m_repetitionList;

};

#endif // TASKDAOIMP_H
