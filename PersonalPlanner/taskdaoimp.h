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
    bool delete_(Task &task);


    TaskListModel *getTaskModel() const;
    void setTaskModel(TaskListModel *value);

private:
    Task* m_task;
    TaskListModel *taskModel;
    //unsigned int m_counter = 1;

};

#endif // TASKDAOIMP_H
