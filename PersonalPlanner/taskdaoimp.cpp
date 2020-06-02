#include <QDebug>
#include <QFile>
#include <QSqlError>
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

    qDebug() << "Prepare Query: "<< query.prepare("INSERT INTO tasks (title, date, description,importance, status, repetition, username) "
                  "VALUES (:title, :date, :description, :importance, :status, :repetition, :username)");

    query.bindValue(":title", task.title());
    query.bindValue(":date", task.date());
    query.bindValue(":description",task.description());
    query.bindValue(":importance", task.importance());
    query.bindValue(":status", task.status());
    query.bindValue(":repetition", task.repetition());
    query.bindValue(":username", m_username);


    return query.exec();
}

Task* TaskDaoImp::read(int t_taskID){

    QString m_title ;
    int m_importance ;
    QString m_description;
    QString m_status;
    QDate t_date(1,2,3);
    QString m_repetition;
    QString m_username;

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
        m_repetition = query.value(7).toString();
        m_username = query.value(8).toString();

        qDebug() << t_taskID << m_title << t_date << m_description << m_importance
                 << m_status << m_repetition << m_username;
    }

    m_task = new Task(t_taskID, m_title, t_date, m_importance, m_username);
    m_task->setDescription(m_description);
    m_task->setStatus(m_status);
    m_task->setRepetition(m_repetition);

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

    return query.exec();
}

