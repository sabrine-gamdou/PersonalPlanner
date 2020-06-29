#ifndef TASKDAOIMP_H
#define TASKDAOIMP_H

#include "task.h"
#include "tasklistmodel.h"

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDate>
#include <QDebug>

class TaskDaoImp{
public:
    TaskDaoImp();
    ~TaskDaoImp();

    bool create (Task &task, const QString &username);
    bool readAll(const QString &username);
    bool update(const Task &task);
    bool delete_(const Task &task);
    bool deleteAllTasks(const QString &username);

    TaskListModel *getTaskModel() const;

    QList<Task> getTaskList() const;
    void setTaskList(const QList<Task> &taskList);

private:
    TaskListModel* taskModel;
    QList<Task> m_taskList;
};

#endif // TASKDAOIMP_H
