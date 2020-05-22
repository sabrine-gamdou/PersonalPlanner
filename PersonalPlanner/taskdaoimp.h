
#include "task.h"

#ifndef TASKDAOIMP_H
#define TASKDAOIMP_H

#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

class TaskDaoImp{
public:
    TaskDaoImp();
    ~TaskDaoImp();
    bool create (Task &task);
    Task *read(int t_taskID);
    bool update(Task &task);
    bool delete_(Task &task);
private:
     Task* m_task;
};

#endif // TASKDAOIMP_H
