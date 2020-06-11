#include "databasesingleton.h"
#include "taskdaoimp.h"
#include "task.h"
#include "user.h"
#include "tasklistmodel.h"


TaskDaoImp::TaskDaoImp(){
}

TaskDaoImp::~TaskDaoImp(){
    delete taskModel;
}

bool TaskDaoImp::create(const Task& task, const QString& username){

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
    query.bindValue(":username", username);

    return query.exec();
}


bool TaskDaoImp::readAll(QString &username){
    m_taskList.clear();

    int t_taskID;
    QString title ;
    int importance ;
    QString description;
    QString status;
    QDate date(1,2,3);
    QString repetition;


    Task newTask(t_taskID, title,date, importance, username);


    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM tasks WHERE username=" ":t_username");
    query.bindValue(":t_username", username);

    bool stat = false;
    if(query.exec()){
        stat = true;
    }

    while (query.next()) {
        t_taskID = query.value(0).toInt();
        title = query.value(1).toString();
        date = query.value(2).toDate();
        description = query.value(3).toString();
        importance = query.value(5).toInt();
        status = query.value(6).toString();
        repetition = query.value(7).toString();

        newTask.setTaskID(t_taskID);
        newTask.setTitle(title);
        newTask.setDate(date);
        newTask.setDescription(description);
        newTask.setImportance(importance);
        newTask.setRepetition(repetition);

        m_taskList.append(newTask);


        qDebug() << t_taskID << title << date << description << importance
                 << status << repetition << username;

    }

    taskModel = new TaskListModel;
    taskModel->populateData(m_taskList);

    return stat;
}


Task TaskDaoImp::read(int t_taskID){

    QString title ;
    int importance ;
    QString description;
    QString status;
    QDate date(1,2,3);
    QString repetition;
    QString username;

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM tasks WHERE task_id=" ":t_taskID");
    query.bindValue(":t_taskID", t_taskID);

    query.exec();

    while (query.next()) {
        t_taskID = query.value(0).toInt();
        title = query.value(1).toString();
        date = query.value(2).toDate();
        description = query.value(3).toString();
        importance = query.value(5).toInt();
        status = query.value(6).toString();
        repetition = query.value(7).toString();
        username = query.value(8).toString();

        qDebug() << t_taskID << title << date << description << importance
                 << status << repetition << username;
    }

    Task task(t_taskID, title, date, importance, username);
    task.setDescription(description);
    task.setStatus(status);
    task.setRepetition(repetition);

    return task;
}

bool TaskDaoImp::update(Task& task){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    qDebug() << "Prepare Query: " << query.prepare( " UPDATE tasks SET WHERE task_id=" ":t_id");
    query.bindValue(":t_id", task.taskID());


    return query.exec();
}

bool TaskDaoImp::delete_(Task task){ // or taskID?
    int t_id = task.taskID();
    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "id is : " << t_id<< "Prepare Query: "<< query.prepare("DELETE FROM tasks WHERE task_id=:t_id");
    query.bindValue(":t_id", t_id);

    return query.exec();
}

TaskListModel *TaskDaoImp::getTaskModel() const
{
    return taskModel;
}

void TaskDaoImp::setTaskModel(TaskListModel *value)
{
    taskModel = value;
}

QList<Task> TaskDaoImp::getTaskList() const
{
    return m_taskList;
}

void TaskDaoImp::setTaskList(const QList<Task> &taskList)
{
    m_taskList = taskList;
}
