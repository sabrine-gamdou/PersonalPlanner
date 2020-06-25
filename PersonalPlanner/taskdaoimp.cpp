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

bool TaskDaoImp::create(Task& task, const QString& username){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    task.setStatus("In-Progress");

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

    Task newTask(-1, "title",QDate(1,2,3), -1, username);

    DatabaseSingleton::getInstance();

    QSqlQuery query;

   // query.prepare( " SELECT * FROM tasks WHERE username=" ":t_username");
    query.prepare("SELECT * FROM tasks WHERE username=(:username) ORDER BY date ASC,  (CASE status WHEN 'Completed' THEN 1 WHEN 'In-Progress' THEN 2 WHEN 'Failed' THEN 3 END), status DESC");
    query.bindValue(":username", username);

    bool status = false;
    if(query.exec()){
        status = true;
    }

    while (query.next()){

        newTask.setTaskID(query.value(0).toInt());
        newTask.setTitle(query.value(1).toString());
        newTask.setDate(query.value(2).toDate());
        newTask.setDescription(query.value(3).toString());
        newTask.setImportance(query.value(4).toInt());
        newTask.setStatus(query.value(5).toString());
        newTask.setRepetition(query.value(6).toString());

        m_taskList.append(newTask);


        qDebug() << newTask.taskID() << newTask.title() << newTask.date()
                 << newTask.description() << newTask.importance()
                 << newTask.status() << newTask.repetition() << newTask.username();

    }

    taskModel = new TaskListModel;
    taskModel->populateData(m_taskList);

    return status;
}


Task TaskDaoImp::read(int t_taskID, QString &username){

    Task task(-1, "title",QDate(1,2,3), -1, username);

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM tasks WHERE task_id=(:t_taskID) AND username=(:username)");
    query.bindValue(":t_taskID", t_taskID);
    query.bindValue(":username", username);

    query.exec();

    while (query.next()) {
        task.setTaskID(query.value(0).toInt());
        task.setTitle(query.value(1).toString());
        task.setDate(query.value(2).toDate());
        task.setDescription(query.value(3).toString());
        task.setImportance(query.value(4).toInt());
        task.setStatus(query.value(5).toString());
        task.setRepetition(query.value(6).toString());

        qDebug() << task.taskID() << task.title() << task.date()
                 << task.description() << task.importance()
                 << task.status() << task.repetition() << task.username();
    }

    return task;
}

bool TaskDaoImp::update(Task& task){

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    task.setStatus("In-Progress");

    qDebug() << "Prepare Query: "<< query.prepare("UPDATE tasks SET title = (:title), date = (:date), "
                                                  "description = (:description), importance = (:importance), "
                                                  "status = (:status), repetition = (:repetition) "
                                                  "WHERE username = (:un)"
                                                  "AND task_id=(:taskID);");
    query.bindValue(":un", task.username());
    query.bindValue(":taskID", task.taskID());
    query.bindValue(":title", task.title());
    query.bindValue(":date", task.date());
    query.bindValue(":description", task.description());
    query.bindValue(":importance", task.importance());
    query.bindValue(":status", task.status());
    query.bindValue(":repetition", task.repetition());

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

TaskListModel *TaskDaoImp::getTaskModel() const{

    return taskModel;
}

void TaskDaoImp::setTaskModel(TaskListModel *value){

    taskModel = value;
}

QList<Task> TaskDaoImp::getTaskList() const{

    return m_taskList;
}

void TaskDaoImp::setTaskList(const QList<Task> &taskList){

    m_taskList = taskList;
}
