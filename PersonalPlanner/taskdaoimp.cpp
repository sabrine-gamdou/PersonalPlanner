#include "databasesingleton.h"
#include "taskdaoimp.h"
#include "task.h"
#include "user.h"
#include "tasklistmodel.h"


TaskDaoImp::TaskDaoImp(){}

TaskDaoImp::~TaskDaoImp(){}

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


//    taskModel->titleList().append(task.title());
//    taskModel->dateList().append(task.date().toString());
//    taskModel->descriptionList().append(task.description());
//    taskModel->importanceList().append(QString::number(task.importance()));
//    taskModel->repetitionList().append(task.repetition());


    return query.exec();
}


bool TaskDaoImp::readAll(QString &username){

    QString title ;
    int importance ;
    QString description;
    QString status;
    QDate date(1,2,3);
    QString repetition;
    //QString username;

    DatabaseSingleton::getInstance();

    QSqlQuery query;

    query.prepare( " SELECT * FROM tasks WHERE username=" ":t_username");
    query.bindValue(":t_username", username);

    bool stat = false;
            if(query.exec()){
            status = true;
        }

    while (query.next()) {
        int t_taskID = query.value(0).toInt();
        title = query.value(1).toString();
        date = query.value(2).toDate();
        description = query.value(3).toString();
        importance = query.value(5).toInt();
        status = query.value(6).toString();
        repetition = query.value(7).toString();
       // username = query.value(8).toString();

        qDebug() << title << date << description << importance
                 << status << repetition << username;

        m_titleList.append(title);
        m_dateList.append(date.toString());
        m_descriptionList.append(description);
        m_importanceList.append(QString::number(importance));
        m_repetitionList.append(repetition);


    }
    taskModel = new TaskListModel;
    taskModel->populateData(m_titleList, m_dateList, m_descriptionList, m_importanceList, m_repetitionList);

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

bool TaskDaoImp::delete_(Task& task){ // or taskID?

    int t_id = task.taskID();

    DatabaseSingleton::getInstance();
    QSqlQuery query;

    qDebug() << "Prepare Query: "<< query.prepare("DELETE FROM tasks WHERE task_id=" ":t_id");
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

QList<QString> TaskDaoImp::getTitleList() const
{
    return m_titleList;
}

void TaskDaoImp::setTitleList(const QList<QString> &titleList)
{
    m_titleList = titleList;
}

QList<QString> TaskDaoImp::getDateList() const
{
    return m_dateList;
}

void TaskDaoImp::setDateList(const QList<QString> &dateList)
{
    m_dateList = dateList;
}

QList<QString> TaskDaoImp::getDescriptionList() const
{
    return m_descriptionList;
}

void TaskDaoImp::setDescriptionList(const QList<QString> &descriptionList)
{
    m_descriptionList = descriptionList;
}

QList<QString> TaskDaoImp::getImportanceList() const
{
    return m_importanceList;
}

void TaskDaoImp::setImportanceList(const QList<QString> &importanceList)
{
    m_importanceList = importanceList;
}

QList<QString> TaskDaoImp::getRepetitionList() const
{
    return m_repetitionList;
}

void TaskDaoImp::setRepetitionList(const QList<QString> &repetitionList)
{
    m_repetitionList = repetitionList;
}


