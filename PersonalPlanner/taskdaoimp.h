

#ifndef TASKDAOIMP_H
#define TASKDAOIMP_H

#include "task.h"
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class TaskDaoImp{
public:
    TaskDaoImp();
    ~TaskDaoImp();
    bool create (Task &task, QString m_username);
    Task *read(int t_taskID);
    bool update(Task &task);
    bool delete_(Task &task);


private:
    Task* m_task;
    //unsigned int m_counter = 1;

};

#endif // TASKDAOIMP_H
