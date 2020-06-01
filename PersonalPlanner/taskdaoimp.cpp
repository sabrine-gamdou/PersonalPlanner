#include <QDebug>
#include <QFile>
#include <QDate>
#include <string>
#include <QDebug>
#include <iostream>
#include "databasesingleton.h"
#include "taskdaoimp.h"
#include "task.h"
#include "user.h"

Task* m_task;
User* m_user;

TaskDaoImp::TaskDaoImp(){}

TaskDaoImp::~TaskDaoImp(){}


bool TaskDaoImp::create(Task& task, QString m_username){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("INSERT INTO tasks (task_id, title, date, description,importance, status, username) "
                  "VALUES (:task_id, :title, :date, :description, :importance, :status, :m_username)");
    query.bindValue(":task_id", task.taskID());
    query.bindValue(":title", task.title());
    query.bindValue(":date", task.date());
    query.bindValue(":description",task.description());
    query.bindValue(":importance", task.importance());
    query.bindValue(":status", task.status());
    query.bindValue(":m_username", m_username);

    bool checkState = query.exec();

    if (checkState) {
        m_counter++;
        return true;
    }
    return false;

}

Task* TaskDaoImp::read(int t_taskID){

    QString m_title ;
    int m_importance ;
    QString m_description;
    QString m_status;
    QDate t_date(1,2,3);

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM tasks WHERE task_id=" ":t_taskID");
    query.bindValue(":t_taskID", t_taskID);

    query.exec();

    while (query.next()) {
        t_taskID = query.value(0).toInt();
        m_title = query.value(1).toString();
        t_date = query.value(2).toDate();
        m_description = query.value(3).toString();
        m_importance = query.value(5).toInt();
        m_status = query.value(6).toString();

        qDebug() << t_taskID << m_title << t_date << m_description << m_importance
                 << m_status;
    }

    m_task = new Task(t_taskID, m_title, t_date, m_importance);
    m_task->setDescription(m_description);
    m_task->setStatus(m_status);

    return m_task;
}

bool TaskDaoImp::update(Task& task){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: " << query.prepare( " UPDATE tasks SET WHERE task_id=" ":t_id");
    query.bindValue(":t_id", task.taskID());


    return query.exec();
}

bool TaskDaoImp::delete_(Task& task){ // or taskID?

    int t_id = task.taskID();

    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("DELETE FROM tasks WHERE task_id=" ":t_id");
    query.bindValue(":t_id", t_id);

    bool checkState = query.exec();

    if (checkState) {
        m_counter--;
        return true;
    }
    return false;
}

int TaskDaoImp::counter() const
{
    return m_counter;
}

void TaskDaoImp::setCounter(int counter)
{
    m_counter = counter;
}
