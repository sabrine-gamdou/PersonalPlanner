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
    bool create (Task &task, const QString& username);
    Task read(int t_taskID, QString &username);
    bool update(Task &task);
    bool delete_(Task task);
    bool readAll(QString &username);
    void sortByStatus(QString &username);

    TaskListModel *getTaskModel() const;
    void setTaskModel(TaskListModel *value);

    QList<Task> getTaskList() const;
    void setTaskList(const QList<Task> &taskList);

private:
    TaskListModel* taskModel;
    QList<Task> m_taskList;

};

#endif // TASKDAOIMP_H
